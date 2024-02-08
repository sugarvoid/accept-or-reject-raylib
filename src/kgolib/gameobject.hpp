#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "raylib.h"

class GameObject
{
public:
    int x; // x-coordinate of the square's center
    int y; // y-coordinate of the square's center

    // Constructor
    GameObject();

    // Destructor
    ~GameObject();

    //
    virtual void draw();
};

#endif