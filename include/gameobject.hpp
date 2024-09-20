#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "../include/raylib.h"

class GameObject
{
public:
    Vector2 position;
    int x; // x-coordinate of the square's center
    int y; // y-coordinate of the square's center
    int size;
    Color color;

    // Constructor
    GameObject(int centerX, int centerY, int size);

    // Destructor
    ~GameObject();

    //
    virtual void draw();
};

#endif