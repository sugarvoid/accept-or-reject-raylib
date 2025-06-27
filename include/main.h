#ifndef MAIN_H
#define MAIN_H


#include "../include/raylib/raylib.h"
#include "../include/raylib/raymath.h"
#include <stdbool.h>
#include <stddef.h>

#define NUM_CASES 24

#define TEXT_BLUE (Color){41, 173, 255, 255}
#define TEXT_GRAY (Color){95, 87, 79, 255}
#define TEXT_ORANGE (Color){255, 136, 0, 255}

#define PT_GREEN (Color){0, 178, 81, 255}
#define PT_RED (Color){255, 0, 77, 255}

typedef struct {
  int value;
  bool in_play;
} CaseValue;

typedef struct Player {
  int CaseNum;
  int CaseVaule;
} Player;


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

#define MAX_COLORS_COUNT 23 // Number of colors available
#define NUM_CASES 24        // Example number of cases
#define NUM_ROWS 4
#define NUM_COLS 6
// #define CASE_WIDTH 100
// #define CASE_HEIGHT 50
#define GAP_X 10 // Horizontal gap between cases
#define GAP_Y 15 // Vertical gap between rows and above

#define DEFAULT_COLOR (Color){88, 86, 85, 255}

#define HOVER_COLOR (Color){255, 163, 0, 255}
#define OFF_WHITE (Color){255, 241, 232, 255}

#define CASE_WIDTH 90
#define CASE_HEIGHT 60



Case *case_new(int number, int value, int x, int y);
void UpdateCase(Case *c, Vector2 mousePos);
void DrawCase(Case *c);
void OpenCase(Case *c);
void UpdateCaseDisplay(int case_num, int case_val);

void UpdateTitleScreen(void);
void UpdateGame(void);
void UpdateGameOver(void);

void PlayerPickCase(Player *p, Case *c);

void DrawTitleScreen(void);
void DrawGame(void);
void DrawGameOver(void);

void DrawCaseValue(Case *Case);
const char *pluralize_cases(int n);

void StartGame(void);
void AcceptDeal(void);
void RejectDeal(void);
void ResetGame(void);
void SetupCases(void);

void AdvanceRound(void);
int GetOffer(void);
void UpdateBannerText(int n_cases);

// void UpdateCaseDisplay(int case_num, int case_val);
void DrawOpenedCaseInfo();

void ShuffleCaseValues(int *array, size_t n);
Sound LoadSoundSafe(const char *filename);

void GoToGameOver(Player *p);
void LogSomething(char str[]);

void CleanUp(void);

#endif // MAIN_H
