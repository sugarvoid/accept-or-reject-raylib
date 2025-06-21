#ifndef CASE_H
#define CASE_H

#include "../include/raylib/raylib.h"
#include "../include/rect_object.h"


#define DEFAULT_COLOR (Color){ 88, 86, 85, 255 } 

#define HOVER_COLOR (Color){ 129, 224, 218, 255 } 

typedef struct {
    Rectangle rect;
    int number;
    int value;
    Vector2 position;
    int x, y;       // Position of the case
    int w, h;       // Width and height of the case
    bool hovered;   // If the mouse is hovering over the case
    bool picked;    // If the case has been selected
    bool visible;   // If the case is visible or hidden
    bool opened;
    Vector2 txt_pos; // Position of the text inside the case
    int move_t;      // Animation duration for case movement (optional)
    Vector2 end_loc; // End location (optional for animation)
} Case;

// Function prototypes
Case* case_new(int number, int value, int x, int y);
void case_update(Case* c, Vector2 mousePos);
void case_draw(Case* c);
void case_was_clicked(Case* c);

#endif // CASE_H
