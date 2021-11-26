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

Camera2D camera{.offset = {screenWidth / 2.0f, screenHeight / 2.0f}, .zoom = 1.0f};

struct CellOption
{
    bool isGoal = false;
    bool isInPath = false;
};

void DrawCell(Cell &c, int columnId, int rowId, const CellOption &option = {})
{
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

    const int WallWidth = CellWidth - WallThickness * 2;
    const int WallHeight = CellHeight - WallThickness * 2;

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

    if (c.ConnectedCell(Direction::North) == InvalidCell)
    {
        DrawRectangle(cellInnerLeft, cellTop, WallWidth, WallThickness, WallColor);
    }

    if (c.ConnectedCell(Direction::South) == InvalidCell)
    {
        DrawRectangle(cellInnerLeft, cellInnerBottom, WallWidth, WallThickness, WallColor);
    }

    if (c.ConnectedCell(Direction::West) == InvalidCell)
    {
        DrawRectangle(cellLeft, cellInnerTop, WallThickness, WallHeight, WallColor);
    }

    if (c.ConnectedCell(Direction::East) == InvalidCell)
    {
        DrawRectangle(cellInnerRight, cellInnerTop, WallThickness, WallHeight, WallColor);
    }
}
} // namespace

void Render2D::Draw(MazeGen::Maze &maze, MazeGen::Path &path, int currentCell, int goalCell, bool isShowingPath)
{
    auto [x, y] = maze.CellPosition(currentCell);

    camera.offset = {screenWidth / 2.0f, screenHeight / 2.0f};
    camera.zoom = 1.0f;
    camera.target = {.x = float(x) * CellWidth, .y = float(y) * CellHeight};

    BeginDrawing();
    {
        ClearBackground(BLACK);

        BeginMode2D(camera);
        {
            for (int i = 0; i < maze.cellCount; i++)
            {
                int x = i % maze.column;
                int y = i / maze.column;

                CellOption option;
                option.isGoal = (i == goalCell);

                if (isShowingPath &&
                    std::find_if(path.begin(), path.end(), [&i](auto &n) { return (n.cell == i); }) != path.end())
                {
                    option.isInPath = true;
                }

                DrawCell(maze[i], x, y, option);
            }
        }
        EndMode2D();
        DrawCircle(screenWidth / 2, screenHeight / 2, 20, RED);
    }
    EndDrawing();
}

void Render2D::Init(int w, int h)
{
    screenWidth = w;
    screenHeight = h;
}
