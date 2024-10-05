#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "Node.h"
#include "raylib/raylib.h"
#include <string>

class Player 
{
protected:
private:
    /* data */
    Texture2D texture; 
    Vector2 position; 
    int width;
    int height;
    float jumpForce;
    bool canJump;


public:
    Player();
    ~Player();
    void CleanUp();
    void Draw();
    void Update(float dt);
};

#endif