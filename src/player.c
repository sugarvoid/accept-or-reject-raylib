#include "../include/player.h"
#include <stdio.h>

Player Player_Create()
{
    Player p;

    p.texture = LoadTexture("./res/run1.png");
    if (p.texture.id == 0)
    {
        TraceLog(LOG_ERROR, "Failed to load player.png");
    }

    p.position = (Vector2){50, 50};
    p.width = 8;
    p.height = 8;
    p.isShooting = false; // 0; // false
    return p;
}

void Player_CleanUp(Player *p)
{
    if (p->texture.id > 0)
    {
        printf("unload texture\n");
        UnloadTexture(p->texture);
    }
    else
    {
        printf("Invalid texture\n");
    }
}

void Player_Destroy(Player *p)
{
    Player_CleanUp(p);
}

void Player_Draw(const Player *p)
{
    DrawRectangle(p->position.x, p->position.y, p->width, p->height, RAYWHITE);
}

void Player_Update(Player *p, float dt)
{
    // Movement controls
    if (IsKeyDown(KEY_D))
        p->position.x += 1.0f;
    if (IsKeyDown(KEY_A))
        p->position.x -= 1.0f;
    if (IsKeyDown(KEY_W))
        p->position.y -= 1.0f;
    if (IsKeyDown(KEY_S))
        p->position.y += 1.0f;

    // Shooting directions
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
