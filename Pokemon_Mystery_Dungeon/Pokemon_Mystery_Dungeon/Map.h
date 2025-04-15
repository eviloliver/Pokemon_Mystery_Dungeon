#pragma once
#include <vector>
#include "CommonFunction.h"
#include "Room.h"

const int MAP_WIDTH = 50;
const int MAP_HEIGHT = 50;

enum TileType {
    TILE_WALL,
    TILE_FLOOR
};

class Map {
public:
    Map();
    void Generate();                    
    void Draw(HDC hdc);                 

    TileType GetTile(int x, int y) const;
    TileType(*GetTiles())[MAP_WIDTH];  // ��ü Ÿ�� ����
    const std::vector<Room>& GetRooms() const;

private:
    TileType tiles[MAP_HEIGHT][MAP_WIDTH];
    std::vector<Room> rooms;
};