#ifndef BUTTON_H
#define BUTTON_H

#include "../include/raylib/raylib.h"
#include <stdbool.h>

#define FONT_SPACING 1

typedef struct {
  Rectangle rect;
  char *text;
  int x;
  int y;
  int w;
  int h;
  int font_size;
  void (*callback)();
  Color col;
  
  Color hovered_col;
  bool is_hovered;
  Color txt_col;
  Vector2 textSize;
  Vector2 textPosition;
} Button;

Button *button_new(char *text, int x, int y, void (*callback)(), Color col, Color hovered_col);
void button_update(Button *btn, Vector2 mousePos);
void button_was_clicked(Button *btn);
void button_draw(Button *btn);

#endif // BUTTON_H
