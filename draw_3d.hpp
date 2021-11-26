#pragma once

#include <maze.hpp>
#include <maze_path.hpp>

namespace Render3D
{
void Init(int screenWidth, int screenHeight);
void Draw(MazeGen::Maze &maze, MazeGen::Path &path, int currentCell, int goalCell, bool isShowingPath);
} // namespace Render3D
