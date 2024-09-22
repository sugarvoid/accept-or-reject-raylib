
#include <stdio.h>

#include "../include/raylib/raylib.h"
#include "../include/square.h"
#include "../include/box2d/box2d.h"


int main(void)
{
    InitWindow(600, 600, "raylib [core] example - basic window");
    SetTargetFPS(60);
    Image icon = LoadImage("raylib_logo.png");
    b2WorldDef worldDef = b2DefaultWorldDef();

    Square test_s = MakeSquare(30, 30, RED);

    if (!icon.data)
    {
        printf("Failed to load icon");
    }

    SetWindowIcon(icon);

    printf("Ding\n");
 
    Vector2 moPos;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        moPos = GetMousePosition();

        //printf("%d, %d\n", (int)moPos.x, (int)moPos.y);
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
