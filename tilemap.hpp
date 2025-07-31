#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include <cmath>
#include <raylib.h>
#include <tuple>

#include "consts.hpp"
#include "grid.hpp"

#define WALKABLE 0
#define OBSTACLE 1

class TileMap : public Grid {
private:
    int collisions[GRID_COLS][GRID_ROWS] = {};

public:
    TileMap();

    bool IsObstacle(int col, int row);
    void SetObstacle(int col, int row);

    void Draw();
};

TileMap::TileMap()
    : Grid(TILE, GRID_COLS, GRID_ROWS)
{
    SetObstacle(8, 5);
    SetObstacle(8, 6);
    SetObstacle(8, 7);
    SetObstacle(8, 8);
}

bool TileMap::IsObstacle(int col, int row)
{
    return collisions[col][row] == OBSTACLE;
}

void TileMap::SetObstacle(int col, int row)
{
    collisions[col][row] = OBSTACLE;
}

void TileMap::Draw()
{
    Grid::Draw();
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if (collisions[col][row] == OBSTACLE) {
                auto p = ToPos(col, row);
                DrawRectangleLines(p.x, p.y, tile, tile, RED);
            }
        }
    }
}

#endif
