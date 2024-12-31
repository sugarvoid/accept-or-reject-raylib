#ifndef BULLET_H
#define BULLET_H

#include "raylib/raylib.h"

typedef struct Bullet {
  Vector2 position;
  Vector2 targetPosition;
  Texture2D texture;
  int width;
  int height;
  float speed;
} Bullet;

Bullet Create_Bullet();
void Bullet_Destroy(Bullet *b);
void Bullet_CleanUp(Bullet *b);
void Bullet_Draw(const Bullet *b);
void Bullet_Update(Bullet *b, float dt);

#endif // BULLET_H