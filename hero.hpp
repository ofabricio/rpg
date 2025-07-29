#ifndef HERO_H
#define HERO_H

#include "sprite.hpp"

class Hero {
private:
    Sheet animIdle;
    Sheet animWalk;
    Sheet animJump;
    Sheet animAttk;
    Sheet animDefs;
    Sheet animHurt;
    Sheet animDead;
    Sheet animCurr;
    Vector2 pos;

public:
    Hero(Texture2D t);
    ~Hero();
    void Update(float);
    void Draw(float);
};

Hero::Hero(Texture2D t)
{
    Vector2 origin = (Vector2) { 32, 64 };
    animIdle = Sheet(t, 0, 32, 32, origin, 6, 4);
    animWalk = Sheet(t, 1, 32, 32, origin, 6, 6);
    animJump = Sheet(t, 2, 32, 32, origin, 6, 3);
    animAttk = Sheet(t, 3, 32, 32, origin, 10, 6);
    animDefs = Sheet(t, 4, 32, 32, origin, 10, 6);
    animHurt = Sheet(t, 5, 32, 32, origin, 6, 3);
    animDead = Sheet(t, 6, 32, 32, origin, 4, 4);
    animDead.loop = false;
    animCurr = animIdle;
}

Hero::~Hero()
{
}

void Hero::Update(float dt)
{
    animCurr.Update(dt);
}

void Hero::Draw(float scale)
{
    animCurr.Draw(pos, scale);
}

#endif
