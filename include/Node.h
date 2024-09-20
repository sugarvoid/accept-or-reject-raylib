#pragma once
#ifndef NODE_H
#define NODE_H

#include <vector>
#include "../include/raymath.h"
#include <string>

class Node
{
public:
    Node();
    ~Node();

    char* GetName();


protected:
    Vector2 position;
    float rotation; 
    Vector2 scale; 
    char* name;
};



#endif