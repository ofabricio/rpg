#include <raylib.h>
#include <raymath.h>
#include <stdio.h>

#include "enemy.h"
#include "hero.h"
#include "sprite.h"
#include "world.h"

int main(int argc, char* argv[])
{
    const float gameScale = 2.0f;
    const int screenWidth = 1280;
    const int screenHeight = screenWidth / 16 * 9;

    InitWindow(screenWidth, screenHeight, "rpg");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(60);

    World world = { 0 };
    World_Init(&world);

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
        Vector2 m = GetScreenToWorld2D(GetMousePosition(), camera);

        camera.zoom += GetMouseWheelMove() * dt * 10;
        if (camera.zoom >= 2.0f)
            camera.zoom = 2.0f;
        if (camera.zoom <= 0.5f)
            camera.zoom = 0.5f;

        Hero_Update(&hero, dt);
        Enemy_Update(&enemy, dt);

        Vector2 p = { 0 };
        int x = 0, y = 0;
        World_PosToGrid(&world, m, &x, &y);
        World_GridToPos(&world, x, y, &p);
        DrawText(TextFormat("MouseInWorld: %.2f, %.2f", m.x, m.y), 10, 50, 20, WHITE);
        DrawText(TextFormat("PosToGrid: %d, %d", x, y), 10, 70, 20, WHITE);
        DrawText(TextFormat("GridToPos: %.2f, %.2f", p.x, p.y), 10, 90, 20, WHITE);

        BeginDrawing();
        {
            // Scene draw.

            ClearBackground(BLACK);
            BeginMode2D(camera);
            {
                World_Draw(&world, gameScale);
                Hero_Draw(&hero, gameScale);
                Enemy_Draw(&enemy, gameScale);
            }
            EndMode2D();

            // UI draw.

            DrawFPS(10, 10);
            DrawText(TextFormat("Zoom: %.2f", camera.zoom), 10, 30, 20, SKYBLUE);
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}