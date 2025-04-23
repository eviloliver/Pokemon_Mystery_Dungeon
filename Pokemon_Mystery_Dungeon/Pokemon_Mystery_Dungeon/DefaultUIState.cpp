#include "DefaultUIState.h"

#include "ImageGDIPlusManager.h"
#include "SkillUIState.h"
#include "UIElementImage.h"
#include "UIElementText.h"
#include "UIManager.h"

HRESULT DefaultUIState::Init()
{
    // �̹���
    auto& manager = *ImageGDIPlusManager::GetInstance();
    auto OtherInterfaceInfoBoxImage = manager.AddImage(
        "OtherInterfaceInfoBox",
        L"Image/UIImage/DefaultUIState/OtherInterfaceInfoBox.png");
    auto PokemonInfoBoxImage = manager.AddImage(
        "PokemonInfoBox", L"Image/UIImage/DefaultUIState/PokemonInfoBox.png");
    auto MapInfoBoxImage = manager.AddImage(
        "MapInfoBox", L"Image/UIImage/DefaultUIState/MapInfoBox.png");
    auto CursorImage =
        manager.AddImage("Cursor", L"Image/UIImage/DefaultUIState/Cursor.png");

    // UI ������Ʈ ����
    OtherInterfaceInfoBox = new UIElementImage();
    PokemonInfoBox = new UIElementImage();
    MapInfoBox = new UIElementImage();
    Cursor = new UIElementImage();
    SkillText = new UIElementText();
    ItemText = new UIElementText();
    SettingText = new UIElementText();
    MapNameText = new UIElementText();
    PokemonNameText = new UIElementText();
    PokemonLevelText = new UIElementText();
    PokemonHPText = new UIElementText();

    OtherInterfaceInfoBox->SetImage(OtherInterfaceInfoBoxImage);
    PokemonInfoBox->SetImage(PokemonInfoBoxImage);
    MapInfoBox->SetImage(MapInfoBoxImage);
    Cursor->SetImage(CursorImage);

    /*--------------- �ؽ�Ʈ ���� ---------------*/
    // otherBox
    SkillText->SetText(L"Skill");
    SkillText->SetFont(L"DungGeunMo", 18);
    SkillText->SetTextLine(5.0f);
    SkillText->SetLocalPos(fontPosX, OffsetY[0]);
    SkillText->SetParent(OtherInterfaceInfoBox);

    ItemText->SetText(L"Item");
    ItemText->SetFont(L"Arial", 18);
    ItemText->SetTextLine(5.0f);
    ItemText->SetLocalPos(fontPosX, OffsetY[1]);
    ItemText->SetParent(OtherInterfaceInfoBox);

    SettingText->SetText(L"Setting");
    SettingText->SetFont(L"Arial", 18);
    SettingText->SetTextLine(5.0f);
    SettingText->SetLocalPos(fontPosX, OffsetY[2]);
    SettingText->SetParent(OtherInterfaceInfoBox);

    // mapBox
    MapNameText->SetText(L"Map Name");
    MapNameText->SetFont(L"Arial", 18);
    MapNameText->SetTextLine(5.0f);
    MapNameText->SetLocalPos(50, MapInfoBox->GetImageHeight() / 2 - 10);
    MapNameText->SetParent(MapInfoBox);

    // pokemonInfoBox
    PokemonNameText->SetText(L"Pokemon Name");
    PokemonNameText->SetFont(L"Arial", 18);
    PokemonNameText->SetTextLine(5.0f);
    PokemonNameText->SetTextColor(241, 179, 0, 255);
    PokemonNameText->SetLocalPos(50, PokemonInfoBox->GetImageHeight() / 2 - 10);
    PokemonNameText->SetParent(PokemonInfoBox);

    PokemonLevelText->SetText(L"Level 1");
    PokemonLevelText->SetFont(L"Arial", 18);
    PokemonLevelText->SetTextLine(5.0f);
    PokemonLevelText->SetLocalPos(50,
                                  PokemonInfoBox->GetImageHeight() / 2 + 20);
    PokemonLevelText->SetParent(PokemonInfoBox);

    PokemonHPText->SetText(L"HP 100 / 100");
    PokemonHPText->SetFont(L"Arial", 18);
    PokemonHPText->SetTextLine(5.0f);
    PokemonHPText->SetLocalPos(50, PokemonInfoBox->GetImageHeight() / 2 + 40);
    PokemonHPText->SetParent(PokemonInfoBox);
    /*--------------- �ؽ�Ʈ ���� �� ---------------*/

    // UI ������Ʈ ��ġ ����
    OtherInterfaceInfoBox->SetLocalPos(25, 10);
    MapInfoBox->SetLocalPos((GameViewSize_X - MapInfoBoxImage->GetWidth()) - 25,
                            40);
    PokemonInfoBox->SetLocalPos(25, GameViewSize_Y - 170);
    Cursor->SetLocalPos(25, OffsetY[YIndex]);

    // ���� ����
    OtherInterfaceInfoBox->setAlpha(0.95f);
    MapInfoBox->setAlpha(0.95f);
    PokemonInfoBox->setAlpha(0.95f);

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
        if (YIndex == 0)
        {
            UIManager::GetInstance()->ChangeState("SkillUI");
        }
        else if (YIndex == 1)
        {
            UIManager::GetInstance()->ChangeState("ItemUI");
        }
        else if (YIndex == 2)
        {
            UIManager::GetInstance()->ChangeState("SettingUI");
        }
    }
    if (KeyManager::GetInstance()->IsOnceKeyDown(0x58))
    {
        UIManager::GetInstance()->ChangeState("IdleUI");
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
