#ifndef ACTOR_HPP
#define ACTOR_HPP

#include <raylib.h>
#include <raymath.h>
#include <string>

#include "consts.hpp"
#include "debug.hpp"
#include "gameobj.hpp"
#include "sprite.hpp"

class Actor : public GameObj {
public:
    std::string name;
    Actor();
    float ZOrder() override;
    void Update(float) override;
    void Draw() override;
};

Actor::Actor()
{
}

float Actor::ZOrder()
{
    return pos.y;
}

void Actor::Update(float dt)
{
}

void Actor::Draw()
{
    float w = TILE;
    float h = TILE * 2.0f;

    DrawRectangleV(Vector2Subtract(pos, Vector2(w / 2.0f, h)), Vector2(w, h), BLUE);

    DrawText(name.c_str(), pos.x - MeasureText(name.c_str(), 10) / 2.0f, pos.y - h - 10, 10, WHITE);

    Debug::DrawPoint(pos, SKYBLUE);
}

#endif
