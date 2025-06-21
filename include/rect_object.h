// rect_object.h

#ifndef RECT_OBJECT_H
#define RECT_OBJECT_H

#include "../include/raylib/raylib.h"

typedef struct {
    int x, y, w, h;
} RectObject;


bool is_mouse_colliding(Vector2 mousePos, RectObject* obj);

#endif // RECT_OBJECT_H
