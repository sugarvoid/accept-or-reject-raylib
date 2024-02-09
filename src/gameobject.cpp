#include "include/gameobject.hpp"
#include "raylib.h"
#include <iostream>

// Constructor
GameObject::GameObject(int centerX, int centerY, int size)
{
    x = centerX;
    y = centerY;
    this->size = size;
    this->color = GOLD;
}

// Destructor
GameObject::~GameObject()
{
    // Destructor implementation (if needed)
}

// Other member functions
void GameObject::draw()
{
}
