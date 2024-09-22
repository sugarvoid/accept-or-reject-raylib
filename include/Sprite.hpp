#ifndef SPRITE_H
#define SPRITE_H

#include "raylib/raylib.h"
#include "../include/Node2d.h"

class Sprite : Node2D
{
protected:
    int frames;
    int frame;
public:
    // Constructor
    Sprite();

    // Destructor
    ~Sprite();

    void Draw();
    void GoToFrame(int newFrame);
};

#endif
