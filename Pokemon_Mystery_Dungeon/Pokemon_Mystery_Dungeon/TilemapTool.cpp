#include "Image.h"
#include "CommonFunction.h"
#include <functional>
#include "TilemapTool.h"


HRESULT TilemapTool::Init()
{
	SetClientRect(g_hWnd, TILEMAPTOOL_X, TILEMAPTOOL_Y);

	sampleTile = ImageManager::GetInstance()->AddImage(
		"smapleTile", L"Image/SceneImage/TiniWoods3.bmp",
		525, 600, SAMPLE_TILE_X, SAMPLE_TILE_Y,
		true , RGB(255, 0, 255));

	// ���� Ÿ�� ����
	rcSampleTile.left = TILEMAPTOOL_X - sampleTile->GetWidth();
	rcSampleTile.top = 0;
	rcSampleTile.right = TILEMAPTOOL_X;
	rcSampleTile.bottom = sampleTile->GetHeight();

	for (int i = 0; i < TILE_Y; ++i)
	{
		for (int j = 0; j < TILE_X; ++j)
		{
			tileInfo[i * TILE_X + j].frameX = 4;
			tileInfo[i * TILE_X + j].frameY = 1;
			tileInfo[i * TILE_X + j].rc.left = j * TILE_SIZE;
			tileInfo[i * TILE_X + j].rc.top = i * TILE_SIZE;
			tileInfo[i * TILE_X + j].rc.right = 
				tileInfo[i * TILE_X + j].rc.left + TILE_SIZE;
			tileInfo[i * TILE_X + j].rc.bottom = 
				tileInfo[i * TILE_X + j].rc.top + TILE_SIZE;
		}
	}

	// ���� Ÿ�� ����
	rcMain.left = 0;
	rcMain.top = 0;
	rcMain.right = TILE_X * TILE_SIZE;
	rcMain.bottom = TILE_Y * TILE_SIZE;

	return S_OK;
}

void TilemapTool::Release()
{

}

void TilemapTool::Update()
{
	if (PtInRect(&rcSampleTile, g_ptMouse))
	{
		if (KeyManager::GetInstance()->IsOnceKeyDown(VK_LBUTTON))
		{
			int posX = g_ptMouse.x - rcSampleTile.left;
			int posY = g_ptMouse.y - rcSampleTile.top;
			selectedTile.x = posX / TILE_SELECT_SIZE;
			selectedTile.y = posY / TILE_SELECT_SIZE;
		}
	}
	else if (PtInRect(&rcMain, g_ptMouse))
	{
		if (KeyManager::GetInstance()->IsStayKeyDown(VK_LBUTTON))
		{
			int posX = g_ptMouse.x;
			int posY = g_ptMouse.y;
			int tileX = posX / TILE_SELECT_SIZE;
			int tileY = posY / TILE_SELECT_SIZE;
			tileInfo[tileY * TILE_X + tileX].frameX = selectedTile.x;
			tileInfo[tileY * TILE_X + tileX].frameY = selectedTile.y;
		}
	}
	if (KeyManager::GetInstance()->IsOnceKeyDown(VK_F2)) {
		Save();
	}
	if (KeyManager::GetInstance()->IsOnceKeyDown(VK_F3)) {
		Load();
	}

}

void TilemapTool::Render(HDC hdc)
{
	PatBlt(hdc, 0, 0, TILEMAPTOOL_X, TILEMAPTOOL_Y, WHITENESS);

	// ���� Ÿ�� ����
	for (int i = 0; i < TILE_X * TILE_Y; ++i)
	{
		sampleTile->FrameRender(hdc, tileInfo[i].rc.left,
			tileInfo[i].rc.top, tileInfo[i].frameX,
			tileInfo[i].frameY, false, false);
	}

	// ���� Ÿ�� ����
	sampleTile->Render(hdc, TILEMAPTOOL_X - sampleTile->GetWidth(), 0);

	// ���õ� Ÿ��
	sampleTile->FrameRender(hdc, 
		TILEMAPTOOL_X - sampleTile->GetWidth(),
		sampleTile->GetHeight() + 100,
		selectedTile.x, selectedTile.y, false, false);
	

	// ����Ÿ�� �������� ������ Ÿ�� ǥ��
	int sampleTileStartX = TILEMAPTOOL_X - sampleTile->GetWidth();
	sampleTile->Render(hdc, sampleTileStartX, 0);
	{
		HPEN hOldPen;
		HPEN hRedPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		hOldPen = (HPEN)SelectObject(hdc, hRedPen);
		HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));

		Rectangle(hdc,
			sampleTileStartX + selectedTile.x * TILE_SELECT_SIZE,
			selectedTile.y * TILE_SELECT_SIZE,
			sampleTileStartX + (selectedTile.x + 1) * TILE_SELECT_SIZE,
			(selectedTile.y + 1) * TILE_SELECT_SIZE);

		SelectObject(hdc, hOldPen);
		SelectObject(hdc, hOldBrush);
		DeleteObject(hRedPen);
	}

}

void TilemapTool::Save()
{
	// ���� ����
	HANDLE hFile = CreateFile(
		L"TileMapData.dat", GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBox(g_hWnd, TEXT("���� ���� ����"), TEXT("���"), MB_OK);
		return;
	}
	DWORD dwByte = 0;
	WriteFile(hFile, tileInfo, sizeof(tileInfo), &dwByte, NULL);
	CloseHandle(hFile);
	MessageBox(g_hWnd, TEXT("Ÿ�ϸ��� ���������� ����Ǿ����ϴ�."), TEXT("�Ϸ�"), MB_OK);
}

void TilemapTool::Load()
{	
	// ���� �ε�
	HANDLE hFile = CreateFile(
		L"TileMapData.dat", GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBox(g_hWnd, TEXT("���� ���� ����"), TEXT("���"), MB_OK);
		return;
	}
	DWORD dwByte = 0;
	if (!ReadFile(hFile, tileInfo, sizeof(tileInfo), &dwByte, NULL))
	{
		MessageBox(g_hWnd, TEXT("���� �б� ����"), TEXT("���"), MB_OK);
	}
	CloseHandle(hFile);
	MessageBox(g_hWnd, TEXT("Ÿ�ϸ��� ���������� �ε�Ǿ����ϴ�."), TEXT("�Ϸ�"), MB_OK);
}
