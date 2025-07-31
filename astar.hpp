#ifndef ASTAR_HPP
#define ASTAR_HPP

#include <algorithm>
#include <map>
#include <queue>
#include <raylib.h>
#include <raymath.h>
#include <set>
#include <vector>

#include "tilemap.hpp"

namespace astar {

struct Node {
    int g = 0, h = 0, f = 0;
    int col = 0, row = 0;
    int parentCol = -1, parentRow = -1;
    bool hasParent = false;
};

std::vector<Vector2> Find(TileMap m, Vector2 ini, Vector2 end)
{
    auto [iniCol, iniRow] = m.ToCell(ini);
    auto [endCol, endRow] = m.ToCell(end);

    if (!m.IsInGrid(iniCol, iniRow) || !m.IsInGrid(endCol, endRow)) {
        return {};
    }

    if (iniCol == endCol && iniRow == endRow) {
        return {};
    }

    // Use a map to store nodes.
    std::map<std::pair<int, int>, Node> nodes;
    std::set<std::pair<int, int>> visited;

    // Priority queue.
    auto compare = [&nodes](const std::pair<int, int>& a, const std::pair<int, int>& b) {
        return nodes[a].f > nodes[b].f;
    };
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(compare)> openList(compare);

    // Create start node
    Node startNode = { 0, 0, 0, iniCol, iniRow, -1, -1, false };
    int deltaX = abs(endCol - iniCol);
    int deltaY = abs(endRow - iniRow);
    startNode.h = (int)(sqrt(deltaX * deltaX + deltaY * deltaY) * 10);
    startNode.f = startNode.h;

    nodes[{ iniCol, iniRow }] = startNode;
    openList.push({ iniCol, iniRow });

    // 8-directional movement: {dx, dy, cost}
    int directions[8][3] = {
        { 0, -1, 10 }, { 0, 1, 10 }, { -1, 0, 10 }, { 1, 0, 10 }, // up, down, left, right
        { -1, -1, 14 }, { -1, 1, 14 }, { 1, -1, 14 }, { 1, 1, 14 } // diagonals
    };

    while (!openList.empty()) {
        auto currentPos = openList.top();
        openList.pop();

        if (visited.count(currentPos))
            continue;
        visited.insert(currentPos);

        Node& current = nodes[currentPos];

        // Check if we reached the goal
        if (current.col == endCol && current.row == endRow) {
            // Reconstruct path
            std::vector<Vector2> path;
            std::pair<int, int> pos = currentPos;

            while (nodes[pos].hasParent || (pos.first == iniCol && pos.second == iniRow)) {
                Vector2 worldPos = m.ToCenter(pos.first, pos.second);
                path.push_back(worldPos);

                if (!nodes[pos].hasParent)
                    break;
                pos = { nodes[pos].parentCol, nodes[pos].parentRow };
            }

            std::reverse(path.begin(), path.end());
            return path;
        }

        // Check all neighbors.
        for (int i = 0; i < 8; i++) {
            int newCol = current.col + directions[i][0];
            int newRow = current.row + directions[i][1];

            if (!m.IsInGrid(newCol, newRow) || visited.count({ newCol, newRow }) || m.IsObstacle(newCol, newRow)) {
                continue;
            }

            int newG = current.g + directions[i][2];
            auto neighborPos = std::make_pair(newCol, newRow);

            // If neighbor doesn't exist or we found a better path.
            if (nodes.find(neighborPos) == nodes.end() || newG < nodes[neighborPos].g) {
                Node& neighbor = nodes[neighborPos]; // Creates if doesn't exist
                neighbor.col = newCol;
                neighbor.row = newRow;
                neighbor.g = newG;

                int deltaX = abs(endCol - newCol);
                int deltaY = abs(endRow - newRow);
                neighbor.h = (int)(sqrt(deltaX * deltaX + deltaY * deltaY) * 10);
                neighbor.f = neighbor.g + neighbor.h;

                neighbor.parentCol = current.col;
                neighbor.parentRow = current.row;
                neighbor.hasParent = true;

                openList.push(neighborPos);
            }
        }
    }

    return {}; // No path found.
}

};

#endif
