#ifndef ENEMY_H
#define ENEMY_H

#include "sprite.hpp"

class Enemy {
public:
    Vector2 pos;

public:
    Enemy();
    ~Enemy();
    void Update(float);
    void Draw(float);
};

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::Update(float dt)
{
}

void Enemy::Draw(float scale)
{
}

#endif
