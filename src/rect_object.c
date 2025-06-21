// rect_object.c
#include "../include/rect_object.h"
#include "../include/raylib/raylib.h"

// Function to check if a mouse position is colliding with a rectangular object
bool is_mouse_colliding(Vector2 mousePos, RectObject* obj) {
    if (mousePos.x < obj->x + obj->w && mousePos.x > obj->x &&
        mousePos.y < obj->y + obj->h && mousePos.y > obj->y) {
        return true;
    }
    return false;
}
