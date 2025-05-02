#include "LevelEditor.h"
#include <fstream>

void LevelEditor::PlaceTile(int x, int y, int id) {
    // Alte Kachel an gleicher Position entfernen
    for (auto it = tiles.begin(); it != tiles.end(); ++it) {
        if (it->x == x && it->y == y) {
            tiles.erase(it);
            break;
        }
    }
    tiles.push_back({ x, y, id });
}

void LevelEditor::RemoveTile(int x, int y) {
    for (auto it = tiles.begin(); it != tiles.end(); ++it) {
        if (it->x == x && it->y == y) {
            tiles.erase(it);
            break;
        }
    }
}

void LevelEditor::DrawEditor(HDC hdc) {
    for (const auto& tile : tiles) {
        RECT rect = { tile.x * 32, tile.y * 32, tile.x * 32 + 32, tile.y * 32 + 32 };
        HBRUSH brush = CreateSolidBrush(RGB(100 * tile.id, 100, 255 - 50 * tile.id));
        FillRect(hdc, &rect, brush);
        DeleteObject(brush);
        Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
    }
}

void LevelEditor::SaveMap(const std::string& filename) {
    std::ofstream out(filename);
    for (const auto& tile : tiles) {
        out << tile.id << " " << tile.x << " " << tile.y << "\n";
    }
}

void LevelEditor::LoadMap(const std::string& filename) {
    std::ifstream in(filename);
    tiles.clear();
    int id, x, y;
    while (in >> id >> x >> y) {
        tiles.push_back({ x, y, id });
    }
}
