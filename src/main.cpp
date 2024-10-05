#include <string>
#include <iostream>
#include "../include/square.hpp"
#include "../include/Sprite.hpp"
#include "../include/raylib/raylib.h"
#include "../include/Node2d.h"
#include "../include/box2d/box2d.h"

const int gameWidth = 128;

const int gameHeight = 128;

void makeSquare()
{
    // Create a new square object using the constructor
    Square mySquare(0.0, 0.0, 8.0); 
    mySquare.setCenterX(2.0);
    mySquare.setCenterY(3.0);
    mySquare.setSize(8.0);

}

int main(void)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(600, 600, "raylib - basic window");

    SetTargetFPS(60);
    Image icon = LoadImage("raylib_logo.png");

    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity.y = 10.0f;
    b2WorldId worldId = b2CreateWorld(&worldDef);

    RenderTexture2D target = LoadRenderTexture(gameWidth, gameHeight);

    if (!icon.data)
    {
        std::cout << "Failed to load icon" << std::endl;
    }

    SetWindowIcon(icon);

    Node2D *player = new Node2D();
    std::cout << "Player Name: " << player->GetName() << std::endl;
    Square mySquare(0, 0, 8.0);
    Sprite mySprite;
    Vector2 moPos;
    Vector2 localMousePos; 


    // Store previous window size and scaling factors
    int prevWindowWidth = GetScreenWidth();
    int prevWindowHeight = GetScreenHeight();
    float scale = 1.0f;
    int scaledWidth = gameWidth;
    int scaledHeight = gameHeight;
    int offsetX = 0;
    int offsetY = 0;

    // Initial calculation of scaling factor
    scale = fminf((float)prevWindowWidth / gameWidth, (float)prevWindowHeight / gameHeight);
    scaledWidth = (int)(gameWidth * scale);
    scaledHeight = (int)(gameHeight * scale);
    offsetX = (prevWindowWidth - scaledWidth) / 2;
    offsetY = (prevWindowHeight - scaledHeight) / 2;

    while (!WindowShouldClose())
    {
        int currentWindowWidth = GetScreenWidth();
        int currentWindowHeight = GetScreenHeight();

        // Recalculate scaling only if the window size has changed
        if (currentWindowWidth != prevWindowWidth || currentWindowHeight != prevWindowHeight) {
            prevWindowWidth = currentWindowWidth;
            prevWindowHeight = currentWindowHeight;

            scale = fminf((float)currentWindowWidth / gameWidth, (float)currentWindowHeight / gameHeight);
            scaledWidth = (int)(gameWidth * scale);
            scaledHeight = (int)(gameHeight * scale);
            offsetX = (currentWindowWidth - scaledWidth) / 2;
            offsetY = (currentWindowHeight - scaledHeight) / 2;
        }

        // Begin drawing to the render texture (128x128)

        BeginTextureMode(target);

        //ClearBackground(SKYBLUE);
        ClearBackground(Color({100, 149, 237, 255}));
        moPos = GetMousePosition();
        localMousePos.x = (moPos.x - offsetX)/scale;
        localMousePos.y = (moPos.y - offsetY)/scale;

        mySquare.update();
        mySquare.draw();
        mySprite.Draw();

        //DrawText("FPS: ", 0, 0, 1, BLACK);
        

        // Your game drawing logic here

        EndTextureMode();

        

        // Begin drawing to the real window
        BeginDrawing();
        ClearBackground(BLACK); // Clear to black to avoid letterboxing artifacts
        // std::cout << "Mouse Position: (" << localMousePos.x << ", " << localMousePos.y << ")" << std::endl;
        // Draw the scaled 128x128 game texture to the window, preserving aspect ratio
        DrawTexturePro(target.texture,
                       (Rectangle){0, 0, (float)target.texture.width, -(float)target.texture.height}, // Flip vertically
                       (Rectangle){offsetX, offsetY, scaledWidth, scaledHeight},
                       (Vector2){0, 0}, 0.0f, WHITE);

        DrawFPS(offsetX, offsetY);
        EndDrawing();
    }

    // Unload resources
    UnloadRenderTexture(target);
    UnloadImage(icon);
    CloseWindow();

    return 0;
}
