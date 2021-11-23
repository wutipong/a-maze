#include <raylib.h>
#include <maze.hpp>
#include <maze_path.hpp>

int main()
{
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 450;

    constexpr int from = 50;
    constexpr int to = 1250;

    InitWindow(screenWidth, screenHeight, "raylib-template");
    SetTargetFPS(60);

    auto maze = MazeGen::Generate(50, 50);
    auto path = MazeGen::FindPathDFS(maze, from, to);

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