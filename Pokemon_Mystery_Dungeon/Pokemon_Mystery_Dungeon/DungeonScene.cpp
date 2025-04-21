#include "DungeonScene.h"
#include "Image.h"
#include "CommonFunction.h"
#include "MPlayer.h"

HRESULT DungeonScene::Init()
{
	SetClientRect(g_hWnd, TILE_SIZE * TILE_X, TILE_SIZE * TILE_Y);

	map.Init();

	mPlayer = new MPlayer;
	mPlayer->Init();

	wallTiles = map.GetWallTiles(); //wallTiles��ǥ  Point��

	dungeonFloor = 0;

	stairPos = map.GetStairPos();
	stairPos.x *= TILE_SIZE;
	stairPos.y *= TILE_SIZE;

	return S_OK;
}

void DungeonScene::Release()
{

}

void DungeonScene::Update()
{
	if (KeyManager::GetInstance()->IsOnceKeyDown(VK_F6)) {
		//SceneManager::GetInstance()->AddScene("������", new DungeonScene());
		SceneManager::GetInstance()->ChangeScene("����");
	}
	if (KeyManager::GetInstance()->IsOnceKeyDown(VK_SPACE)) {
		map.Init();
		wallTiles = map.GetWallTiles();
		stairPos = map.GetStairPos();
		stairPos.x *= TILE_SIZE;
		stairPos.y *= TILE_SIZE;
		++dungeonFloor;
	}


	if (mPlayer) {
		mPlayer->Update();
		POINT playerPos = mPlayer->GetPos(); // �÷��̾��� Ÿ�� ��ġ�� �޾ƿ��� �Լ� �ʿ�

		if (abs(playerPos.x - stairPos.x) <= 25 && abs(playerPos.y - stairPos.y) <= 25) {
			map.Init();
			wallTiles = map.GetWallTiles();
			stairPos = map.GetStairPos();
			stairPos.x *= TILE_SIZE;
			stairPos.y *= TILE_SIZE;
			++dungeonFloor;
		}
	}

	
}

void DungeonScene::Render(HDC hdc)
{
	PatBlt(hdc, 0, 0, 2000, 2000, BLACKNESS);

	map.Render(hdc);
	map.MiniMapRender(hdc, 0, 0);

	//for (const POINT& wall : wallTiles) {
	//	RenderRectAtCenter(hdc, wall.x*TILE_SIZE, wall.y*TILE_SIZE, TILE_SIZE, TILE_SIZE);
	//}
	
//	map.Draw(hdc);
	if (mPlayer) {
		mPlayer->Render(hdc);
	}

}
