#ifndef GRID_H
#define GRID_H

#include <cmath>
#include <raylib.h>
#include <tuple>

class Grid {
    float cellSize;
    int gridCols;
    int gridRows;

public:
    Grid(float cellSize, int gridCols, int gridRows);
    std::tuple<int, int> PosToGrid(Vector2);
    std::tuple<int, int> IDToGrid(int id);
    Vector2 GridToPos(int col, int row);
    Vector2 IDToPos(int id);
    int GridToID(int col, int row);
    bool IsInGrid(int col, int row);
    Vector2 Cell();
    void Draw(float scale, float w, float h);
};

Grid::Grid(float cellSize, int gridCols, int gridRows)
{
    this->cellSize = cellSize;
    this->gridCols = gridCols;
    this->gridRows = gridRows;
}

std::tuple<int, int> Grid::PosToGrid(Vector2 p)
{
    int x = (int)(p.x / cellSize) - signbit(p.x);
    int y = (int)(p.y / cellSize) - signbit(p.y);
    return std::make_tuple(x, y);
}

std::tuple<int, int> Grid::IDToGrid(int id)
{
    int x = id % gridCols;
    int y = id / gridCols;
    return std::make_tuple(x, y);
}

Vector2 Grid::IDToPos(int id)
{
    auto [col, row] = IDToGrid(id);
    return GridToPos(col, row);
}

Vector2 Grid::GridToPos(int col, int row)
{
    return Vector2(col * cellSize, row * cellSize);
}

int Grid::GridToID(int col, int row)
{
    if (!IsInGrid(col, row)) {
        return -1;
    }
    return row * gridCols + col;
}

bool Grid::IsInGrid(int col, int row)
{
    return col >= 0 && col < gridCols && row >= 0 && row < gridRows;
}

Vector2 Grid::Cell()
{
    return Vector2(cellSize, cellSize);
}

void Grid::Draw(float scale, float w, float h)
{
    for (size_t row = 0; row <= h; row += cellSize) {
        DrawLine(0, row, w, row, DARKGRAY);
    }
    for (size_t col = 0; col <= w; col += cellSize) {
        DrawLine(col, 0, col, h, DARKGRAY);
    }
}

#endif
