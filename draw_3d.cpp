#include "draw_3d.hpp"
#include <raylib.h>

namespace
{
// Define the camera to look into our 3d world
Camera3D camera3d = {
    .position = {0.0f, 100.0f, 100.0f}, // Camera position
    .target = {0.0f, 0.0f, 0.0f},       // Camera looking at point
    .up = {0.0f, 1.0f, 0.0f},           // Camera up vector (rotation towards target)
    .fovy = 45.0f,                      // Camera field-of-view Y
    .projection = CAMERA_PERSPECTIVE,   // Camera mode type
};
} // namespace

void Render3D::Init(int screenWidth, int screenHeight)
{
}

void Render3D::Draw(MazeGen::Maze &maze, MazeGen::Path &path, int currentCell, int goalCell, bool isShowingPath)
{
}
