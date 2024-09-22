
// square.h
#ifndef SQUARE_H
#define SQUARE_H

#include "raylib/raylib.h"
#include "raylib/raymath.h"

typedef struct square
{
    /* data */
    Vector2 position; 
    Color color;
} Square;




Square MakeSquare(float x, float y, Color color);
void UpdateSquare(Square *square);
void DrawSquare(Square *square);
void UnloadSquare(Square square);

#endif