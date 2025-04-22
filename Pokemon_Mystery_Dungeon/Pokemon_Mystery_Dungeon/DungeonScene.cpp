#include "DungeonScene.h"
#include "Image.h"
#include "CommonFunction.h"
#include "MPlayer.h"
#include "BossScene.h"

HRESULT DungeonScene::Init()
{
	SetClientRect(g_hWnd, TILE_SIZE * TILE_X, TILE_SIZE * TILE_Y);

	mPlayer = new MPlayer;
	mPlayer->Init();

	wallTiles = map.GetWallTiles(); //wallTiles��ǥ  Point��

	dungeonFloor = 0;

	GenerateNextFloor();
	
	return S_OK;
}

void DungeonScene::Release()
{
	if (mPlayer) {
		mPlayer->Release();
		delete mPlayer;
		mPlayer = nullptr;
	}
}

void DungeonScene::Update()
{
	if (KeyManager::GetInstance()->IsOnceKeyDown(VK_F6)) {
		//SceneManager::GetInstance()->AddScene("������", new DungeonScene());
		SceneManager::GetInstance()->ChangeScene("����");
	}
	if (KeyManager::GetInstance()->IsOnceKeyDown(VK_SPACE)) {
		GenerateNextFloor();
	}
	if (dungeonFloor > 5) {
		dungeonFloor = 0;
		SceneManager::GetInstance()->AddScene("������", new BossScene());
		SceneManager::GetInstance()->ChangeScene("������");
	}

	if (mPlayer) {
		mPlayer->Update();
		POINT playerPos = mPlayer->GetPos(); // �÷��̾��� Ÿ�� ��ġ�� �޾ƿ��� �Լ� �ʿ�

		if (IsPlayerOnStair()) {
			++dungeonFloor;
			GenerateNextFloor();
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

void DungeonScene::GenerateNextFloor()
{
	map.Init();
	wallTiles = map.GetWallTiles();
	stairPos = ConvertToPixel(map.GetStairPos());
}

POINT DungeonScene::ConvertToPixel(POINT tilePos)
{
	tilePos.x *= TILE_SIZE;
	tilePos.y *= TILE_SIZE;
	return tilePos;
}

bool DungeonScene::IsPlayerOnStair()
{
	POINT playerPos = mPlayer->GetPos();
	return abs(playerPos.x - stairPos.x) <= TILE_SIZE &&
		abs(playerPos.y - stairPos.y) <= TILE_SIZE;
}