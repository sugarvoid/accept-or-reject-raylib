
// square.h
#ifndef PLAYER_H
#define PLAYER_H

#include "raylib/raylib.h"
#include "raylib/raymath.h"

typedef struct player
{
    Vector2 position; 
    Texture2D texture;
} Player;




Player MakePlayer();
void UpdatePlayer(Player *player);
void DrawPlayer(Player *player);
void UnloadPlayer(Player player);

#endif