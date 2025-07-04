#include "../include/main.h"
#include "../include/button.h"
#include "../include/raylib/raylib.h"
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#if defined(_WIN32) || defined(_WIN64)
// Define gmtime_r in terms of Windows gmtime_s
static struct tm *gmtime_r(const time_t *timep, struct tm *result) {
  // gmtime_s returns 0 on success
  return (gmtime_s(result, timep) == 0) ? result : NULL;
}
#endif

CaseValue case_values[NUM_CASES];
Case *cases[NUM_CASES] = {NULL};
int case_timer = OPEN_CASE_TIME;

int player_case_num;
int player_case_value;
int opened_case_num = 0;
int opened_case_value = 0;
const short CASES_PER_ROUND[10] = {0, 6, 5, 4, 3, 2, 1, 1, 1, 0};
bool is_case_opening = false;

Button *btn_play = NULL;
Button *btn_accept = NULL;
Button *btn_reject = NULL;
Button *btn_retrun = NULL;

bool was_offer_accepted = false;

Sound duck_sfx;

enum GameState { TITLE, PICK_CASE, DISPLAY_CASE, OFFER, GAMEOVER };

int game_state = TITLE;
short game_round = 0;
int current_offer = 0;
short cases_to_pick = 7;
int banner_x = 0;
char *banner_text = "";
// const int SCREEN_WIDTH = 960;
// const int SCREEN_HEIGHT = 540;

CaseValue case_values[24] = {
    {1, true},      {3, true},      {5, true},      {10, true},
    {25, true},     {50, true},     {75, true},     {100, true},
    {200, true},    {250, true},    {500, true},    {750, true},
    {1000, true},   {2500, true},   {5000, true},   {10000, true},
    {25000, true},  {50000, true},  {100000, true}, {200000, true},
    {300000, true}, {500000, true}, {750000, true}, {1000000, true}};

int main(void) {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Accept Or Reject");
  InitAudioDevice();
  SetTargetFPS(FPS);
  SetTraceLogLevel(LOG_ALL);
  SetExitKey(KEY_Q);

  duck_sfx = LoadSound("res/duck.ogg");

  btn_play = button_new("Play", 400, 370, StartGame, PT_BLUE, PT_GRAY);
  btn_accept = button_new("Accept", 200, 400, AcceptDeal, PT_GREEN, PT_GRAY);
  btn_reject = button_new("Reject", 400, 400, RejectDeal, PT_RED, PT_GRAY);
  btn_retrun = button_new("Main", 400, 450, BackToMain, PT_BLUE, PT_GRAY);

  ResetGame();

  while (!WindowShouldClose()) {
    switch (game_state) {
    case TITLE:
      UpdateTitleScreen();
      break;
    case PICK_CASE:
      UpdateGame();
      break;
    case OFFER:
      UpdateOffer();
      break;
    case GAMEOVER:
      UpdateGameOver();
      break;
    }

    BeginDrawing();
    ClearBackground(BLACK);
    switch (game_state) {
    case TITLE:
      DrawTitleScreen();
      break;
    case PICK_CASE:
      DrawGame();
      break;
    case OFFER:
      DrawOffer();
      break;
    case GAMEOVER:
      DrawGameOver();
      break;
    }
    EndDrawing();
  }

  CleanUp();
  CloseAudioDevice();
  CloseWindow();
  return 0;
}

void BackToMain() {
  game_state = TITLE;
  ResetGame();
}

void UpdateTitleScreen() {
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    if (btn_play->is_hovered) {
      button_was_clicked(btn_play);
    }
  }
  button_update(btn_play, GetMousePosition());
}

void UpdateGame() {
  UpdateBanner();
  if (case_timer < OPEN_CASE_TIME) {
    case_timer++;
  }
  if (case_timer >= OPEN_CASE_TIME) {
    if (cases_to_pick == 0 && game_round <= 8) {
      game_state = OFFER;
      is_case_opening = false;
      UpdateBannerText(99);
      current_offer = GetOffer();
    } else {
      if (game_round <= 8) {
        game_state = PICK_CASE;
      } else if (game_round == 9) {
        game_state = GAMEOVER;
      }
    }
  }
  is_case_opening = case_timer < OPEN_CASE_TIME - 10;

  // Update each case
  for (int i = 0; i < NUM_CASES; i++) {
    if (cases[i]->interactable) {
      UpdateCase(cases[i], GetMousePosition());
    }
    // Make sure player can't keep clicking after opening case
    if (!is_case_opening) {
      if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && cases[i]->hovered) {
        PlayerPickCase(cases[i]);
        if (cases[i]->value == 1000000) {
          PlaySound(duck_sfx);
        }
      }
    }
  }
}

void UpdateBanner() {
  banner_x += 2;
  if (banner_x >= SCREEN_WIDTH) {
    banner_x = -MeasureText(banner_text, 38);
  }
}

void UpdateOffer() {
  UpdateBanner();
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    if (btn_accept->is_hovered) {
      button_was_clicked(btn_accept);
    }
    if (btn_reject->is_hovered) {
      button_was_clicked(btn_reject);
    }
  }
  Vector2 mousePos = GetMousePosition();
  button_update(btn_accept, mousePos);
  button_update(btn_reject, mousePos);
}

void SetupCases() {
  int indices[NUM_CASES];
  for (int i = 0; i < NUM_CASES; i++) {
    indices[i] = i;
  }
  ShuffleCaseValues(indices, NUM_CASES);

  // Setting up cases
  for (int i = 0; i < NUM_CASES; i++) {
    case_values[i].in_play = true;
    // Calculate the row and column
    int row = i / NUM_COLS; // Integer division (gives row index)
    int col = i % NUM_COLS; // Modulo operation (gives column index)

    // Calculate the x and y positions based on row and column with gaps
    int x = 30 + (col * (CASE_WIDTH + CASE_GAP_X));
    int y = 80 + (row * (CASE_HEIGHT + CASE_GAP_Y));

    // Create case
    cases[i] = case_new(i + 1, case_values[indices[i]].value, x, y);
    cases[i]->value_index = indices[i];
    if (!cases[i]) {
      TraceLog(LOG_ERROR, "Failed to allocate memory for case %d", i);
      CleanUp();
      CloseWindow();
    }
  }
}

void UpdateGameOver() {
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    if (btn_retrun->is_hovered) {
      button_was_clicked(btn_retrun);
    }
  }
  button_update(btn_retrun, GetMousePosition());
}

void DrawTitleScreen() {
  DrawText("Accept or Reject", 300, 200, 40, PT_WHITE);
  button_draw(btn_play);
}

void DrawGame() {
  if (case_timer < OPEN_CASE_TIME) {
    DrawOpenedCaseInfo();
  } else {
    DrawBanner();
    DrawLines();
    DrawDollarAmounts();
    for (int i = 0; i < NUM_CASES; i++) {
      DrawCase(cases[i]);
    }
  }
}

// TODO: Rename to DrawMarquee
void DrawBanner() {
  DrawText(banner_text, banner_x, 4, BANNER_FONT_SIZE, PT_ORANGE);
}

void DrawLines() {
  DrawRectangleLinesEx((Rectangle){0, 0, SCREEN_WIDTH, 44}, LINE_THICKNESS,
                       PT_BLUE);
  DrawRectangleLinesEx((Rectangle){0, 0, SCREEN_WIDTH, SCREEN_HEIGHT},
                       LINE_THICKNESS, PT_BLUE);
  DrawRectangleLinesEx((Rectangle){0, 40, SCREEN_WIDTH - 300, SCREEN_HEIGHT},
                       LINE_THICKNESS, PT_BLUE);
}

void DrawDollarAmounts() {
  for (int i = 0; i < 12; i++) {
    DrawText(TextFormat("$%d", case_values[i].value), 700, 80 + (34 * i), 30,
             case_values[i].in_play ? PT_BLUE : Fade(PT_GRAY, 0.4f));
  }

  for (int i = 12; i < 24; i++) {
    DrawText(TextFormat("$%d", case_values[i].value), 800, 80 + (34 * (i - 12)),
             30, case_values[i].in_play ? PT_BLUE : Fade(PT_GRAY, 0.4f));
  }
}

void DrawOffer() {
  DrawBanner();
  if (game_round == 7) {
    DrawText("Last Offer", 10, 60, 30, PT_ORANGE);
  } else {
    DrawText(TextFormat("Next Round\n%s",
                        pluralize_cases(CASES_PER_ROUND[game_round + 1])),
             10, 50, 30, PT_ORANGE);
  }
  DrawLines();
  DrawDollarAmounts();
  DrawText("Offer", 350, 200, 30, PT_WHITE);
  DrawLine(340, 230, 420, 230, PT_WHITE);
  DrawText(TextFormat("$ %d", GetOffer()), 350, 300, 30, PT_WHITE);
  button_draw(btn_accept);
  button_draw(btn_reject);
}

void DrawGameOver() {
  if (was_offer_accepted) {
    DrawText("Offer Accepted:", 350, 200, 30, PT_WHITE);
    DrawText(TextFormat("$ %d", current_offer), 350, 250, 30, PT_WHITE);

    DrawText("Your case had:", 350, 300, 30, PT_WHITE);
    DrawText(TextFormat("$ %d", player_case_value), 350, 350, 30, PT_WHITE);
  } else {
    DrawText("Your case had:", 350, 300, 30, PT_WHITE);
    DrawText(TextFormat("$ %d", player_case_value), 350, 350, 30, PT_WHITE);
  }

  button_draw(btn_retrun);
}

void DrawOpenedCaseInfo() {
  const char *line_1 = TextFormat("Case %d had", opened_case_num);
  const char *line_2 = TextFormat("$ %d", opened_case_value);
  DrawText(line_1, (SCREEN_WIDTH / 2) - (MeasureText(line_1, 40) / 2), 200, 40,
           PT_WHITE);
  DrawText(line_2, (SCREEN_WIDTH / 2) - (MeasureText(line_2, 40) / 2), 260, 40,
           PT_WHITE);
}

void StartGame() {
  TraceLog(LOG_DEBUG, "Starting game...");
  game_state = PICK_CASE;
}

void AcceptDeal() {
  TraceLog(LOG_DEBUG,
           TextFormat("Player accepted the deal of %d", current_offer));
  was_offer_accepted = true;
  GoToGameOver();
}
void RejectDeal() {
  TraceLog(LOG_DEBUG,
           TextFormat("Player refused the deal of %d", current_offer));
  if (game_round < 7) {
    AdvanceRound();
  } else {
    GoToGameOver();
  }
}

void CleanUp(void) {
  for (int i = 0; i < NUM_CASES; i++) {
    free(cases[i]);
  }
  free(btn_play);
  free(btn_accept);
  free(btn_reject);
  UnloadSound(duck_sfx);
}

void ShuffleCaseValues(int *array, size_t n) {
  srand(time(NULL));
  if (n > 1) {
    size_t i;
    for (i = 0; i < n - 1; i++) {
      size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
      int t = array[j];
      array[j] = array[i];
      array[i] = t;
    }
  }
}

Sound LoadSoundSafe(const char *filename) {
  Sound sound = LoadSound(filename);
  if (sound.stream.buffer == NULL) {
    TraceLog(LOG_ERROR, TextFormat("Failed to load sound: %s", filename));
  }
  return sound;
}

const char *pluralize_cases(int n) {
  static char buffer[32];

  if (n == 1) {
    snprintf(buffer, sizeof(buffer), "1 Case");
  } else {
    snprintf(buffer, sizeof(buffer), "%d Cases", n);
  }

  return buffer;
}

void ResetGame() {
  game_state = TITLE;
  was_offer_accepted = false;
  player_case_num = 0;
  player_case_value = 0;
  memset(cases, 0, sizeof(cases));
  SetupCases();
  cases_to_pick = 7;
  game_round = 0;
  UpdateBannerText(cases_to_pick);
}

int GetOffer() {
  int values_left = 0;
  double sum = 0.0;
  int lowest = 1000000;

  // First pass: calculate values_left, sum, and lowest
  for (int i = 0; i < NUM_CASES; i++) {
    if (case_values[i].in_play) {
      values_left++;
      sum += case_values[i].value;
      if (case_values[i].value < lowest) {
        lowest = case_values[i].value;
      }
    }
  }

  double off_set = 1.0 - 0.7 * ((double)values_left / NUM_CASES);
  double initial = lowest + ((sum / values_left - lowest) * off_set);

  // Second pass: find next_lower
  int next_lower = -1;
  for (int i = 0; i < NUM_CASES; i++) {
    if (case_values[i].in_play) {
      int val = case_values[i].value;
      if (val > next_lower && val <= initial) {
        next_lower = val;
      }
    }
  }

  // Final offer calculation
  double offer =
      next_lower * (1 - off_set * off_set) + initial * (off_set * off_set);
  return (int)floor(offer);
}

void AdvanceRound() {
  game_round++;
  cases_to_pick = CASES_PER_ROUND[game_round];
  UpdateBannerText(cases_to_pick);
  if (game_round < 9) {
    game_state = PICK_CASE;
  }
}

void UpdateBannerText(int n_cases) {
  static char buffer[MAX_BANNER_LEN];

  // FIXME: Find better way to set banner for banker's offer
  if (n_cases == 99) {
    banner_text = "Banker's Offer";
    return;
  }

  if (player_case_num != 0) {
    if (n_cases > 1) {
      snprintf(buffer, sizeof(buffer), "Open %d more cases", n_cases);
    } else {
      snprintf(buffer, sizeof(buffer), "Open %d case", n_cases);
    }
  } else {
    snprintf(buffer, sizeof(buffer), "Pick your case");
  }
  banner_text = buffer;
  // return buffer; // Return pointer to static buffer
}

void LogMessage(char str[]) {
  FILE *log = NULL;
  log = fopen("aor.log", "a");
  if (log == NULL) {
    printf("Error! can't open log file.");
  }
  time_t t = time(NULL);
  assert(t != ((time_t)-1)); // error handling
  struct tm tm;
  memset(&tm, 0, sizeof(tm));
  assert(gmtime_r(&t, &tm) != NULL); // error handling
  fprintf(log, "%04d-%02d-%02d %02d:%02d:%02d - %s\n", 1900 + tm.tm_year,
          tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, str);
  fclose(log);
}

void PlayerPickCase(Case *c) {
  if (c == NULL) {
    TraceLog(LOG_ERROR, "Case is null");
  }
  if (player_case_num == 0) {
    c->selected = true;
    c->hovered = false;
    c->interactable = false;
    player_case_num = c->number;
    player_case_value = c->value;
    AdvanceRound();

  } else {
    OpenCase(c);
  }
}

Case *case_new(int number, int value, int x, int y) {
  Case *c = malloc(sizeof(Case));
  if (!c) {
    return NULL;
  }
  c->number = number;
  c->value = value;
  c->rect = (Rectangle){x, y, CASE_WIDTH, CASE_HEIGHT};
  c->position = (Vector2){x, y};
  c->interactable = true;
  c->selected = false;
  c->hovered = false;
  c->picked = false;
  c->opened = false;
  c->visible = true;
  c->txt_pos = (Vector2){x + 8, y + 6};
  return c;
}

void UpdateCase(Case *c, Vector2 mousePos) {
  c->hovered = CheckCollisionPointRec(mousePos, c->rect);
}

void DrawCase(Case *c) {
  if (c->visible) {
    if (c->selected) {
      DrawRectangleLinesEx(
          (Rectangle){c->position.x, c->position.y, CASE_WIDTH, CASE_HEIGHT}, 3,
          Fade(PT_BLUE, 0.5f));
      DrawText(TextFormat("%d", c->number), (int)c->txt_pos.x,
               (int)c->txt_pos.y, 30, Fade(PT_BLUE, 0.5f));
    } else {
      DrawRectangleLinesEx(
          (Rectangle){c->position.x, c->position.y, CASE_WIDTH, CASE_HEIGHT}, 3,
          c->hovered ? PT_ORANGE : PT_GRAY);
      DrawText(TextFormat("%d", c->number), (int)c->txt_pos.x,
               (int)c->txt_pos.y, 30, c->hovered ? PT_ORANGE : PT_GRAY);
    }
  }
}

void OpenCase(Case *c) {
  TraceLog(LOG_INFO,
           TextFormat("Case %d was opened. Had $%d", c->number, c->value));
  if (!c->selected) {
    case_timer = 0;
    UpdateCaseDisplay(c->number, c->value);
    Clamp(cases_to_pick--, 0, 10);
    UpdateBannerText(cases_to_pick);
    c->interactable = false;
    c->hovered = false;
    c->opened = true;
    c->selected = false;
    c->picked = true;
    case_values[c->value_index].in_play = false;
    c->visible = false;
  }
}

void UpdateCaseDisplay(int case_num, int case_val) {
  opened_case_num = case_num;
  opened_case_value = case_val;
}

void GoToGameOver() { game_state = GAMEOVER; }
