#include "SquareScene.h"
#include "Image.h"
#include "CommonFunction.h"
#include "TilemapTool.h"


#define SQUARESIZE_X 954
#define SQUARESIZE_Y 714

HRESULT SquareScene::Init()
{
	SetClientRect(g_hWnd, SQUARESIZE_X, SQUARESIZE_Y -14);

	backGround = new Image();
	//954, 714
	if (FAILED(backGround->Init(TEXT("Image/SceneImage/Square.bmp"), SQUARESIZE_X, SQUARESIZE_Y)))
	{
		MessageBox(g_hWnd,
			TEXT("Image/backGround.bmp ���� ����"), TEXT("���"), MB_OK);
		return E_FAIL;
	}


	return S_OK;

}

void SquareScene::Release()
{

}

void SquareScene::Update()
{
	if (KeyManager::GetInstance()->IsOnceKeyDown(VK_F1)) {

		SceneManager::GetInstance()->AddScene("Ÿ�ϸ���", new TilemapTool());
		SceneManager::GetInstance()->ChangeScene("Ÿ�ϸ���");

	}
}

void SquareScene::Render(HDC hdc)
{
	backGround->Render(hdc);

}
