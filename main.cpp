#include <fmt/core.h>
#include <maze.hpp>
#include <maze_path.hpp>
#include <raylib.h>

using namespace MazeGen;

void DrawCell(Cell &c, int columnId, int rowId);

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

    Camera2D camera{.offset = {screenWidth / 2.0f, screenHeight / 2.0f}, .zoom = 1.0f};
    while (!WindowShouldClose())
    {
        BeginDrawing();
        {
            ClearBackground(BLACK);

            BeginMode2D(camera);
            {
                for (int i = 0; i < maze.cellCount; i++)
                {
                    int x = i % maze.column;
                    int y = i / maze.column;

                    DrawCell(maze[i], x, y);
                }
            }
            EndMode2D();

            DrawCircle(screenWidth / 2, screenHeight / 2, 20, RED);
        }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}

void DrawCell(Cell &c, int columnId, int rowId)
{
    constexpr int CellWidth = 100;
    constexpr int CellHeight = CellWidth;

    constexpr int HalfWidth = CellWidth / 2;
    constexpr int HalfHeight = CellHeight / 2;

    constexpr int WallThickness = 20;

    const int originX = columnId * CellWidth;
    const int originY = rowId * CellHeight;

    const int cellLeft = originX - HalfWidth;
    const int cellRight = originX + HalfWidth;
    const int cellTop = originY - HalfHeight;
    const int cellBottom = originY - HalfHeight;

    const int cellInnerLeft = cellLeft + WallThickness;
    const int cellInnerRight = cellRight - WallThickness;
    const int cellInnerTop = cellTop + WallThickness;
    const int cellInnerBottom = cellBottom - WallThickness;

    // DrawRectangle(originX - HalfWidth, originY - HalfHeight, CellWidth, CellHeight, DARKGRAY);

    DrawRectangle(cellLeft, cellTop, WallThickness, WallThickness, DARKGREEN);
    DrawRectangle(cellInnerRight, cellTop, WallThickness, WallThickness, RED);
    DrawRectangle(cellLeft, cellInnerBottom, WallThickness, WallThickness, DARKBLUE);
    DrawRectangle(cellInnerRight, cellInnerBottom, WallThickness, WallThickness, DARKGRAY);

    DrawText(fmt::format("{0}, {1}", columnId, rowId).c_str(), originX, originY, 20, LIGHTGRAY);
}
