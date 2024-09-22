#include <string>
#include <iostream>
#include "../include/square.hpp"
#include "../include/Sprite.hpp"
#include "../include/raylib/raylib.h"
#include "../include/Node2d.h"
#include "../include/box2d/box2d.h"

void makeSquare()
{
    // Create a new square object using the constructor
    Square mySquare(0.0, 0.0, 5.0); // Center at (0,0) and size of 5.0

    // Realistic gravity is achieved by multiplying gravity by the length unit.
	
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity.y = 10.0f;
	b2WorldId worldId = b2CreateWorld(&worldDef);
    // Use setter functions to modify the square's properties
    mySquare.setCenterX(2.0);
    mySquare.setCenterY(3.0);
    mySquare.setSize(8.0);

    // Display updated information about the square
}

int main(void)
{
    InitWindow(600, 600, "raylib [core] example - basic window");
    SetTargetFPS(60);
    Image icon = LoadImage("raylib_logo.png");

    if (!icon.data)
    {
        std::cout << "Failed to load icon" << std::endl;
    }

    SetWindowIcon(icon);

    Node2D player; 

    std::cout << "Test Node2d " << player.GetName() << std::endl;

    Square mySquare(40.0, 40.0, 64.0);
    Sprite mySprite;
    Vector2 moPos;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        moPos = GetMousePosition();
        DrawFPS(0, 0);

        

        mySquare.update();
        mySquare.draw();
        mySprite.Draw();
        ClearBackground(Color({100, 149, 237, 255}));

        // std::cout << "Mouse Position: (" << moPos.x << ", " << moPos.y << ")" << std::endl;

        EndDrawing();
    }

    UnloadImage(icon); // Needed if continuously loaded.
    CloseWindow();

    return 0;
}
