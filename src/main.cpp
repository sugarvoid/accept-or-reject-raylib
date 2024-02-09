#include <string>
#include <iostream>
#include "include/square.hpp"
#include "raylib.h"

void makeSquare()
{
    // Create a new square object using the constructor
    Square mySquare(0.0, 0.0, 5.0); // Center at (0,0) and size of 5.0

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
    Square mySquare(40.0, 40.0, 64.0);
    Vector2 moPos;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        moPos = GetMousePosition();
        DrawFPS(0, 0);

        mySquare.draw();
        ClearBackground(Color({100, 149, 237, 255}));

        std::cout << "Mouse Position: (" << moPos.x << ", " << moPos.y << ")" << std::endl;

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
