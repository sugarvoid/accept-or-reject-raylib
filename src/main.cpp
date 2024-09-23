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
    Square mySquare(0.0, 0.0, 5.0); // Center at (0,0) and size of 5.0

    // Realistic gravity is achieved by multiplying gravity by the length unit.

    // Use setter functions to modify the square's properties
    mySquare.setCenterX(2.0);
    mySquare.setCenterY(3.0);
    mySquare.setSize(8.0);

    // Display updated information about the square
}

int main(void)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(600, 600, "raylib [core] example - basic window");

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

    while (!WindowShouldClose())
    {

        // Begin drawing to the render texture (128x128)

        BeginTextureMode(target);

        ClearBackground(RAYWHITE);
        moPos = GetMousePosition();

        mySquare.update();
        mySquare.draw();
        mySprite.Draw();
        ClearBackground(Color({100, 149, 237, 255}));

        // Your game drawing logic here

        EndTextureMode();

        // Get the size of the actual window

        int windowWidth = GetScreenWidth();

        int windowHeight = GetScreenHeight();

        // Calculate the scaling factor while preserving the aspect ratio

        float scale = fminf((float)windowWidth / gameWidth, (float)windowHeight / gameHeight);

        int scaledWidth = (int)(gameWidth * scale);

        int scaledHeight = (int)(gameHeight * scale);

        int offsetX = (windowWidth - scaledWidth) / 2;

        int offsetY = (windowHeight - scaledHeight) / 2;

        // Begin drawing to the real window

        BeginDrawing();

        ClearBackground(BLACK); // Clear to black to avoid letterboxing artifacts

        // std::cout << "Mouse Position: (" << moPos.x << ", " << moPos.y << ")" << std::endl;

        // Draw the scaled 128x128 game texture to the window, preserving aspect ratio

        DrawTexturePro(target.texture,
                       (Rectangle){0, 0, (float)target.texture.width, -(float)target.texture.height}, // Flip vertically
                       (Rectangle){offsetX, offsetY, scaledWidth, scaledHeight},
                       (Vector2){0, 0}, 0.0f, WHITE);

        DrawFPS(0, 0);

        EndDrawing();
    }

    // Unload resources

    UnloadRenderTexture(target);

    UnloadImage(icon); // Needed if continuously loaded.
    CloseWindow();

    return 0;
}
