#pragma once
#include <maze.hpp>
#include <maze_path.hpp>

namespace Render2D
{
    void Init(int screenWidth, int screenHeight);
    void Draw(MazeGen::Maze & maze, MazeGen::Path & path, int currentCell, int goalCell, bool isShowingPath);
} // namespace 2D