#include <maze.hpp>
#include <maze_path.hpp>
#include <raylib.h>

#include "draw_2d.hpp"
#include "draw_3d.hpp"

using namespace MazeGen;

constexpr int StartCell = 125;
constexpr int GoalCell = 2092;

constexpr int ScreenWidth = 1280;
constexpr int ScreenHeight = 720;

enum class RenderMode
{
    Graphics2D,
    Graphics3D
};

RenderMode renderMode = RenderMode::Graphics2D;

void Update(Maze &maze, int &currentCell, bool &showPath, MazeGen::Path &path);
void DrawInstruction();

int main()
{
    InitWindow(ScreenWidth, ScreenHeight, "A-Maze");
    SetTargetFPS(60);

    auto maze = MazeGen::Generate(50, 50);
    auto path = MazeGen::FindPathDFS(maze, StartCell, GoalCell);
    bool isShowingPath = false;

    int currentCell = StartCell;

    Render2D::Init(ScreenWidth, ScreenHeight);
    Render3D::Init(ScreenWidth, ScreenHeight);

    while (!WindowShouldClose())
    {
        Update(maze, currentCell, isShowingPath, path);
        BeginDrawing();
        {
            ClearBackground(BLACK);
            switch (renderMode)
            {
            case RenderMode::Graphics2D:
                Render2D::Draw(maze, path, currentCell, GoalCell, isShowingPath);
                break;

            case RenderMode::Graphics3D:
                Render3D::Draw(maze, path, currentCell, GoalCell, isShowingPath);
                break;
            }

            DrawInstruction();
        }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}

void Update(Maze &maze, int &currentCellId, bool &showPath, MazeGen::Path &path)
{
    Cell c = maze[currentCellId];

    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
    {
        int connectedCell = c.ConnectedCell(Direction::North);
        if (connectedCell != InvalidCell)
        {
            currentCellId = connectedCell;
        }
    }

    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S))
    {
        int connectedCell = c.ConnectedCell(Direction::South);
        if (connectedCell != InvalidCell)
        {
            currentCellId = connectedCell;
        }
    }

    if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A))
    {
        int connectedCell = c.ConnectedCell(Direction::West);
        if (connectedCell != InvalidCell)
        {
            currentCellId = connectedCell;
        }
    }

    if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D))
    {
        int connectedCell = c.ConnectedCell(Direction::East);
        if (connectedCell != InvalidCell)
        {
            currentCellId = connectedCell;
        }
    }

    if (IsKeyPressed(KEY_P))
    {
        showPath = !showPath;
        if (showPath)
        {
            path = FindPathDFS(maze, currentCellId, GoalCell);
        }
    }

    if (IsKeyPressed(KEY_ZERO))
    {
        switch (renderMode)
        {
        case RenderMode::Graphics2D:
            renderMode = RenderMode::Graphics3D;
            break;

        case RenderMode::Graphics3D:
            renderMode = RenderMode::Graphics2D;
            break;
        }
    }
}

void DrawInstruction()
{
    constexpr int posX = ScreenWidth - 500;
    constexpr int posY = ScreenHeight - 220;
    constexpr int width = 480;
    constexpr int height = 200;

    DrawRectangleGradientV(posX, posY, width, height, Color{0, 0, 0, 0x80}, Color{0, 0, 0, 0xB0});

    DrawText("Instruction", posX + 10, posY + 10, 20, YELLOW);
    DrawText("Moves to the green cell desinated somewhere in this maze.", posX + 20, posY + 40, 16, WHITE);
    DrawText("* WSAD/Arrow Key - Moves the player.", posX + 20, posY + 80, 16, WHITE);
    DrawText("* P - Toggles the path finder.", posX + 20, posY + 110, 16, WHITE);
    DrawText("* 0 - Toggles 2D/3D mode.", posX + 20, posY + 140, 16, WHITE);
}