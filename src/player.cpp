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
    this->width = 8;
    this->height = 8;

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
    //DrawTexture(this->texture, this->position.x, this->position.y, WHITE);
    DrawRectangle(this->position.x, this->position.y, 8, 8, RAYWHITE);

    // DrawTexture(this->texture, this->position.x - this->texture.width/2, this->position.y- this->texture.height/2, WHITE);
}
void Player::Update(float dt)
{
    // std::cout << "updating" << std::endl;
    if (IsKeyDown(KEY_D))
        this->position.x += 1.0f;
    if (IsKeyDown(KEY_A))
        this->position.x -= 1.0f;
    if (IsKeyDown(KEY_W))
        this->position.y -= 1.0f;
    if (IsKeyDown(KEY_S))
        this->position.y += 1.0f;

    if (IsKeyDown(KEY_RIGHT))
        TraceLog(LOG_INFO, "Shoot Right");
    if (IsKeyDown(KEY_LEFT))
        TraceLog(LOG_INFO, "Shoot Left");
    if (IsKeyDown(KEY_UP))
        TraceLog(LOG_INFO, "Shoot Up");
    if (IsKeyDown(KEY_DOWN))
        TraceLog(LOG_INFO, "Shoot Down");

    if (IsKeyPressed(KEY_Z))
    {
        TraceLog(LOG_INFO, "Pressed Z");
        
    }

    if (IsKeyPressed(KEY_X))
    {
        TraceLog(LOG_INFO, "Pressed X");
    }

    
}