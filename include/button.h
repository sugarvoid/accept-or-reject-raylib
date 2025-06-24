#ifndef BUTTON_H
#define BUTTON_H

#include "../include/raylib/raylib.h"
#include "../include/rect_object.h"
#include <stdbool.h>

typedef struct {
  RectObject rect;
  char *text;         // Button text
  int x, y;           // Position (x, y)
  int w, h;           // Width and height
  void (*callback)(); // Callback function when button is clicked
  Color col;          // Button color
  bool is_hovered;    // Is the button hovered by the mouse
  Color txt_col;      // Text color
  Vector2 textSize;
  Vector2 textPosition;
} Button;

// Function prototypes
Button *button_new(char *text, int x, int y, void (*callback)(), Color col);
void button_update(Button *btn, Vector2 mousePos);
void button_was_clicked(Button *btn);
void button_draw(Button *btn);

#endif // BUTTON_H
