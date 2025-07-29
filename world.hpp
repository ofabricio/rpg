#ifndef WORLD_H
#define WORLD_H

#include <cmath>
#include <raylib.h>

#define WORLD_GRID_X 32
#define WORLD_GRID_Y 32
#define WORLD_TILE_SIZE 32

#define WORLD_WIDTH (WORLD_GRID_X * WORLD_TILE_SIZE)
#define WORLD_HEIGHT (WORLD_GRID_Y * WORLD_TILE_SIZE)

#define WORLD_FREE 0
#define WORLD_BLOCKED 1

class World {
public:
    int block[WORLD_GRID_Y][WORLD_GRID_X];
    void Init();
    void PosToGrid(Vector2 p, int* x, int* y);
    void GridToPos(int x, int y, Vector2* p) const;
    bool IsInGrid(int x, int y) const;
    bool IsFree(int x, int y) const;
    void BlockPosition(int x, int y);
    void FreePosition(int x, int y);
    void Draw(float gameScale);
};

void World::Init()
{
    for (size_t y = 0; y < WORLD_GRID_Y; ++y) {
        for (size_t x = 0; x < WORLD_GRID_X; ++x) {
            block[y][x] = WORLD_FREE;
        }
    }
}

void World::PosToGrid(Vector2 p, int* x, int* y)
{
    *x = (int)(p.x / WORLD_TILE_SIZE) - signbit(p.x);
    *y = (int)(p.y / WORLD_TILE_SIZE) - signbit(p.y);
}

void World::GridToPos(int x, int y, Vector2* p) const
{
    p->x = (float)x * WORLD_TILE_SIZE; //- signbit(p.x);
    p->y = (float)y * WORLD_TILE_SIZE; //- signbit(p.y);
}

bool World::IsInGrid(int x, int y) const
{
    return x >= 0 && x < WORLD_WIDTH && y >= 0 && y < WORLD_HEIGHT;
}

bool World::IsFree(int x, int y) const
{
    if (IsInGrid(x, y)) {
        return block[y][x] == WORLD_FREE;
    }
    return false;
}

void World::BlockPosition(int x, int y)
{
    if (IsInGrid(x, y)) {
        block[y][x] = WORLD_BLOCKED;
    }
}

void World::FreePosition(int x, int y)
{
    if (IsInGrid(x, y)) {
        block[y][x] = WORLD_FREE;
    }
}

void World::Draw(float gameScale)
{
    for (size_t y = 0; y < WORLD_GRID_Y; y++) {
        for (size_t x = 0; x < WORLD_GRID_X; x++) {
            DrawLine(x * WORLD_TILE_SIZE, 0, x * WORLD_TILE_SIZE, WORLD_WIDTH, DARKGRAY);
            DrawLine(0, y * WORLD_TILE_SIZE, WORLD_HEIGHT, y * WORLD_TILE_SIZE, DARKGRAY);
        }
    }
}

#endif
