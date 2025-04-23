#include "InfoUIState.h"

#include "ImageGDIPlusManager.h"
#include "ImageManager.h"
#include "UIElementImage.h"
#include "UIElementText.h"

HRESULT InfoUIState::Init()
{
    auto& manager = *ImageManager::GetInstance();
    auto FirstInfoBoxImage = manager.AddImage(
        "FirstInfoBox", L"Image/UIImage/InfoUIState/ExistsInfoBox.bmp", 300,
        50);
    auto SecondInfoBoxImage = manager.AddImage(
        "SecondInfoBox", L"Image/UIImage/InfoUIState/NotExistsInfoBox.bmp", 300,
        50);
    auto ThirdInfoBoxImage = manager.AddImage(
        "ThirdInfoBox", L"Image/UIImage/InfoUIState/NotExistsInfoBox.bmp", 300,
        50);
    auto FourthInfoBoxImage = manager.AddImage(
        "FourthInfoBox", L"Image/UIImage/InfoUIState/NotExistsInfoBox.bmp", 300,
        50);

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

    FirstInfoBox->SetParent(this);
    SecondInfoBox->SetParent(this);
    ThirdInfoBox->SetParent(this);
    FourthInfoBox->SetParent(this);

    // �ڽ� ��ü ���� waterTypeText
    NameText = new UIElementText();
    NameText->SetText(L"���� �̸�");
    NameText->SetFont(L"Arial", 20);
    NameText->SetTextColor(255, 255, 255, 255);  // ���
    NameText->SetLocalPos(50, 0);
    NameText->SetParent(FirstInfoBox);

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
