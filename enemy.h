#ifndef ENEMY_H
#define ENEMY_H

#include "sprite.h"

typedef struct Enemy {
    Sheet animIdle;
    Sheet animWalk;
    Sheet animJump;
    Sheet animAttk;
    Sheet animDefs;
    Sheet animHurt;
    Sheet animDead;
    Sheet animCurr;
    Vector2 pos;
} Enemy;

void Enemy_Init(Enemy* e, Texture2D t)
{
    Vector2 origin = (Vector2) { 16, 48 };
    e->animIdle = Sheet_New(t, 0, 16, 24, origin, 6, 4);
    e->animWalk = Sheet_New(t, 1, 16, 24, origin, 6, 6);
    e->animJump = Sheet_New(t, 2, 16, 24, origin, 6, 3);
    e->animAttk = Sheet_New(t, 3, 16, 24, origin, 10, 6);
    e->animDefs = Sheet_New(t, 4, 16, 24, origin, 10, 6);
    e->animHurt = Sheet_New(t, 5, 16, 24, origin, 6, 3);
    e->animDead = Sheet_New(t, 6, 16, 24, origin, 4, 4);
    e->animDead.loop = false;
    e->animCurr = e->animIdle;
}

void Enemy_Update(Enemy* e, float dt)
{
    Sheet_Update(&e->animCurr, dt);
}

void Enemy_Draw(Enemy* e, float scale)
{
    Sheet_Draw(&e->animCurr, e->pos, scale);
}

#endif
