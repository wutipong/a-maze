#include "draw_3d.hpp"
#include <raylib.h>

namespace
{
constexpr float CellWidth = 50;
constexpr float CellLength = 50;

constexpr float WallWidth = 10;
constexpr float WallLength = 10;
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

    constexpr float SideWallWidth = CellWidth - WallWidth;
    constexpr float SideWallLength = CellLength - WallLength;

    DrawPlane({xPos, 0, zPos}, {CellWidth, CellLength}, GRAY);

    // Wall
    DrawCube({xPos, HalfWallHeight, -HalfCellLength}, SideWallWidth, WallHeight, HalfWallLength, DARKGRAY);
    DrawCubeWires({xPos, HalfWallHeight, -HalfCellLength}, SideWallWidth, WallHeight, HalfWallLength, SKYBLUE);

    DrawCube({xPos, HalfWallHeight, HalfCellLength}, SideWallWidth, WallHeight, HalfWallLength, DARKBLUE);
    DrawCubeWires({xPos, HalfWallHeight, HalfCellLength}, SideWallWidth, WallHeight, HalfWallLength, SKYBLUE);

    DrawCube({-HalfCellWidth, HalfWallHeight, 0.0f}, HalfWallWidth, WallHeight, SideWallLength, DARKGREEN);
    DrawCubeWires({-HalfCellWidth, HalfWallHeight, 0.0f}, HalfWallWidth, WallHeight, SideWallLength, SKYBLUE);

    DrawCube({HalfCellWidth, HalfWallHeight, 0.0f}, HalfWallWidth, WallHeight, SideWallLength, DARKPURPLE);
    DrawCubeWires({HalfCellWidth, HalfWallHeight, 0.0f}, HalfWallWidth, WallHeight, SideWallLength, SKYBLUE);

    // Corners
    DrawCube({-HalfCellWidth/2, HalfWallHeight, -HalfCellLength}, HalfWallWidth, WallHeight, HalfWallLength, RED);
    DrawCubeWires({-HalfCellWidth/2, HalfWallHeight, -HalfCellLength}, HalfWallWidth, WallHeight, HalfWallLength,
                  SKYBLUE);

    DrawCube({HalfCellWidth, HalfWallHeight, HalfCellLength}, HalfWallWidth, WallHeight, HalfWallLength, GREEN);
    DrawCubeWires({HalfCellWidth, HalfWallHeight, HalfCellLength}, HalfWallWidth, WallHeight, HalfWallLength, SKYBLUE);

    DrawCube({-HalfCellWidth, HalfWallHeight, HalfCellLength}, HalfWallWidth, WallHeight, HalfWallLength, BLUE);
    DrawCubeWires({-HalfCellWidth, HalfWallHeight, HalfCellLength}, HalfWallWidth, WallHeight, HalfWallLength, SKYBLUE);

    DrawCube({HalfCellWidth, HalfWallHeight, -HalfCellLength}, HalfWallWidth, WallHeight, HalfWallLength, WHITE);
    DrawCubeWires({HalfCellWidth, HalfWallHeight, -HalfCellLength}, HalfWallWidth, WallHeight, HalfWallLength, SKYBLUE);
}
} // namespace

void Render3D::Init(int screenWidth, int screenHeight)
{
}

void Render3D::Draw(MazeGen::Maze &maze, MazeGen::Path &path, int currentCell, int goalCell, bool isShowingPath)
{

    auto [x, z] = maze.CellPosition(currentCell);

    Camera3D camera = {
        .position = {x * WallWidth, 100.0f, 100.0f + (z * WallLength)},
        .target = {x * WallWidth, 0.0f, z * WallLength},
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
            constexpr float PlayerWidth = 10;
            constexpr float PlayerHeight = 10;
            constexpr float PlayerLength = 10;

            constexpr float HalfPlayerWidth = PlayerWidth / 2;
            constexpr float HalfPlayerHeight = PlayerHeight / 2;
            constexpr float HalfPlayerLength = PlayerLength / 2;

            DrawSphere({x * WallWidth, HalfPlayerHeight, z * WallLength}, HalfPlayerWidth, RED);
        }
        EndMode3D();
    }
    EndDrawing();
}
