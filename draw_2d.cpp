#include "draw_2d.hpp"

#include <raylib.h>

using namespace MazeGen;

namespace
{
constexpr int CellWidth = 100;
constexpr int CellHeight = CellWidth;

constexpr int HalfWidth = CellWidth / 2;
constexpr int HalfHeight = CellHeight / 2;

constexpr int WallThickness = 20;

constexpr auto WallColor = LIGHTGRAY;
constexpr auto GoalCell = DARKGREEN;
constexpr auto InPath = YELLOW;

int screenWidth = 0;
int screenHeight = 0;

struct CellOption
{
    bool isGoal = false;
    bool isInPath = false;
};

void DrawCell(Maze &maze, int cellId, const CellOption &option = {})
{
    auto [columnId, rowId] = maze.CellPosition(cellId);

    const int originX = columnId * CellWidth;
    const int originY = rowId * CellHeight;

    const int cellLeft = originX - HalfWidth;
    const int cellRight = originX + HalfWidth;
    const int cellTop = originY - HalfHeight;
    const int cellBottom = originY + HalfHeight;

    const int cellInnerLeft = cellLeft + WallThickness;
    const int cellInnerRight = cellRight - WallThickness;
    const int cellInnerTop = cellTop + WallThickness;
    const int cellInnerBottom = cellBottom - WallThickness;

    const int wallWidth = CellWidth - WallThickness * 2;
    const int wallHeight = CellHeight - WallThickness * 2;

    if (option.isInPath)
    {
        DrawRectangle(originX - HalfWidth, originY - HalfHeight, CellWidth, CellHeight, InPath);
    }

    if (option.isGoal)
    {
        DrawRectangle(originX - HalfWidth, originY - HalfHeight, CellWidth, CellHeight, GoalCell);
    }

    DrawRectangle(cellLeft, cellTop, WallThickness, WallThickness, WallColor);
    DrawRectangle(cellInnerRight, cellTop, WallThickness, WallThickness, WallColor);
    DrawRectangle(cellLeft, cellInnerBottom, WallThickness, WallThickness, WallColor);
    DrawRectangle(cellInnerRight, cellInnerBottom, WallThickness, WallThickness, WallColor);

    if (maze[cellId].ConnectedCell(Direction::North) == InvalidCell)
    {
        DrawRectangle(cellInnerLeft, cellTop, wallWidth, WallThickness, WallColor);
    }

    if (maze[cellId].ConnectedCell(Direction::South) == InvalidCell)
    {
        DrawRectangle(cellInnerLeft, cellInnerBottom, wallWidth, WallThickness, WallColor);
    }

    if (maze[cellId].ConnectedCell(Direction::West) == InvalidCell)
    {
        DrawRectangle(cellLeft, cellInnerTop, WallThickness, wallHeight, WallColor);
    }

    if (maze[cellId].ConnectedCell(Direction::East) == InvalidCell)
    {
        DrawRectangle(cellInnerRight, cellInnerTop, WallThickness, wallHeight, WallColor);
    }
}

bool IsCellOnPath(MazeGen::Path &path, int &i)
{
    return std::find_if(path.begin(), path.end(), [&i](auto &n) { return (n.cell == i); }) != path.end();
}
} // namespace

void Render2D::Draw(MazeGen::Maze &maze, MazeGen::Path &path, int currentCell, int goalCell, bool isShowingPath)
{
    auto [x, y] = maze.CellPosition(currentCell);

    Camera2D camera{
        .offset = {screenWidth / 2.0f, screenHeight / 2.0f},
        .target = {.x = float(x) * CellWidth, .y = float(y) * CellHeight},
        .zoom = 1.0f,
    };

    ClearBackground(BLACK);

    BeginMode2D(camera);
    {
        for (int i = 0; i < maze.cellCount; i++)
        {
            CellOption option;
            option.isGoal = (i == goalCell);

            if (isShowingPath && IsCellOnPath(path, i))
            {
                option.isInPath = true;
            }

            DrawCell(maze, i, option);
        }
    }
    EndMode2D();
    DrawCircle(screenWidth / 2, screenHeight / 2, 20, RED);
}

void Render2D::Init(int w, int h)
{
    screenWidth = w;
    screenHeight = h;
}
