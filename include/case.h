#ifndef CASE_H
#define CASE_H

#include "../include/raylib/raylib.h"

#define DEFAULT_COLOR (Color){88, 86, 85, 255}

#define HOVER_COLOR (Color){255, 163, 0, 255}
#define OFF_WHITE (Color){255, 241, 232, 255}

#define CASE_WIDTH 90
#define CASE_HEIGHT 60

typedef struct {
  Rectangle rect;
  int number;
  int value;
  Vector2 position;
  // int w;
  // int h;
  bool hovered;
  bool picked;
  bool visible;
  bool interactable;
  bool opened;
  bool selected;
  int value_index;
  Vector2 txt_pos;
} Case;

// Function prototypes
Case *case_new(int number, int value, int x, int y);
void UpdateCase(Case *c, Vector2 mousePos);
void DrawCase(Case *c);
void OnCaseClick(Case *c);
void OpenCase(Case *c);
void UpdateCaseDisplay(int case_num, int case_val);

#endif // CASE_H
