#ifndef ZONE_HPP
#define ZONE_HPP

#include <algorithm>
#include <raylib.h>
#include <vector>

#include "actor.hpp"
#include "gameobj.hpp"
#include "tilemap.hpp"

class Zone {
    TileMap tmap;
    std::vector<Actor*> actors;
    std::vector<GameObj*> render;

public:
    Zone(TileMap);
    ~Zone();
    void Add(Actor*);
    void Update(float);
    void Draw();
};

Zone::Zone(TileMap m)
    : tmap(m)
{
}

Zone::~Zone()
{
    actors.clear();
    render.clear();
}

void Zone::Add(Actor* v)
{
    actors.push_back(v);
    render.push_back(v);
}

void Zone::Update(float dt)
{
    for (auto& a : actors) {
        a->Update(dt);
    }
}

void Zone::Draw()
{
    std::sort(render.begin(), render.end(), [](GameObj* a, GameObj* b) { return a->ZOrder() < b->ZOrder(); });
    for (auto& r : render) {
        r->Draw();
    }
}

#endif
