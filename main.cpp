#include <maze.hpp>
#include <maze_path.hpp>
#include <raylib.h>

#include "draw_2d.hpp"

using namespace MazeGen;

constexpr int from = 50;
constexpr int to = 1492;

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

    Render2D::Init(screenWidth, screenHeight);

    while (!WindowShouldClose())
    {
        Update(maze, currentCell, isShowingPath, path);
        Render2D::Draw(maze, path, currentCell, to, isShowingPath);
    }

    CloseWindow();

    return 0;
}

void Update(Maze &maze, int &currentCell, bool &showPath, MazeGen::Path &path)
{
    Cell c = maze[currentCell];

    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
    {
        int cell = c.ConnectedCell(Direction::North);
        if (cell != InvalidCell)
        {
            currentCell = cell;
        }
    }

    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S))
    {
        int cell = c.ConnectedCell(Direction::South);
        if (cell != InvalidCell)
        {
            currentCell = cell;
        }
    }

    if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A))
    {
        int cell = c.ConnectedCell(Direction::West);
        if (cell != InvalidCell)
        {
            currentCell = cell;
        }
    }

    if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D))
    {
        int cell = c.ConnectedCell(Direction::East);
        if (cell != InvalidCell)
        {
            currentCell = cell;
        }
    }

    if (IsKeyPressed(KEY_P))
    {
        showPath = !showPath;
        if (showPath)
        {
            path = FindPathDFS(maze, currentCell, to);
        }
    }
}
