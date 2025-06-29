#ifndef MAIN_H
#define MAIN_H

#include "../include/raylib/raylib.h"
#include "../include/raylib/raymath.h"
#include <stdbool.h>
#include <stddef.h>

#define NUM_CASES 24
#define NUM_ROWS 4
#define NUM_COLS 6
#define CASE_GAP_X 10
#define CASE_GAP_Y 15
#define CASE_WIDTH 90
#define CASE_HEIGHT 60

#define OPEN_CASE_TIME 90

#define PT_BLUE (Color){41, 173, 255, 255}
#define PT_GRAY (Color){95, 87, 79, 255}
#define PT_ORANGE (Color){255, 136, 0, 255}
#define PT_GREEN (Color){0, 178, 81, 255}
#define PT_RED (Color){255, 0, 77, 255}

#define DEFAULT_COLOR (Color){88, 86, 85, 255}
#define HOVER_COLOR (Color){255, 163, 0, 255}
#define PT_WHITE (Color){255, 241, 232, 255}

#define SHOW_CASE_VAULE_TIME 1.0f
#define FPS 60
#define BANNER_FONT_SIZE 38
#define BANNER_SCROLL_SPEED 2
#define MAX_BANNER_LEN 64

typedef struct {
  int value;
  bool in_play;
} CaseValue;

// typedef struct Player {
//   int CaseNum;
//   int CaseVaule;
// } Player;

typedef struct {
  Rectangle rect;
  int number;
  int value;
  Vector2 position;
  bool hovered;
  bool picked;
  bool visible;
  bool interactable;
  bool opened;
  bool selected;
  int value_index;
  Vector2 txt_pos;
} Case;

Case *case_new(int number, int value, int x, int y);
void UpdateCase(Case *c, Vector2 mousePos);
void DrawCase(Case *c);
void OpenCase(Case *c);
void UpdateCaseDisplay(int case_num, int case_val);

void UpdateTitleScreen(void);
void UpdateGame(void);
void UpdateGameOver(void);
void UpdateOffer(void);

void PlayerPickCase(Case *c);

void DrawTitleScreen(void);
void DrawGame(void);
void DrawGameOver(void);
void DrawOffer(void);

void BackToMain(void);

void DrawCaseValue(Case *Case);
const char *pluralize_cases(int n);

void DrawDollarAmounts(void);
void DrawLines(void);

void StartGame(void);
void AcceptDeal(void);
void RejectDeal(void);
void ResetGame(void);
void SetupCases(void);

void AdvanceRound(void);
int GetOffer(void);

void UpdateBanner(void);
void DrawBanner(void);
void UpdateBannerText(int n_cases);

// void UpdateCaseDisplay(int case_num, int case_val);
void DrawOpenedCaseInfo(void);

void ShuffleCaseValues(int *array, size_t n);
Sound LoadSoundSafe(const char *filename);

void GoToGameOver(void);
void LogMessage(char str[]);

void CleanUp(void);

#endif // MAIN_H
