#include "InfoUIState.h"
#include "ImageGDIPlusManager.h"
#include "UIElementImage.h"
#include "UIElementText.h"

HRESULT InfoUIState::Init()
{
	auto& manager = *ImageGDIPlusManager::GetInstance();
	auto FirstInfoBoxImage = manager.AddImage("FirstInfoBox", L"Image/UIImage/InfoUIState/ExistsInfoBox.png");
	auto SecondInfoBoxImage = manager.AddImage("SecondInfoBox", L"Image/UIImage/InfoUIState/NotExistsInfoBox.png");
	auto ThirdInfoBoxImage = manager.AddImage("ThirdInfoBox", L"Image/UIImage/InfoUIState/NotExistsInfoBox.png");
	auto FourthInfoBoxImage = manager.AddImage("FourthInfoBox", L"Image/UIImage/InfoUIState/NotExistsInfoBox.png");

	// UI ������Ʈ ����
	FirstInfoBox = new UIElementImage();
	SecondInfoBox = new UIElementImage();
	ThirdInfoBox = new UIElementImage();
	FourthInfoBox = new UIElementImage();

	FirstInfoBox->SetImage(FirstInfoBoxImage);
	SecondInfoBox->SetImage(SecondInfoBoxImage);
	ThirdInfoBox->SetImage(ThirdInfoBoxImage);
	FourthInfoBox->SetImage(FourthInfoBoxImage);

	// UI ������Ʈ ��ġ ����
	FirstInfoBox->SetLocalPos(InfoBoxPosX, InfoBoxPosYOffset[0]);
	SecondInfoBox->SetLocalPos(InfoBoxPosX, InfoBoxPosYOffset[1]);
	ThirdInfoBox->SetLocalPos(InfoBoxPosX, InfoBoxPosYOffset[2]);
	FourthInfoBox->SetLocalPos(InfoBoxPosX, InfoBoxPosYOffset[3]);

	UpdateRealPos();

	return S_OK;
}

void InfoUIState::Release()
{
}

void InfoUIState::Update()
{
}

void InfoUIState::Render(HDC hdc)
{
	FirstInfoBox->Render(hdc);
	SecondInfoBox->Render(hdc);
	ThirdInfoBox->Render(hdc);
	FourthInfoBox->Render(hdc);
	// �ؽ�Ʈ ������
}

InfoUIState::~InfoUIState()
{
}

void InfoUIState::SetInfoBoxText(int index, const wstring& text)
{
}

