#include "../include/Node.h"
#include <string>

Node::Node(/* args */)
{
    this->position.x = 0;
    this->position.y = 0;
}

Node::~Node()
{
    
}

std::string Node::GetName() {
    return this->name;
}