#include "CameraTestScene.h"
#include "ImageGDIPlusManager.h"
#include "CameraManager.h"
#include "DialogueUIState.h"
#include "UIManager.h"
#include "DialogueManager.h"
#include "DialogueTemplate.h"
#include "ImageManager.h"
#include "Image.h"

#define SQUARESIZE_X 954
#define SQUARESIZE_Y 714

HRESULT CameraTestScene::Init()
{
	backGround = ImageManager::GetInstance()->AddImage(
		"������", L"Image/SceneImage/Square3.bmp",
		SQUARESIZE_X, SQUARESIZE_Y, 1, 1,
		0, RGB(255, 0, 255));

	UIManager::GetInstance()->RegisterAllUIStates();

	CameraManager::GetInstance()->Init(GameViewSize_X, GameViewSize_Y, 1420, 700);
	UIManager::GetInstance()->AddState("dialogueBox", new DialogueUIState());


	return S_OK;
}

void CameraTestScene::Release()
{
}

void CameraTestScene::Update()
{
	POINT mouse;
	GetCursorPos(&mouse);
	ScreenToClient(g_hWnd, &mouse);
	CameraManager::GetInstance()->SetCameraPos(mouse.x, mouse.y);

	if (KeyManager::GetInstance()->IsOnceKeyDown(VK_TAB))
	{
		UIManager::GetInstance()->OpenUIStateBox("defaultUI");
	}
	// IŰ ������ dialogueBox UI ���·� ��ȯ + �׽�Ʈ ��� ���
	if (KeyManager::GetInstance()->IsOnceKeyDown(0x49)) // 'I' Ű
	{
		DialogueManager::GetInstance()->ShowLine(DialogueTemplate::FoundItem,{ {L"itemName", L"Monster Ball"} });
	}

	if (KeyManager::GetInstance()->IsOnceKeyDown(0x44)) // 'D' Ű
	{
		UIManager::GetInstance()->OpenUIStateBox("DungeonUI");
	}

	UIManager::GetInstance()->Update();
}

void CameraTestScene::Render(HDC hdc)
{
	RECT cam = CameraManager::GetInstance()->GetViewPos();

	if (backGround) {
		backGround->RenderBackground(hdc);
	}
	UIManager::GetInstance()->Render(hdc);
}
