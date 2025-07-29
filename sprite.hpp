#ifndef SPRITE_H
#define SPRITE_H

#include <raylib.h>
#include <stdio.h>

class Sheet {
private:
    Texture2D t;
    Rectangle frames[8];
    Vector2 origin;
    int len;
    int frame;
    float fps;
    float time;

public:
    bool loop;

public:
    Sheet() = default;
    Sheet(Texture2D texture, int id, float spriteW, float spriteH, Vector2 origin, int fps, int frames);
    void Play();
    void Update(float dt);
    void Draw(Vector2 p, float scale);
};

Sheet::Sheet(Texture2D texture, int id, float spriteW, float spriteH, Vector2 origin, int fps, int frames)
{
    t = texture;
    this->origin = origin;
    this->fps = fps;
    len = frames;
    frame = 0;
    loop = true;
    time = 0.0f;

    for (int i = 0; i < frames; i++) {
        this->frames[i] = (Rectangle) { spriteW * (float)i, spriteH * (float)id, spriteW, spriteH };
    }
}

void Sheet::Play() { time = 0.0f; }

void Sheet::Update(float dt)
{
    frame = (int)(time * fps) % len;
    if (!loop && frame == len - 1)
        return;
    time += dt;
}

void Sheet::Draw(Vector2 p, float scale)
{
    Rectangle src = frames[frame];
    Rectangle dst = { p.x, p.y, src.width * scale, src.height * scale };
    DrawTexturePro(t, src, dst, origin, 0, WHITE);

    // Debug.
    dst.x -= origin.x;
    dst.y -= origin.y;
    DrawCircleLinesV(p, 10, RED);
    DrawRectangleLinesEx(dst, 1, RED);
    DrawText(TextFormat("F=%d", frame), p.x + src.width + 1, p.y - dst.height, 10, BLUE);
}

#endif
