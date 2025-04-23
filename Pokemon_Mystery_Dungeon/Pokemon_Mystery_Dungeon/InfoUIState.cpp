#include "InfoUIState.h"

#include "ImageGDIPlusManager.h"
#include "ImageManager.h"
#include "UIElementImage.h"
#include "UIElementText.h"
#include "Image.h"

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

    auto CurrHpBarImage = manager.AddImage(
        "CurrHpBar", L"Image/UIImage/InfoUIState/CurrHpBar.bmp", 94, 20);
    auto MaxHpBarImage = manager.AddImage(
        "MaxHpBar", L"Image/UIImage/InfoUIState/MaxHpBar.bmp", 103, 26);

    // UI ������Ʈ ����
    FirstInfoBox = new UIElementImage();
    SecondInfoBox = new UIElementImage();
    ThirdInfoBox = new UIElementImage();
    FourthInfoBox = new UIElementImage();

    CurrHpBar = new UIElementImage();
    MaxHpBar = new UIElementImage();

    FirstInfoBox->SetImage(FirstInfoBoxImage);
    SecondInfoBox->SetImage(SecondInfoBoxImage);
    ThirdInfoBox->SetImage(ThirdInfoBoxImage);
    FourthInfoBox->SetImage(FourthInfoBoxImage);

    CurrHpBar->SetImage(CurrHpBarImage);
    MaxHpBar->SetImage(MaxHpBarImage);

    // UI ������Ʈ ��ġ ����
    FirstInfoBox->SetLocalPos(InfoBoxPosX, InfoBoxPosYOffset[0]);
    SecondInfoBox->SetLocalPos(InfoBoxPosX, InfoBoxPosYOffset[1]);
    ThirdInfoBox->SetLocalPos(InfoBoxPosX, InfoBoxPosYOffset[2]);
    FourthInfoBox->SetLocalPos(InfoBoxPosX, InfoBoxPosYOffset[3]);

    MaxHpBar->SetLocalPos(680, 20);
    CurrHpBar->SetLocalPos(680, 20);

    FirstInfoBox->SetParent(this);
    SecondInfoBox->SetParent(this);
    ThirdInfoBox->SetParent(this);
    FourthInfoBox->SetParent(this);

    MaxHpBar->SetParent(nullptr);
    CurrHpBar->SetParent(nullptr);


    // �̸�
    NameText = new UIElementText();
    NameText->SetText(L"Name");
    NameText->SetFont(12);
    NameText->SetTextColorRGB(255, 204, 0);  // ����� ����
    NameText->SetLocalPos(80, 5);
    NameText->SetParent(FirstInfoBox);

    // ����
    LevelText = new UIElementText();
    LevelText->SetText(L"Level");
    LevelText->SetFont(12);
    LevelText->SetTextColorRGB(255, 255, 255);  // ���
    LevelText->SetLocalPos(100,20);
    LevelText->SetParent(FirstInfoBox);

    // HP
    HPText = new UIElementText();
    HPText->SetText(L"HP");
    HPText->SetFont(12);
    HPText->SetTextColorRGB(241, 179, 0);  // ��Ȳ ������
    HPText->SetLocalPos(160, 20);
    HPText->SetParent(FirstInfoBox);

    UpdateRealPos();

    return S_OK;
}

void InfoUIState::Release()
{
}

void InfoUIState::Update()
{
    // hp update 
    barWidth = (int)(CurrHpBar->GetImageWidth() * percent);
    barHeight = CurrHpBar->GetImageHeight();
}

void InfoUIState::Render(HDC hdc)
{

    FirstInfoBox->Render(hdc);
    SecondInfoBox->Render(hdc);
    ThirdInfoBox->Render(hdc);
    FourthInfoBox->Render(hdc);

    MaxHpBar->Render(hdc);
    CurrHpBar->RenderPartial(hdc,  barWidth, barHeight);
    

    // �ؽ�Ʈ ������
}

InfoUIState::~InfoUIState()
{
}

void InfoUIState::SetInfoBoxText(int index, const wstring& text)
{
}
