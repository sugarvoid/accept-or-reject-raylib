#pragma once
#ifndef INPUT_H
#define INPUT_H

#include <vector>
#include "raylib/raylib.h"
#include <string>

static Input
{
public:
    Input();
    ~Input();

    static Vector2 localMousePos;
    std::string GetName();


protected:
    Vector2 position;
    float rotation; 
    Vector2 scale; 
    std::string name;
};



#endif