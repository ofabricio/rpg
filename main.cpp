#include <raylib.h>
#include <raymath.h>
#include <stdio.h>

#include "actor.hpp"
#include "astar.hpp"
#include "consts.hpp"
#include "debug.hpp"
#include "tilemap.hpp"
#include "zone.hpp"

int main(int argc, char* argv[])
{
    const float gameScale = 2.0f;

    InitWindow(SCREEN_W * gameScale, SCREEN_H * gameScale, "rpg");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(60);

    Zone zone = LoadZone(1);

    Actor hero = {};
    hero.pos = zone.tmap.ToCenter(3, 8);
    hero.name = "Hero";

    Actor enemy = {};
    enemy.pos = zone.tmap.ToCenter(20, 8);
    enemy.name = "Enemy";

    Camera2D camera = {};
    camera.target = Vector2(SCREEN_W / 2.0f, SCREEN_H / 2.0f);
    camera.offset = Vector2(SCREEN_W / 2.0f * gameScale, SCREEN_H / 2.0f * gameScale);
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    auto path = astar::Find(zone.tmap, zone.tmap.ToPos(5, 5), zone.tmap.ToPos(20, 13));

    zone.Add(&enemy);
    zone.Add(&hero);

    while (!WindowShouldClose()) {

        float dt = GetFrameTime();
        Vector2 m = GetScreenToWorld2D(GetMousePosition(), camera);

        camera.zoom += GetMouseWheelMove() * dt * 10;
        if (camera.zoom >= 2.0f)
            camera.zoom = 2.0f;
        if (camera.zoom <= 0.5f)
            camera.zoom = 0.5f;
        // camera.zoom = 2.0f;

        zone.Update(dt);

        BeginDrawing();
        {
            // Scene draw.

            ClearBackground(BLACK);
            BeginMode2D(camera);
            {
                zone.Draw();

                auto [col, row] = zone.tmap.ToCell(m);
                auto v = zone.tmap.ToPos(col, row);
                DrawRectangleLines(v.x, v.y, TILE, TILE, zone.tmap.IsInGrid(col, row) ? GREEN : RED);

                Debug::DrawPoint(Vector2(0, 0), SKYBLUE);

                for (const auto& p : path) {
                    DrawCircleV(p, 5, YELLOW);
                }
            }
            EndMode2D();

            // UI draw.

            DrawFPS(10, 10);
            DrawText(TextFormat("Zoom: %.2f", camera.zoom), 10, 30, 20, SKYBLUE);
            auto [col, row] = zone.tmap.ToCell(m);
            auto p = zone.tmap.ToPos(col, row);
            DrawText(TextFormat("MouseInWorld: %.2f, %.2f", m.x, m.y), 10, 50, 20, WHITE);
            DrawText(TextFormat("Grid RowCol: %d, %d", col, row), 10, 70, 20, WHITE);
            DrawText(TextFormat("Grid Pos: %.2f, %.2f", p.x, p.y), 10, 90, 20, WHITE);
            DrawText(TextFormat("Grid ID: %d", zone.tmap.ToId(col, row)), 10, 110, 20, WHITE);
            DrawText(TextFormat("Obstacle: %d", zone.tmap.IsObstacle(col, row)), 10, 130, 20, WHITE);
            DrawText(TextFormat("Waypoint: %d", zone.tmap.GetWaypoint(col, row)), 10, 150, 20, WHITE);
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}