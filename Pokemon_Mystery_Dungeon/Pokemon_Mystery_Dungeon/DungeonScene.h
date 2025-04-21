#pragma once
#include "GameObject.h"
#include "Map.h"

class Player;
class MPlayer;
class Map;

class DungeonScene :public GameObject
{
public:
	virtual HRESULT Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	DungeonScene() {};
	virtual ~DungeonScene() {};


private:
	Map map;
	Image* sampleTile;
	MPlayer* mPlayer;

	int dungeonFloor;
	POINT stairPos;

	TileType tiles[TILE_Y][TILE_X];
	std::vector<POINT> wallTiles;
};

