#ifndef PLAYER_H
#define PLAYER_H

#include "raylib/raylib.h"

typedef struct Player
{
  Texture2D texture;
  Vector2 position;
  int width;
  int health;
  int height;
  float speed;
  bool isShooting;
} Player;

Player Player_Create();
void Player_Destroy(Player *p);
void Player_CleanUp(Player *p);
void Player_Draw(const Player *p);
void Player_Update(Player *p, float dt);

#endif // PLAYER_H
