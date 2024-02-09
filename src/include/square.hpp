// square.h
#ifndef SQUARE_H
#define SQUARE_H

#include "raylib.h"

class Square
{
public:
    int x;    // x-coordinate of the square's center
    int y;    // y-coordinate of the square's center
    int size; // size of the square
    Color color;

    // Constructor
    Square(int centerX, int centerY, int size);

    // Destructor
    ~Square();

    void setCenterX(int centerX);
    void setCenterY(int centerY);
    void setSize(int size);
    void wasClicked();

    int getCenterX();
    int getCenterY();
    int getSize();

    //
    void draw();
};

#endif
