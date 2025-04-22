#include "DefaultUIState.h"
#include "ImageGDIPlusManager.h"
#include "UIElementImage.h"
#include "UIElementText.h"
#include "UIManager.h"


HRESULT DefaultUIState::Init()
{
	// �̹���
	auto& manager = *ImageGDIPlusManager::GetInstance();
	auto OtherInterfaceInfoBoxImage = manager.AddImage("OtherInterfaceInfoBox", L"Image/UIImage/DefaultUIState/OtherInterfaceInfoBox.png");
	auto PokemonInfoBoxImage = manager.AddImage("PokemonInfoBox", L"Image/UIImage/DefaultUIState/PokemonInfoBox.png");
	auto MapInfoBoxImage = manager.AddImage("MapInfoBox", L"Image/UIImage/DefaultUIState/MapInfoBox.png");
	auto CursorImage = manager.AddImage("Cursor", L"Image/UIImage/DefaultUIState/Cursor.png");

	// UI ������Ʈ ����
	OtherInterfaceInfoBox = new UIElementImage();
	PokemonInfoBox = new UIElementImage();
	MapInfoBox = new UIElementImage();
	Cursor = new UIElementImage();

	OtherInterfaceInfoBox->SetImage(OtherInterfaceInfoBoxImage);
	PokemonInfoBox->SetImage(PokemonInfoBoxImage);
	MapInfoBox->SetImage(MapInfoBoxImage);
	Cursor->SetImage(CursorImage);

	// UI ������Ʈ ��ġ ����
	OtherInterfaceInfoBox->SetLocalPos(25, 10);
	MapInfoBox->SetLocalPos((GameViewSize_X - MapInfoBoxImage->GetWidth()) - 25, 40);
	PokemonInfoBox->SetLocalPos(25, GameViewSize_Y - 170);
	Cursor->SetLocalPos(25, OffsetY[YIndex]);

	// ���� ����
	OtherInterfaceInfoBox->setAlpha(0.7f);
	MapInfoBox->setAlpha(0.7f);
	PokemonInfoBox->setAlpha(0.7f);

	// �̹��� ũ�� �� ������
	OtherInterfaceInfoBox->setScale(1.0f, 1.0f);
	MapInfoBox->setScale(1.0f, 1.0f);
	PokemonInfoBox->setScale(1.0f, 1.0f);

	// �θ� ��ü�� ����
	OtherInterfaceInfoBox->SetParent(this);
	PokemonInfoBox->SetParent(this);
	MapInfoBox->SetParent(this);

	// �θ���ġ ��ӹ޴� �ڽ� ��ü
	Cursor->SetParent(OtherInterfaceInfoBox);

	UpdateRealPos();

	return S_OK;
}

void DefaultUIState::Release()
{
}

void DefaultUIState::Update()
{
	fadeOutTime += TimerManager::GetInstance()->GetDeltaTime();
	fadeInTime = (sinf(fadeOutTime * 6.0f) * 0.5f) + 0.5f;

	if (KeyManager::GetInstance()->IsOnceKeyDown(VK_DOWN))
	{
		YIndex = (YIndex + 1) % 3;
		Cursor->SetLocalPos(25, OffsetY[YIndex]);
		Cursor->UpdateRealPos();
	}
	else if (KeyManager::GetInstance()->IsOnceKeyDown(VK_UP))
	{
		YIndex = (YIndex - 1 + 3) % 3;
		Cursor->SetLocalPos(25, OffsetY[YIndex]);
		Cursor->UpdateRealPos();
	}

	Cursor->setAlpha(fadeInTime);

	if (KeyManager::GetInstance()->IsOnceKeyDown(0x5A))
	{
		UIManager::GetInstance()->ChangeState("SkillUI");
	}

}

void DefaultUIState::Render(HDC hdc)
{
	OtherInterfaceInfoBox->Render(hdc);
	PokemonInfoBox->Render(hdc);
	MapInfoBox->Render(hdc);
	Cursor->Render(hdc);


}

DefaultUIState::~DefaultUIState()
{
}
