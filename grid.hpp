#ifndef GRID_HPP
#define GRID_HPP

#include <cmath>
#include <raylib.h>
#include <tuple>

struct Grid {
    int tile;
    int cols;
    int rows;

    Grid(int tile, int cols, int rows);
    std::tuple<int, int> ToCell(Vector2);
    std::tuple<int, int> ToCell(int);
    Vector2 ToPos(int col, int row);
    Vector2 ToPos(int);
    Vector2 ToCenter(int col, int row);
    Vector2 TileSize();
    int ToId(int col, int row);
    bool IsInGrid(int col, int row);
    bool IsInGrid(Vector2);
    void Draw();
};

Grid::Grid(int tile, int cols, int rows)
    : tile(tile)
    , cols(cols)
    , rows(rows)
{
}

std::tuple<int, int> Grid::ToCell(Vector2 v)
{
    int col = (v.x / tile) - signbit(v.x);
    int row = (v.y / tile) - signbit(v.y);
    return std::make_tuple(col, row);
}

std::tuple<int, int> Grid::ToCell(int id)
{
    int col = id % cols;
    int row = id / cols;
    return std::make_tuple(col, row);
}

Vector2 Grid::ToPos(int id)
{
    auto [col, row] = ToCell(id);
    return ToPos(col, row);
}

Vector2 Grid::ToPos(int col, int row)
{
    return Vector2(col * tile, row * tile);
}

Vector2 Grid::ToCenter(int col, int row)
{
    return Vector2(col * tile + tile / 2.0f, row * tile + tile / 2.0f);
}

int Grid::ToId(int col, int row)
{
    return row * cols + col;
}

bool Grid::IsInGrid(int col, int row)
{
    return col >= 0 && col < cols
        && row >= 0 && row < rows;
}

bool Grid::IsInGrid(Vector2 v)
{
    auto [col, row] = ToCell(v);
    return IsInGrid(col, row);
}

Vector2 Grid::TileSize()
{
    return Vector2(tile, tile);
}

void Grid::Draw()
{
    float w = cols * tile;
    float h = rows * tile;

    for (size_t row = 0; row <= h; row += tile) {
        DrawLine(0, row, w, row, DARKGRAY);
    }
    for (size_t col = 0; col <= w; col += tile) {
        DrawLine(col, 0, col, h, DARKGRAY);
    }
}

#endif
