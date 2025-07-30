#ifndef ZONE_H
#define ZONE_H

#include <raylib.h>
#include <vector>

#include "grid.hpp"

class Zone {
    Grid grid;

public:
    Zone(Grid g);
    void Update(float dt);
    void Draw();
};

Zone::Zone(Grid g)
    : grid(g)
{
}

void Zone::Update(float dt)
{
}

void Zone::Draw()
{
}

#endif
