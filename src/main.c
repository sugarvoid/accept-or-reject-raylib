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

Vector2 mousePos = (Vector2){0, 0};

// Player *player = NULL;

int player_case_num;
int player_case_value;

const short CASES_PER_ROUND[10] = {0, 6, 5, 4, 3, 2, 1, 1, 1, 0};

Button *btn_play = NULL;
Button *btn_accept = NULL;
Button *btn_reject = NULL;

bool wasOfferAccepted = false;

CaseValue case_values[NUM_CASES];
Case *cases[NUM_CASES] = {NULL};
Case *pickedCase = NULL;
Case *playerCase = NULL;
int opened_case_num = 0;
int opened_case_value = 0;
Sound duck_sfx;

typedef enum { TITLE, PICK_CASE, DISPLAY_CASE, OFFER, GAMEOVER } GameState;

short game_round = 0;
int current_offer = 0;
short cases_to_pick = 7;

int game_state = TITLE;
int banner_x = 0;
char *bannerText = "";

const int screenWidth = 960;
const int screenHeight = 540;
int playerCaseValue = 0;
bool is_case_opening = false;

int case_timer = 90;
// Timer *opening_case_timer = NULL;

CaseValue case_values[24] = {
    {1, true},      {3, true},      {5, true},      {10, true},
    {25, true},     {50, true},     {75, true},     {100, true},
    {200, true},    {250, true},    {500, true},    {750, true},
    {1000, true},   {2500, true},   {5000, true},   {10000, true},
    {25000, true},  {50000, true},  {100000, true}, {200000, true},
    {300000, true}, {500000, true}, {750000, true}, {1000000, true}};

int main(void) {
  InitWindow(screenWidth, screenHeight, "Accept Or Reject");
  InitAudioDevice();
  SetTargetFPS(FPS);
  SetTraceLogLevel(LOG_ALL);
  SetExitKey(KEY_Q);
  LogMessage("I passed this in");

  duck_sfx = LoadSound("res/duck.ogg");

  btn_play = button_new("Play", 400, 350, StartGame, PT_BLUE, PT_GRAY);
  btn_accept = button_new("Accept", 200, 400, AcceptDeal, PT_GREEN, PT_GRAY);
  btn_reject = button_new("Reject", 400, 400, RejectDeal, PT_RED, PT_GRAY);

  // opening_case_timer = CreateTimer();

  ResetGame();

  while (!WindowShouldClose()) {
    // mousePos = GetMousePosition();
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
  // UpdateTimer(opening_case_timer);
  if (case_timer < 90) {
    case_timer++;
  }
  if (case_timer >= 90) {
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
  is_case_opening = case_timer < 80;

  // Update each case
  for (int i = 0; i < NUM_CASES; i++) {
    if (cases[i]->interactable) {
      UpdateCase(cases[i], GetMousePosition());
    }
    // Make sure player can't keep clicking after opening case
    if (!is_case_opening) {
      if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && cases[i]->hovered) {
        // if (!is_case_opening) {
        if (player_case_num != 0) {
          // StartTimer(opening_case_timer, SHOW_CASE_VAULE_TIME);
        }
        PlayerPickCase(cases[i]);
        if (cases[i]->value == 1000000) {
          PlaySound(duck_sfx);
        }
        //}
      }
    }
  }
}

void UpdateBanner() {
  banner_x += 2;
  if (banner_x >= screenWidth) {
    banner_x = -MeasureText(bannerText, 38);
  }
}

void UpdateOffer() {
  UpdateBanner();
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
    // Calculate the row and column
    int row = i / NUM_COLS; // Integer division (gives row index)
    int col = i % NUM_COLS; // Modulo operation (gives column index)

    // Calculate the x and y positions based on row and column with gaps
    int x = 30 + (col * (CASE_WIDTH + CASE_GAP_X));
    int y = 80 + (row * (CASE_HEIGHT + CASE_GAP_Y));

    // Create a new case with the calculated position
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
  DrawText("Game Over", 350, 200, 30, PT_WHITE);
  DrawText("Press ENTER to Restart", 280, 300, 20, PT_WHITE);
}

void DrawTitleScreen() {
  DrawText("Accept or Reject", 300, 200, 40, PT_WHITE);
  button_draw(btn_play);
}

void DrawGame() {
  // if (opening_case_timer->TimeLeft <= 0) {
  if (case_timer < 90) {
    DrawOpenedCaseInfo();

  } else {
    DrawBanner();

    DrawLines();
    DrawDollarAmounts();
    // Draw all cases
    for (int i = 0; i < NUM_CASES; i++) {
      DrawCase(cases[i]);
    }
  }
}

// TODO: Rename to DrawMarqee
void DrawBanner() {
  DrawText(bannerText, banner_x, 4, BANNER_FONT_SIZE, PT_ORANGE);
}

void DrawLines() {
  DrawRectangleLinesEx((Rectangle){0, 0, screenWidth, 44}, 4.0f, PT_BLUE);
  DrawRectangleLinesEx((Rectangle){0, 0, screenWidth, screenHeight}, 4.0f,
                       PT_BLUE);
  DrawRectangleLinesEx((Rectangle){0, 40, screenWidth - 300, screenHeight},
                       4.0f, PT_BLUE);
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
    DrawText(TextFormat("Next Round\n %s",
                        pluralize_cases(CASES_PER_ROUND[game_round + 1])),
             10, 50, 30, PT_ORANGE);
  }
  DrawLines();
  DrawDollarAmounts();
  DrawText("Offer", 350, 200, 30, PT_WHITE);
  DrawLine(340, 220, 420, 220, PT_WHITE);
  DrawText(TextFormat("$ %d", GetOffer()), 350, 370, 30, PT_WHITE);
  button_draw(btn_accept);
  button_draw(btn_reject);
}

void DrawGameOver() {
  DrawText("Game Over", 350, 200, 30, PT_WHITE);
  DrawText("Press ENTER to Restart", 280, 300, 20, PT_WHITE);
}

void DrawOpenedCaseInfo() {
  DrawText(TextFormat("Case %d had", opened_case_num), 350, 200, 30, PT_WHITE);
  DrawText(TextFormat("$ %d", opened_case_value), 280, 300, 40, PT_WHITE);
}

void StartGame() {
  TraceLog(LOG_DEBUG, "Starting game");
  game_state = PICK_CASE;
}

void AcceptDeal() {
  TraceLog(LOG_DEBUG, "Player accepted the deal");
  wasOfferAccepted = true;
}
void RejectDeal() { TraceLog(LOG_DEBUG, "Player accepted the deal"); }

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

void DrawCaseValue(Case *c) {}

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
  UpdateBannerText(cases_to_pick);
  game_state = TITLE;
  wasOfferAccepted = false;
  player_case_num = 0;
  player_case_value = 0;
  memset(cases, 0, sizeof(cases));
  SetupCases();
  cases_to_pick = 7;
  game_round = 0;
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
}

void UpdateBannerText(int n_cases) {
  static char buffer[MAX_BANNER_LEN];

  // FIXME: Do better?
  if (n_cases == 99) {
    bannerText = "Banker's Offer";
    return;
  }

  if (player_case_num != 0) {
    if (n_cases > 1) {
      snprintf(buffer, sizeof(buffer), "PICK %d MORE CASES", n_cases);
    } else {
      snprintf(buffer, sizeof(buffer), "PICK %d CASE", n_cases);
    }
  } else {
    snprintf(buffer, sizeof(buffer), "Pick your case");
  }
  bannerText = buffer;
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
    // Draw the case with hover effect
    // Color current_col = c->hovered ? c->hover_col : c->col;
    if (c->selected) {
      DrawRectangleLinesEx(
          (Rectangle){c->position.x, c->position.y, CASE_WIDTH, CASE_HEIGHT}, 3,
          Fade(PT_BLUE, 0.5f));
      // Draw the number inside the case
      DrawText(TextFormat("%d", c->number), (int)c->txt_pos.x,
               (int)c->txt_pos.y, 30, Fade(PT_BLUE, 0.5f));
    } else {
      DrawRectangleLinesEx(
          (Rectangle){c->position.x, c->position.y, CASE_WIDTH, CASE_HEIGHT}, 3,
          c->hovered ? HOVER_COLOR : DEFAULT_COLOR);
      // Draw the number inside the case
      DrawText(TextFormat("%d", c->number), (int)c->txt_pos.x,
               (int)c->txt_pos.y, 30, c->hovered ? PT_WHITE : DEFAULT_COLOR);
    }
  }
}

void OpenCase(Case *c) {
  TraceLog(LOG_INFO, TextFormat("Case %d was opened", c->number));
  if (!c->selected) {
    case_timer = 0;
    UpdateCaseDisplay(c->number, c->value);
    Clamp(cases_to_pick--, 0, 10);
    UpdateBannerText(cases_to_pick);
    // TraceLog(LOG_DEBUG, TextFormat("Case %d was clicked! Value: %d",
    // c->number, c->value));
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

void GoToGameOver() {}