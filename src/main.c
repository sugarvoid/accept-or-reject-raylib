
//#include "../include/square.hpp"

#include "../include/raylib/raylib.h"
#include <stdio.h>

#include "../include/square.h"

#include "../include/box2d/box2d.h"

void makeSquare()
{
    // // Create a new square object using the constructor
    // Square mySquare(0.0, 0.0, 5.0); // Center at (0,0) and size of 5.0

    // // Use setter functions to modify the square's properties
    // mySquare.setCenterX(2.0);
    // mySquare.setCenterY(3.0);
    // mySquare.setSize(8.0);

    // // Display updated information about the square
}

int main(void)
{
    InitWindow(600, 600, "raylib [core] example - basic window");
    SetTargetFPS(60);
    Image icon = LoadImage("raylib_logo.png");
    b2WorldDef worldDef = b2DefaultWorldDef();

    Square test_s = MakeSquare(30, 30, RED);

    if (!icon.data)
    {
        //std::cout << "Failed to load icon" << std::endl;
        printf("Failed to load icon");
    }

    SetWindowIcon(icon);



    //std::cout << "Test Node2d " << player.GetName() << std::endl;

 
    Vector2 moPos;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        moPos = GetMousePosition();
        DrawFPS(0, 0);

        DrawSquare(&test_s);
        ClearBackground(RAYWHITE);


        // std::cout << "Mouse Position: (" << moPos.x << ", " << moPos.y << ")" << std::endl;

        EndDrawing();
    }

    UnloadImage(icon); // Needed if continuously loaded.
    CloseWindow();

    return 0;
}
