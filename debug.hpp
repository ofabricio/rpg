#ifndef DEBUG_H
#define DEBUG_H

#include <raylib.h>

namespace Debug {

void DrawPoint(Vector2 p, Color color)
{
    auto txt = TextFormat("%.2f, %.2f", p.x, p.y);
    DrawCircleLines(p.x, p.y, 3, color);
    DrawText(txt, p.x + 7, p.y - 5, 10, color);
}

};

#endif
