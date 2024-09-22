#pragma once
#ifndef NODE_H
#define NODE_H

#include <vector>
#include "raylib/raylib.h"
#include <string>

class Node
{
public:
    Node();
    ~Node();

    std::string GetName();


protected:
    Vector2 position;
    float rotation; 
    Vector2 scale; 
    std::string name;
};



#endif