#include <raylib.h>
#include <raymath.h>
#include <stdio.h>

#include "enemy.h"
#include "hero.h"
#include "sprite.h"

int main(int argc, char* argv[])
{
    const float gameScale = 2.0f;
    const int screenWidth = 1280;
    const int screenHeight = screenWidth / 16 * 9;

    InitWindow(screenWidth, screenHeight, "rpg");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(60);

    Hero hero = { 0 };
    Hero_Init(&hero, LoadTexture("assets/shieldman.png"));

    Enemy enemy = { 0 };
    Enemy_Init(&enemy, LoadTexture("assets/sprites.png"));
    enemy.pos = (Vector2) { 64, 0 };

    Camera2D camera = { 0 };
    camera.target = (Vector2) { 0 };
    camera.offset = (Vector2) { (float)screenWidth / 2.0f, (float)screenHeight / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    while (!WindowShouldClose()) {

        float dt = GetFrameTime();

        camera.zoom += GetMouseWheelMove() * dt * 10;
        if (camera.zoom >= 2.0f)
            camera.zoom = 2.0f;
        if (camera.zoom <= 0.5f)
            camera.zoom = 0.5f;

        Hero_Update(&hero, dt);
        Enemy_Update(&enemy, dt);

        Vector2 m = GetScreenToWorld2D(GetMousePosition(), camera);
        hero.pos = Vector2MoveTowards(hero.pos, m, dt * 100);

        BeginDrawing();
        {
            // Scene draw.

            ClearBackground(BLACK);
            BeginMode2D(camera);
            {
                Hero_Draw(&hero, gameScale);
                Enemy_Draw(&enemy, gameScale);
            }
            EndMode2D();

            // UI draw.

            DrawFPS(10, 10);
            DrawText(TextFormat("zoom: %.2f", camera.zoom), 10, 40, 10, SKYBLUE);
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}