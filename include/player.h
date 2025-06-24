#ifndef PLAYER_H
#define PLAYER_H

#include "../include/case.h"
#include "raylib/raylib.h"

typedef struct Player {
  int CaseNum;
  int CaseVaule;
} Player;

void PlayerPickCase(Player *p, Case *c);

Player Player_Create();
void Player_Destroy(Player *p);
void Player_CleanUp(Player *p);
void Player_Draw(const Player *p);
void Player_Update(Player *p, float dt);

#endif // PLAYER_H
