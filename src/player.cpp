#include "../include/player.h"
#include <iostream>

Player::Player()
{
    this->texture = LoadTexture("./res/run1.png");
    if (this->texture.id == 0)
    {
        TraceLog(LOG_ERROR, "Failed to load player.png");
    }
    this->position = (Vector2){50, 50};
    this->canJump = true;
    this->width = 16;
    this->height = 16;
    this->jumpForce = 0.0f;
}

void Player::CleanUp()
{
    if (this->texture.id > 0)
    {
        std::cout << "unload texture" << std::endl;
        UnloadTexture(this->texture);
    }
    else
    {
        std::cout << "Invalid texture" << std::endl;
    }
}

Player::~Player()
{

    // std::cout << "Player was deleted" << std::endl;
    // UnloadTexture(this->texture);
    // std::cout << "Player was deleted 2222" << std::endl;
}

void Player::Draw()
{
    DrawTexture(this->texture, this->position.x, this->position.y, WHITE);
    // DrawTexture(this->texture, this->position.x - this->texture.width/2, this->position.y- this->texture.height/2, WHITE);
}
void Player::Update(float dt)
{
    // std::cout << "updating" << std::endl;
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
        this->position.x += 1.0f;
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
        this->position.x -= 1.0f;
    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
        this->position.y -= 1.0f;
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
        this->position.y += 1.0f;

    if (IsKeyPressed(KEY_Z) && this->canJump)
    {
        TraceLog(LOG_INFO, "Pressed Z");
        this->canJump = false;
        this->jumpForce = -1.0f;
    }

    if (IsKeyPressed(KEY_X))
    {
        TraceLog(LOG_INFO, "Pressed X");
    }

    if (this->canJump == false)
    {
        // Here we update the player y position.
        // We want to move 1 pixel at a time. This for collision detection(Not going through tiles.)
        for (int i = 0; i < abs((int)this->jumpForce); i++)
        {
            // If we are still jumping then update the position.
            if (this->canJump == false)
                this->position.y += this->jumpForce;
            // if we touch the ground then reset out position and set canjump to true.
            if (this->position.y < 10.0f)
            {
                this->position.y = 10.0f;
                this->canJump = true;
                break;
            }
        }
        // Here we add to the jumpforce. It will go from - to +.
        this->jumpForce += 0.2f;
    }
}