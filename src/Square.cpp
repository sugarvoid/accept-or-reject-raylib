#include "header/Square.h"
#include "raylib.h"
#include <iostream>

// Constructor
Square::Square(int centerX, int centerY, int size) {
    x = centerX;
    y = centerY;
    this->size = size;
}

// Destructor
Square::~Square() {
    // Destructor implementation (if needed)
}

// Setter functions
void Square::setCenterX(int centerX) {
    x = centerX;
}

void Square::setCenterY(int centerY) {
    y = centerY;
}

void Square::setSize(int size) {
    this->size = size;
}

// Getter functions
int Square::getCenterX()  {
    return x;
}

int Square::getCenterY()  {
    return y;
}

int Square::getSize()  {
    return size;
}

// Other member functions
void Square::draw() const {
    DrawRectangle(this->getCenterX, this->getCenterX, this->size, this->size, RED);
   // DrawRectangle(screenWidth/4*2 - 60, 100, 120, 60, RED);
    std::cout << "Square Center: (" << x << ", " << y << "), Size: " << size << std::endl;
}

