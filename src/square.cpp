#include "../include/square.hpp"
#include <iostream>



// Constructor
Square::Square(int centerX, int centerY, int size)
{
    x = centerX;
    y = centerY;
    this->size = size;
    this->color = GREEN;
    this->position.x = 0;
}

// Destructor
Square::~Square()
{
    // Destructor implementation (if needed)
    std::cout << "Square was deleted" << std::endl;
}

// Setter functions
void Square::setCenterX(int centerX)
{
    x = centerX;
}

void Square::setCenterY(int centerY)
{
    y = centerY;
}

void Square::setSize(int size)
{
    this->size = size;
}

// Getter functions
int Square::getCenterX()
{
    return x;
}

int Square::getCenterY()
{
    return y;
}

int Square::getSize()
{
    return size;
}

// Other member functions
void Square::draw()
{
    DrawRectangle(this->x, this->y, this->size, this->size, this->color);
    // DrawRectangle(screenWidth/4*2 - 60, 100, 120, 60, RED);
}

void Square::update()
{   
    //std::cout << "updating" << std::endl;
    if (IsKeyDown(KEY_RIGHT)) this->x += 2.0f;
    if (IsKeyDown(KEY_LEFT)) this->x -= 2.0f;
    if (IsKeyDown(KEY_UP)) this->y -= 2.0f;
    if (IsKeyDown(KEY_DOWN)) this->y += 2.0f;
}

void wasClicked()
{
    std::cout << "Square was clicked" << std::endl;
}

Vector2 Square::GetPosition()
{
    return this->position;
}
