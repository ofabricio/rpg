#ifndef SPRITE_H
#define SPRITE_H

#include <raylib.h>

typedef struct Sheet {
    Texture2D t;
    Rectangle frames[8];
    Vector2 origin;
    int len;
    int frame;
    bool loop;
    float fps;
    float time;
} Sheet;

Sheet Sheet_New(Texture2D t, int id, int spriteW, int spriteH, Vector2 origin, int fps, int frames)
{
    Sheet s = { 0 };
    s.t = t;
    s.origin = origin;
    s.fps = fps;
    s.len = frames;
    s.loop = true;
    for (size_t i = 0; i < frames; i++) {
        s.frames[i] = (Rectangle) { spriteW * i, spriteH * id, spriteW, spriteH };
    }
    return s;
}

void Sheet_Play(Sheet* s)
{
    s->time = 0.0f;
}

void Sheet_Update(Sheet* s, float dt)
{
    s->frame = (int)(s->time * s->fps) % s->len;
    if (!s->loop && s->frame == s->len - 1) {
        return;
    }
    s->time += dt;
}

void Sheet_Draw(Sheet* s, Vector2 p, float scale)
{
    Rectangle src = s->frames[s->frame];
    Rectangle dst = { p.x, p.y, src.width * scale, src.height * scale };
    DrawTexturePro(s->t, src, dst, s->origin, 0, WHITE);

    // Debug.
    dst.x -= s->origin.x;
    dst.y -= s->origin.y;
    DrawCircleLinesV(p, 10, RED);
    DrawRectangleLinesEx(dst, 1, RED);
    DrawText(TextFormat("F=%d", s->frame), p.x + src.width + 1, p.y - dst.height, 10, BLUE);
}

#endif
