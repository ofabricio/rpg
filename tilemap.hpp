#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include <cmath>
#include <raylib.h>
#include <tuple>

#include "grid.hpp"

#define WALKABLE 0
#define OBSTACLE 1

class TileMap : public Grid {
private:
    std::vector<int> waypoints;
    std::vector<int> collision;

public:
    TileMap(Grid g, std::vector<int> waypoints, std::vector<int> collision);

    bool IsObstacle(int col, int row);
    void SetObstacle(int col, int row);
    void SetWaypoint(int col, int row, int value);
    int GetWaypoint(int col, int row);

    void Draw();
};

TileMap::TileMap(Grid g, std::vector<int> waypoints, std::vector<int> collision)
    : Grid(g)
    , waypoints(waypoints)
    , collision(collision)
{
}

bool TileMap::IsObstacle(int col, int row)
{
    return collision[ToId(col, row)] == OBSTACLE;
}

void TileMap::SetObstacle(int col, int row)
{
    collision[ToId(col, row)] = OBSTACLE;
}

void TileMap::SetWaypoint(int col, int row, int value)
{
    waypoints[ToId(col, row)] = value;
}

int TileMap::GetWaypoint(int col, int row)
{
    return waypoints[ToId(col, row)];
}

void TileMap::Draw()
{
    Grid::Draw();
    for (size_t i = 0; i < cols * rows; i++) {
        if (collision[i] == OBSTACLE) {
            auto p = ToPos(i);
            DrawRectangleLines(p.x, p.y, tile, tile, RED);
        }
    }
    for (size_t i = 0; i < cols * rows; i++) {
        if (waypoints[i] > 0) {
            auto p = ToPos(i);
            DrawRectangleLines(p.x, p.y, tile, tile, YELLOW);
        }
    }
}

#endif
