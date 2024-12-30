// // #include <string.h> // For string manipulation (e.g., strcpy, strlen)
// #include <stdio.h> // For input/output (e.g., printf, scanf)

// #include "../include/player.h"
// #include "../include/raylib/raylib.h"
// // #include "../include/raylib/raymath.h"
// #include "math.h"

// // #include "../include/box2d/box2d.h"

// const int gameWidth = 128;
// const int gameHeight = 128;

// int main(void) {
//   SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
//   InitWindow(600, 600, "raylib - basic window");

//   Camera2D camera = {0};
//   camera.target = (Vector2){20.0f, 20.0f};
//   camera.offset = (Vector2){400 / 2.0f, 400 / 2.0f};
//   camera.rotation = 0.0f;
//   camera.zoom = 1.0f;

//   SetTargetFPS(60);
//   Image icon = LoadImage("raylib_logo.png");

//   // b2WorldDef worldDef = b2DefaultWorldDef();
//   // worldDef.gravity.y = 10.0f;
//   // b2WorldId worldId = b2CreateWorld(&worldDef);

//   RenderTexture2D target = LoadRenderTexture(gameWidth, gameHeight);

//   if (!icon.data) {
//     printf("Failed to load icon");
//   }

//   SetWindowIcon(icon);

//   // Player player;
//   Player player = Player_Create();
//   // std::cout << "Player Name: " << player->GetName() << std::endl;
//   Vector2 moPos;
//   Vector2 localMousePos;

//   // Store previous window size and scaling factors
//   int prevWindowWidth = GetScreenWidth();
//   int prevWindowHeight = GetScreenHeight();
//   float scale = 1.0f;
//   int scaledWidth = gameWidth;
//   int scaledHeight = gameHeight;
//   int offsetX = 0;
//   int offsetY = 0;

//   // Initial calculation of scaling factor
//   scale = fminf((float)prevWindowWidth / gameWidth,
//                 (float)prevWindowHeight / gameHeight);
//   scaledWidth = (int)(gameWidth * scale);
//   scaledHeight = (int)(gameHeight * scale);
//   offsetX = (prevWindowWidth - scaledWidth) / 2;
//   offsetY = (prevWindowHeight - scaledHeight) / 2;

//   while (!WindowShouldClose()) {
//     int currentWindowWidth = GetScreenWidth();
//     int currentWindowHeight = GetScreenHeight();

//     // Recalculate scaling only if the window size has changed
//     if (currentWindowWidth != prevWindowWidth ||
//         currentWindowHeight != prevWindowHeight) {
//       prevWindowWidth = currentWindowWidth;
//       prevWindowHeight = currentWindowHeight;

//       scale = fminf((float)currentWindowWidth / gameWidth,
//                     (float)currentWindowHeight / gameHeight);
//       scaledWidth = (int)(gameWidth * scale);
//       scaledHeight = (int)(gameHeight * scale);
//       offsetX = (currentWindowWidth - scaledWidth) / 2;
//       offsetY = (currentWindowHeight - scaledHeight) / 2;
//     }

//     // Begin drawing to the render texture (128x128)

//     BeginTextureMode(target);

//     // ClearBackground(BLACK);
//     // ClearBackground(Color({100, 149, 237, 255}));
//     ClearBackground(DARKGREEN);
//     moPos = GetMousePosition();
//     localMousePos.x = (moPos.x - offsetX) / scale;
//     localMousePos.y = (moPos.y - offsetY) / scale;

//     // player.Draw();
//     Player_Draw(&player);
//     Player_Update(&player, GetTime());
//     // player.Update(GetTime());

//     // DrawText("FPS: ", 0, 0, 1, BLACK);

//     // Your game drawing logic here

//     EndTextureMode();

//     // Begin drawing to the real window
//     BeginDrawing();
//     ClearBackground(BLACK); // Clear to black to avoid letterboxing artifacts
//     // std::cout << "Mouse Position: (" << localMousePos.x << ", " <<
//     // localMousePos.y << ")" << std::endl; Draw the scaled 128x128 game
//     texture
//     // to the window, preserving aspect ratio
//     DrawTexturePro(
//         target.texture,
//         (Rectangle){0, 0, (float)target.texture.width,
//                     -(float)target.texture.height}, // Flip vertically
//         (Rectangle){(float)offsetX, (float)offsetY, (float)scaledWidth,
//                     (float)scaledHeight},
//         (Vector2){0, 0}, 0.0f, WHITE);

//     DrawFPS(offsetX, offsetY);
//     EndDrawing();
//   }

//   // Unload resources
//   Player_CleanUp(&player);
//   UnloadRenderTexture(target);
//   UnloadImage(icon);
//   CloseWindow();

//   return 0;
// }

/*******************************************************************************************
 *
 *   raylib [textures] example - Bunnymark
 *
 *   Example originally created with raylib 1.6, last time updated with
 *raylib 2.5
 *
 *   Example licensed under an unmodified zlib/libpng license, which is an
 *OSI-certified, BSD-like license that allows static linking with closed source
 *software
 *
 *   Copyright (c) 2014-2024 Ramon Santamaria (@raysan5)
 *
 ********************************************************************************************/

#include "../include/raylib/raylib.h"
// // #include "../include/raylib/raymath.h"

#include <stdlib.h> // Required for: malloc(), free()

#define MAX_BUNNIES 50000 // 50K bunnies limit

// This is the maximum amount of elements (quads) per batch
// NOTE: This value is defined in [rlgl] module and can be changed there
#define MAX_BATCH_ELEMENTS 8192

typedef struct Bunny {
  Vector2 position;
  Vector2 speed;
  Color color;
} Bunny;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void) {
  // Initialization
  //--------------------------------------------------------------------------------------
  const int screenWidth = 800;
  const int screenHeight = 800;

  InitWindow(screenWidth, screenHeight,
             "raylib [textures] example - bunnymark");

  // Load bunny texture
  Texture2D texBunny = LoadTexture("res/wabbit_alpha.png");

  Bunny *bunnies =
      (Bunny *)malloc(MAX_BUNNIES * sizeof(Bunny)); // Bunnies array

  int bunniesCount = 0; // Bunnies counter

  SetTargetFPS(60); // Set our game to run at 60 frames-per-second
  //--------------------------------------------------------------------------------------

  // Main game loop
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    // Update
    //----------------------------------------------------------------------------------
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
      // Create more bunnies
      for (int i = 0; i < 100; i++) {
        if (bunniesCount < MAX_BUNNIES) {
          bunnies[bunniesCount].position = GetMousePosition();
          bunnies[bunniesCount].speed.x =
              (float)GetRandomValue(-250, 250) / 60.0f;
          bunnies[bunniesCount].speed.y =
              (float)GetRandomValue(-250, 250) / 60.0f;
          bunnies[bunniesCount].color =
              (Color){GetRandomValue(50, 240), GetRandomValue(80, 240),
                      GetRandomValue(100, 240), 255};
          bunniesCount++;
        }
      }
    }

    // Update bunnies
    for (int i = 0; i < bunniesCount; i++) {
      bunnies[i].position.x += bunnies[i].speed.x;
      bunnies[i].position.y += bunnies[i].speed.y;

      if (((bunnies[i].position.x + texBunny.width / 2) > GetScreenWidth()) ||
          ((bunnies[i].position.x + texBunny.width / 2) < 0))
        bunnies[i].speed.x *= -1;
      if (((bunnies[i].position.y + texBunny.height / 2) > GetScreenHeight()) ||
          ((bunnies[i].position.y + texBunny.height / 2 - 40) < 0))
        bunnies[i].speed.y *= -1;
    }
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

    ClearBackground(RAYWHITE);

    for (int i = 0; i < bunniesCount; i++) {
      // NOTE: When internal batch buffer limit is reached (MAX_BATCH_ELEMENTS),
      // a draw call is launched and buffer starts being filled again;
      // before issuing a draw call, updated vertex data from internal CPU
      // buffer is send to GPU... Process of sending data is costly and it could
      // happen that GPU data has not been completely processed for drawing
      // while new data is tried to be sent (updating current in-use buffers) it
      // could generates a stall and consequently a frame drop, limiting the
      // number of drawn bunnies
      DrawTexture(texBunny, (int)bunnies[i].position.x,
                  (int)bunnies[i].position.y, bunnies[i].color);
    }

    DrawRectangle(0, 0, screenWidth, 40, BLACK);
    DrawText(TextFormat("bunnies: %i", bunniesCount), 120, 10, 20, GREEN);
    DrawText(TextFormat("batched draw calls: %i",
                        1 + bunniesCount / MAX_BATCH_ELEMENTS),
             320, 10, 20, MAROON);

    DrawFPS(10, 10);

    EndDrawing();
    //----------------------------------------------------------------------------------
  }

  // De-Initialization
  //--------------------------------------------------------------------------------------
  free(bunnies); // Unload bunnies data array

  UnloadTexture(texBunny); // Unload bunny texture

  CloseWindow(); // Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  return 0;
}