#include <raylib.h>
#include <raymath.h>
#include <stdio.h>

#include "enemy.hpp"
#include "hero.hpp"
#include "sprite.hpp"
#include "world.hpp"

int main(int argc, char* argv[])
{
    const float spriteSize = 32.0f;
    const int screenWidth = spriteSize * 48;
    const int screenHeight = spriteSize * 30;

    const float gameScale = 2.0f;

    InitWindow(screenWidth, screenHeight, "rpg");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(60);

    World world = {};
    world.Init();

    Hero hero(LoadTexture("assets/shieldman.png"));

    Enemy enemy(LoadTexture("assets/sprites.png"));
    enemy.pos = (Vector2) { 64, 0 };

    Camera2D camera = {};
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

        hero.Update(dt);
        enemy.Update(dt);

        Vector2 p = { 0 };
        int x = 0, y = 0;
        world.PosToGrid(m, &x, &y);
        world.GridToPos(x, y, &p);
        DrawText(TextFormat("MouseInWorld: %.2f, %.2f", m.x, m.y), 10, 50, 20, WHITE);
        DrawText(TextFormat("PosToGrid: %d, %d", x, y), 10, 70, 20, WHITE);
        DrawText(TextFormat("GridToPos: %.2f, %.2f", p.x, p.y), 10, 90, 20, WHITE);

        BeginDrawing();
        {
            // Scene draw.

            ClearBackground(BLACK);
            BeginMode2D(camera);
            {
                world.Draw(gameScale);
                hero.Draw(gameScale);
                enemy.Draw(gameScale);
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