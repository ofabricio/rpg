#ifndef WORLD_H
#define WORLD_H

#define WORLD_GRID_X 32
#define WORLD_GRID_Y 32
#define WORLD_TILE_SIZE 32

#define WORLD_WIDTH (WORLD_GRID_X * WORLD_TILE_SIZE)
#define WORLD_HEIGHT (WORLD_GRID_Y * WORLD_TILE_SIZE)

#define WORLD_FREE 0
#define WORLD_BLOCKED 1

typedef struct World {
    int block[WORLD_GRID_Y][WORLD_GRID_X];
} World;

void World_Init(World* w)
{
    for (size_t y = 0; y < WORLD_GRID_Y; ++y) {
        for (size_t x = 0; x < WORLD_GRID_X; ++x) {
            w->block[y][x] = WORLD_FREE;
        }
    }
}

void World_PosToGrid(const World* w, Vector2 p, int* x, int* y)
{
    *x = (int)(p.x / WORLD_TILE_SIZE) - signbit(p.x);
    *y = (int)(p.y / WORLD_TILE_SIZE) - signbit(p.y);
}

void World_GridToPos(const World* w, int x, int y, Vector2* p)
{
    p->x = (float)x * WORLD_TILE_SIZE; //- signbit(p.x);
    p->y = (float)y * WORLD_TILE_SIZE; //- signbit(p.y);
}

bool World_IsInGrid(const World* w, int x, int y)
{
    return x >= 0 && x < WORLD_WIDTH && y >= 0 && y < WORLD_HEIGHT;
}

bool World_IsFree(const World* w, int x, int y)
{
    if (World_IsInGrid(w, x, y)) {
        return w->block[y][x] == WORLD_FREE;
    }
    return false;
}

void World_BlockPosition(World* w, int x, int y)
{
    if (World_IsInGrid(w, x, y)) {
        w->block[y][x] = WORLD_BLOCKED;
    }
}

void World_FreePosition(World* w, int x, int y)
{
    if (World_IsInGrid(w, x, y)) {
        w->block[y][x] = WORLD_FREE;
    }
}

void World_Draw(const World* _, float gameScale)
{
    for (size_t y = 0; y < WORLD_GRID_Y; y++) {
        for (size_t x = 0; x < WORLD_GRID_X; x++) {
            DrawLine(x * WORLD_TILE_SIZE, 0, x * WORLD_TILE_SIZE, WORLD_WIDTH, DARKGRAY);
            DrawLine(0, y * WORLD_TILE_SIZE, WORLD_HEIGHT, y * WORLD_TILE_SIZE, DARKGRAY);
        }
    }
}

#endif
