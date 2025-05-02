#pragma once
#include <vector>
#include <Windows.h>
#include <string>

struct Tile {
    int x, y;
    int id;
};

class LevelEditor {
public:
    void PlaceTile(int x, int y, int id);
    void RemoveTile(int x, int y);
    void DrawEditor(HDC hdc);
    void SaveMap(const std::string& filename);
    void LoadMap(const std::string& filename);

private:
    std::vector<Tile> tiles;
};
