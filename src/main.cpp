#include "raylib.h"

int main(void)
{
    InitWindow(800, 800, "raylib [core] example - basic window");

    while (!WindowShouldClose())
    {
        BeginDrawing();
            GetMousePosition();
            ClearBackground(Color({100, 149, 237, 255}));
            DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}