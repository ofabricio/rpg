#include <raylib.h>
#include <raymath.h>
#include <stdio.h>

#include "consts.hpp"
#include "debug.hpp"
#include "enemy.hpp"
#include "grid.hpp"
#include "hero.hpp"
#include "sprite.hpp"

int main(int argc, char* argv[])
{
    const float gameScale = 2.0f;

    InitWindow(SCREEN_W * gameScale, SCREEN_H * gameScale, "rpg");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(60);

    Grid grid(CELL, GRID_COLS, GRID_ROWS);

    Hero hero = {};

    Enemy enemy = {};
    enemy.pos = Vector2(64, 0);

    Camera2D camera = {};
    camera.target = Vector2(SCREEN_W / 2.0f, SCREEN_H / 2.0f);
    camera.offset = Vector2(SCREEN_W * gameScale / 2.0f, SCREEN_H * gameScale / 2.0f);
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
        // camera.zoom = 2.0f;

        hero.Update(dt);
        enemy.Update(dt);

        BeginDrawing();
        {
            // Scene draw.

            ClearBackground(BLACK);
            BeginMode2D(camera);
            {
                grid.Draw(gameScale, SCREEN_W, SCREEN_H);
                hero.Draw(gameScale);
                enemy.Draw(gameScale);

                auto [col, row] = grid.PosToGrid(m);
                auto v = grid.GridToPos(col, row);
                DrawRectangleLines(v.x, v.y, CELL, CELL, grid.IsInGrid(col, row) ? GREEN : RED);

                Debug::DrawPoint(Vector2(0, 0), SKYBLUE);
            }
            EndMode2D();

            // UI draw.

            DrawFPS(10, 10);
            DrawText(TextFormat("Zoom: %.2f", camera.zoom), 10, 30, 20, SKYBLUE);
            auto [col, row] = grid.PosToGrid(m);
            auto p = grid.GridToPos(col, row);
            DrawText(TextFormat("MouseInWorld: %.2f, %.2f", m.x, m.y), 10, 50, 20, WHITE);
            DrawText(TextFormat("Grid RowCol: %d, %d", col, row), 10, 70, 20, WHITE);
            DrawText(TextFormat("Grid Pos: %.2f, %.2f", p.x, p.y), 10, 90, 20, WHITE);
            DrawText(TextFormat("Grid ID: %d", grid.GridToID(col, row)), 10, 110, 20, WHITE);
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}