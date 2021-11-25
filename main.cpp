#include <maze.hpp>
#include <maze_path.hpp>
#include <raylib.h>

using namespace MazeGen;

constexpr int CellWidth = 100;
constexpr int CellHeight = CellWidth;

constexpr int from = 50;
constexpr int to = 1492;

struct CellOption
{
    bool isGoal = false;
    bool isInPath = false;
};

void DrawCell(Cell &c, int columnId, int rowId, const CellOption &option = {});

void Update(Camera2D &camera, Maze &maze, int &currentCell, bool &showPath, Path &path);

int main()
{
    constexpr int screenWidth = 1280;
    constexpr int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "A-Maze");
    SetTargetFPS(60);

    auto maze = MazeGen::Generate(50, 50);
    Path path = MazeGen::FindPathDFS(maze, from, to);
    bool isShowingPath = false;

    SetTargetFPS(15);

    int currentCell = from;

    Camera2D camera{.offset = {screenWidth / 2.0f, screenHeight / 2.0f}, .zoom = 1.0f};

    // Define the camera to look into our 3d world
    Camera3D camera3d = {
        .position = {0.0f, 100.0f, 100.0f}, // Camera position
        .target = {0.0f, 0.0f, 0.0f},     // Camera looking at point
        .up = {0.0f, 1.0f, 0.0f},         // Camera up vector (rotation towards target)
        .fovy = 45.0f,                    // Camera field-of-view Y
        .projection = CAMERA_PERSPECTIVE,  // Camera mode type
    };
    while (!WindowShouldClose())
    {
        Update(camera, maze, currentCell, isShowingPath, path);
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
                    option.isGoal = (i == to);

                    if (isShowingPath &&
                        std::find_if(path.begin(), path.end(), [&i](auto &n) { return (n.cell == i); }) != path.end())
                    {
                        option.isInPath = true;
                    }

                    DrawCell(maze[i], x, y, option);
                }
            }
            EndMode2D();

            BeginMode3D(camera3d);
            {
                Vector3 cubePosition = {0.0f, 2.0f, 0.0f};

                DrawCube({0, 0, 0}, 10.0f, 10.0f, 10.0f, DARKGREEN);
                DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED);
                DrawPlane({0, 0, 0}, {2.0f, 2.0f}, GRAY);
            }
            EndMode3D();

            DrawCircle(screenWidth / 2, screenHeight / 2, 20, RED);
        }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}

void Update(Camera2D &camera, Maze &maze, int &currentCell, bool &showPath, Path &path)
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
            path = FindPathDFS(maze, currentCell, to);
    }

    int x = currentCell % maze.column;
    int y = currentCell / maze.column;

    camera.target = {.x = float(x) * CellWidth, .y = float(y) * CellHeight};
}

void DrawCell(Cell &c, int columnId, int rowId, const CellOption &option)
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
