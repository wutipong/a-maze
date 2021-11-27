#include <maze.hpp>
#include <maze_path.hpp>
#include <raylib.h>

// #define RENDER_3D

#ifdef RENDER_3D
#include "draw_3d.hpp"
using namespace Render3D;
#else
#include "draw_2d.hpp"
using namespace Render2D;
#endif

using namespace MazeGen;

constexpr int from = 0;
constexpr int to = 2092;

void Update(Maze &maze, int &currentCell, bool &showPath, MazeGen::Path &path);


int main()
{
    constexpr int screenWidth = 1280;
    constexpr int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "A-Maze");
    SetTargetFPS(60);

    auto maze = MazeGen::Generate(50, 50);
    auto path = MazeGen::FindPathDFS(maze, from, to);
    bool isShowingPath = false;

    int currentCell = from;

    Init(screenWidth, screenHeight);

    while (!WindowShouldClose())
    {
        Update(maze, currentCell, isShowingPath, path);
        Draw(maze, path, currentCell, to, isShowingPath);
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
            path = FindPathDFS(maze, currentCellId, to);
        }
    }
}
