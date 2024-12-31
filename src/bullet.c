#include "../include/bullet.h"
#include <stdio.h>

Bullet Create_Bullet()
{
    Bullet b;

    b.texture = LoadTexture("./res/run1.png");
    if (b.texture.id == 0)
    {
        TraceLog(LOG_ERROR, "Failed to load Bullet.png");
    }

    b.position = (Vector2){50, 50};
    b.speed = 200.0f;
    b.width = 20;
    b.height = 20;

    return b;
}

void Bullet_CleanUp(Bullet *b)
{
    
}

void Bullet_Destroy(Bullet *b)
{
    Bullet_CleanUp(b);
}

void Bullet_Draw(const Bullet *b)
{
    DrawCircle(b->position.x, b->position.y, 3, LIGHTGRAY);
    
}

void Bullet_Update(Bullet *b, float dt)
{

}
