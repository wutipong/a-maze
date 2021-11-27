#include "draw_3d.hpp"
#include <raylib.h>

using namespace MazeGen;

namespace
{
constexpr float CellWidth = 50;
constexpr float CellLength = 50;

constexpr float WallWidth = 20;
constexpr float WallLength = 20;
constexpr float WallHeight = 10;

void DrawCell(MazeGen::Maze &maze, int currentCell)
{
    const auto [x, z] = maze.CellPosition(currentCell);

    const auto xPos = x * CellWidth;
    const auto zPos = z * CellLength;

    constexpr float HalfCellWidth = CellWidth / 2;
    constexpr float HalfCellLength = CellLength / 2;

    constexpr float HalfWallWidth = WallWidth / 2;
    constexpr float HalfWallLength = WallLength / 2;
    constexpr float HalfWallHeight = WallHeight / 2;

    constexpr float QuarterWallWidth = HalfWallWidth / 2;
    constexpr float QuarterWallLength = HalfWallLength / 2;

    constexpr float SideWallWidth = CellWidth - WallWidth;
    constexpr float SideWallLength = CellLength - WallLength;

    DrawPlane({xPos, 0, zPos}, {CellWidth, CellLength}, GRAY);

    // Raylib draws cube by using the cube's center as the reference point. We have to adjust the origin  so we can
    // specify the outer edges as its positioning. 
    
    // Wall
    if (maze[currentCell].ConnectedCell(Direction::North) == InvalidCell)
    {

        DrawCube({xPos, HalfWallHeight, zPos - HalfCellLength + QuarterWallLength}, SideWallWidth, WallHeight,
                 HalfWallLength, DARKGRAY);
        DrawCubeWires({xPos, HalfWallHeight, zPos - HalfCellLength + QuarterWallLength}, SideWallWidth, WallHeight,
                      HalfWallLength, LIGHTGRAY);
    }

    if (maze[currentCell].ConnectedCell(Direction::South) == InvalidCell)
    {
        DrawCube({xPos, HalfWallHeight, zPos + HalfCellLength - QuarterWallLength}, SideWallWidth, WallHeight,
                 HalfWallLength, DARKGRAY);
        DrawCubeWires({xPos, HalfWallHeight, zPos + HalfCellLength + QuarterWallLength}, SideWallWidth, WallHeight,
                      HalfWallLength, LIGHTGRAY);
    }

    if (maze[currentCell].ConnectedCell(Direction::West) == InvalidCell)
    {
        DrawCube({xPos - HalfCellWidth + QuarterWallWidth, HalfWallHeight, zPos}, HalfWallWidth, WallHeight,
                 SideWallLength, DARKGRAY);
        DrawCubeWires({xPos - HalfCellWidth + QuarterWallWidth, HalfWallHeight, zPos}, HalfWallWidth, WallHeight,
                      SideWallLength, LIGHTGRAY);
    }

    if (maze[currentCell].ConnectedCell(Direction::East) == InvalidCell)
    {
        DrawCube({xPos + HalfCellWidth - QuarterWallWidth, HalfWallHeight, zPos}, HalfWallWidth, WallHeight,
                 SideWallLength, DARKGRAY);
        DrawCubeWires({xPos + HalfCellWidth - QuarterWallWidth, HalfWallHeight, zPos}, HalfWallWidth, WallHeight,
                      SideWallLength, LIGHTGRAY);
    }
    // Corners
    DrawCube({xPos - HalfCellWidth + QuarterWallWidth, HalfWallHeight, zPos - HalfCellLength + QuarterWallLength},
             HalfWallWidth, WallHeight, HalfWallLength, DARKGRAY);
    DrawCubeWires({xPos - HalfCellWidth + QuarterWallWidth, HalfWallHeight, zPos - HalfCellLength + QuarterWallLength},
                  HalfWallWidth, WallHeight, HalfWallLength, LIGHTGRAY);

    DrawCube({xPos + HalfCellWidth - QuarterWallWidth, HalfWallHeight, zPos + HalfCellLength - QuarterWallLength},
             HalfWallWidth, WallHeight, HalfWallLength, DARKGRAY);
    DrawCubeWires({xPos + HalfCellWidth - QuarterWallWidth, HalfWallHeight, zPos + HalfCellLength - QuarterWallLength},
                  HalfWallWidth, WallHeight, HalfWallLength, LIGHTGRAY);

    DrawCube({xPos - HalfCellWidth + QuarterWallWidth, HalfWallHeight, zPos + HalfCellLength - QuarterWallLength},
             HalfWallWidth, WallHeight, HalfWallLength, DARKGRAY);
    DrawCubeWires({xPos - HalfCellWidth + QuarterWallWidth, HalfWallHeight, zPos +HalfCellLength - QuarterWallLength},
                  HalfWallWidth, WallHeight, HalfWallLength, LIGHTGRAY);

    DrawCube({xPos + HalfCellWidth - QuarterWallWidth, HalfWallHeight, zPos - HalfCellLength + QuarterWallLength},
             HalfWallWidth, WallHeight, HalfWallLength, DARKGRAY);
    DrawCubeWires({xPos + HalfCellWidth - QuarterWallWidth, HalfWallHeight, zPos - HalfCellLength + QuarterWallLength},
                  HalfWallWidth, WallHeight, HalfWallLength, LIGHTGRAY);
}
} // namespace

void Render3D::Init(int screenWidth, int screenHeight)
{
}

void Render3D::Draw(MazeGen::Maze &maze, MazeGen::Path &path, int currentCell, int goalCell, bool isShowingPath)
{
    auto [x, z] = maze.CellPosition(currentCell);

    Camera3D camera = {
        .position = {x * CellWidth, 100.0f, 100.0f + (z * CellLength)},
        .target = {x * CellWidth, 0.0f, z * CellLength},
        .up = {0.0f, 1.0f, 0.0f},
        .fovy = 45.0f,
        .projection = CAMERA_PERSPECTIVE,
    };

    BeginDrawing();
    {
        ClearBackground(BLACK);

        BeginMode3D(camera);
        {
            for (int i = 0; i < maze.cellCount; i++)
            {
                DrawCell(maze, i);
            }

            // Player
            constexpr float PlayerWidth = 20;
            constexpr float PlayerHeight = 20;
            constexpr float PlayerLength = 20;

            constexpr float HalfPlayerWidth = PlayerWidth / 2;
            constexpr float HalfPlayerHeight = PlayerHeight / 2;
            constexpr float HalfPlayerLength = PlayerLength / 2;

            DrawSphere({x * CellWidth, HalfPlayerHeight, z * CellLength}, HalfPlayerWidth, RED);
        }
        EndMode3D();
    }
    EndDrawing();
}
