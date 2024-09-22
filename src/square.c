
#include "../include//raylib/raylib.h"
#include "../include/square.h"


Square MakeSquare(float x, float y, Color color){
    Square new_sq;
    new_sq.position.x = x;
    new_sq.position.y = y;
    new_sq.color = color;
    return new_sq;

}
void UpdateSquare(Square *square){

}
void DrawSquare(Square *square){
    DrawRectangle(square->position.x, square->position.y, 100, 100, square->color);

}
void UnloadSquare(Square square){

}