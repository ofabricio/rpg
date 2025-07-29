#ifndef ENEMY_H
#define ENEMY_H

#include "sprite.hpp"

class Enemy {
private:
    Sheet animIdle;
    Sheet animWalk;
    Sheet animJump;
    Sheet animAttk;
    Sheet animDefs;
    Sheet animHurt;
    Sheet animDead;
    Sheet animCurr;

public:
    Vector2 pos;

public:
    Enemy(Texture2D t);
    ~Enemy();
    void Update(float);
    void Draw(float);
};

Enemy::Enemy(Texture2D t)
{
    Vector2 origin = (Vector2) { 16, 48 };
    animIdle = Sheet(t, 0, 16, 24, origin, 6, 4);
    animWalk = Sheet(t, 1, 16, 24, origin, 6, 6);
    animJump = Sheet(t, 2, 16, 24, origin, 6, 3);
    animAttk = Sheet(t, 3, 16, 24, origin, 10, 6);
    animDefs = Sheet(t, 4, 16, 24, origin, 10, 6);
    animHurt = Sheet(t, 5, 16, 24, origin, 6, 3);
    animDead = Sheet(t, 6, 16, 24, origin, 4, 4);
    animDead.loop = false;
    animCurr = animIdle;
}

Enemy::~Enemy()
{
}

void Enemy::Update(float dt)
{
    animCurr.Update(dt);
}

void Enemy::Draw(float scale)
{
    animCurr.Draw(pos, scale);
}

#endif
