#include "draw_2d.hpp"
namespace
{
void DrawCell(Cell &c, int columnId, int rowId, const CellOption &option = {})
{
    constexpr int HalfWidth = CellWidth / 2;
    constexpr int HalfHeight = CellHeight / 2;

    constexpr int WallThickness = 20;

    constexpr auto WallColor = LIGHTGRAY;
    constexpr auto GoalCell = DARKGREEN;
    constexpr auto InPath = YELLOW;

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
}
void Draw2D(const MazeGen::Maze &maze, const MazeGen::Path &path, int currentCell, int goalCell)
{

}