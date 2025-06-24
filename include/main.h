#ifndef MAIN_H
#define MAIN_H

#include "../include/case.h"
#include "../include/player.h"
#include "../include/raylib/raylib.h"
#include "../include/raylib/raymath.h"
#include <stdbool.h>
#include <stddef.h>

#define MAX_COLORS_COUNT 23 // Number of colors available
#define NUM_CASES 24        // Example number of cases
#define NUM_ROWS 4
#define NUM_COLS 6
// #define CASE_WIDTH 100
// #define CASE_HEIGHT 50
#define GAP_X 10 // Horizontal gap between cases
#define GAP_Y 15 // Vertical gap between rows and above
#define TEXT_BLUE (Color){41, 173, 255, 255}
#define TEXT_GRAY (Color){95, 87, 79, 255}

void UpdateTitleScreen(void);
void UpdateGame(void);
void UpdateGameOver(void);

void DrawTitleScreen(void);
void DrawGame(void);
void DrawGameOver(void);

void DrawCaseValue(Case *Case);
const char *pluralize_cases(int n);

void StartGame(void);
void AcceptDeal(void);
void RejectDeal(void);

void ShuffleCaseValues(int *array, size_t n);
Sound LoadSoundSafe(const char *filename);
void CleanUp(void);

#endif // MAIN_H
