#include <raylib.h>

int main()
{
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib-template");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        {
            ClearBackground(RAYWHITE);
            DrawText("Hello", 190, 200, 20, LIGHTGRAY);
        }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}