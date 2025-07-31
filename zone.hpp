#ifndef ZONE_HPP
#define ZONE_HPP

#include <algorithm>
#include <fstream>
#include <iostream>
#include <raylib.h>
#include <sstream>
#include <string>
#include <vector>

#include "actor.hpp"
#include "gameobj.hpp"
#include "third/parser/parser.hpp"
#include "tilemap.hpp"

class Zone {
public:
    std::string title;
    TileMap tmap;
    std::vector<Actor*> actors;
    std::vector<GameObj*> render;

public:
    Zone(TileMap);
    ~Zone();
    void Add(Actor*);
    void Update(float);
    void Draw();
};

Zone::Zone(TileMap m)
    : tmap(m)
{
}

Zone::~Zone()
{
    actors.clear();
    render.clear();
}

void Zone::Add(Actor* v)
{
    actors.push_back(v);
    render.push_back(v);
}

void Zone::Update(float dt)
{
    for (auto& a : actors) {
        a->Update(dt);
    }
}

void Zone::Draw()
{
    tmap.Draw();
    std::sort(render.begin(), render.end(), [](GameObj* a, GameObj* b) { return a->ZOrder() < b->ZOrder(); });
    for (auto& r : render) {
        r->Draw();
    }
}

class ZoneFileParser {
private:
    Parser p;

public:
    ZoneFileParser(const std::string& content)
        : p(content)
    {
    }

    void ParseHead(int& tile, int& cols, int& rows)
    {
        p.Space();
        p.Match("Tiles=") && p.Number(tile)
            && p.Space()
            && p.Match("Cols=") && p.Number(cols)
            && p.Space()
            && p.Match("Rows=") && p.Number(rows);
    }

    void ParseTitle(std::string* title)
    {
        std::string_view t;
        p.Space();
        if (p.Match("Title=") && p.Out(p.Mark(), p.Line(), t)) {
            t.remove_suffix(1); // Remove newline.
            *title = std::string(t);
        }
        *title = "<null> Zone";
    }

    void ParseWaypoints(std::string_view key, std::vector<int>& waypoints)
    {
        p.Space();
        p.Match(key);
        int v = 0;
        for (size_t i = 0; i < waypoints.size() && ((p.Space() || true) && p.Number(v)); i++) {
            waypoints[i] = v;
        }
    }
};

std::string CreateZoneFileName(int id)
{
    // Construct the filename based on the zone ID.
    std::stringstream stream;
    stream << std::uppercase << std::hex << id;
    std::string filename(stream.str());
    filename = id <= 0x0F ? "0" + filename : filename;
    filename = "assets/zones/" + filename;
    return filename;
}

std::string LoadZoneFileContent(std::string filename)
{
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error opening file '" << filename << "': "
                  << std::strerror(errno) << '\n';
        exit(EXIT_FAILURE);
    }
    std::stringstream buf;
    buf << file.rdbuf();
    file.close();
    return buf.str();
}

Zone LoadZone(int id)
{
    std::string filename = CreateZoneFileName(id);
    std::string content = LoadZoneFileContent(filename);

    std::string title;
    int tile = 0, cols = 0, rows = 0;

    ZoneFileParser p(content);
    p.ParseHead(tile, cols, rows);
    p.ParseTitle(&title);
    auto waypoints = std::vector<int>(cols * rows, 0);
    auto collision = std::vector<int>(cols * rows, 0);
    p.ParseWaypoints("WAYPOINT", waypoints);
    p.ParseWaypoints("COLLISION", collision);

    Zone z(TileMap(Grid(tile, cols, rows), waypoints, collision));
    z.title = title;
    return z;
}

#endif
