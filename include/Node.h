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

    std::string GetName();


protected:
    Vector2 position;
    std::string name;
};



#endif