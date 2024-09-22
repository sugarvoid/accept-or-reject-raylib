#include "../include/Node.h"
#include <string>
#include <iostream>

Node::Node()
    : name("Default")
{ 
    this->scale.x = 1; 
    this->scale.y = 1; 
    this->position.x = 0;
    this->position.y = 0;
}

Node::~Node()
{
    std::cout << this << " was deleted" << std::endl;
}

std::string Node::GetName() {
    return this->name;
}