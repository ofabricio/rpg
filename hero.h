#ifndef HERO_H
#define HERO_H

#include "sprite.h"

typedef struct Hero {
    Sheet animIdle;
    Sheet animWalk;
    Sheet animJump;
    Sheet animAttk;
    Sheet animDefs;
    Sheet animHurt;
    Sheet animDead;
    Sheet animCurr;
    Vector2 pos;
} Hero;

void Hero_Init(Hero* h, Texture2D t)
{
    Vector2 origin = (Vector2) { 32, 64 };
    h->animIdle = Sheet_New(t, 0, 32, 32, origin, 6, 4);
    h->animWalk = Sheet_New(t, 1, 32, 32, origin, 6, 6);
    h->animJump = Sheet_New(t, 2, 32, 32, origin, 6, 3);
    h->animAttk = Sheet_New(t, 3, 32, 32, origin, 10, 6);
    h->animDefs = Sheet_New(t, 4, 32, 32, origin, 10, 6);
    h->animHurt = Sheet_New(t, 5, 32, 32, origin, 6, 3);
    h->animDead = Sheet_New(t, 6, 32, 32, origin, 4, 4);
    h->animDead.loop = false;
    h->animCurr = h->animIdle;
}

void Hero_Update(Hero* h, float dt)
{
    Sheet_Update(&h->animCurr, dt);
}

void Hero_Draw(Hero* h, float scale)
{
    Sheet_Draw(&h->animCurr, h->pos, scale);
}

#endif
