#include "DungeonUIState.h"

#include "ImageGDIPlusManager.h"
#include "UIManager.h"

HRESULT DungeonUIState::Init()
{
    // �̹���
    auto& manager = *ImageGDIPlusManager::GetInstance();
    auto DungeonInfoBoxImage = manager.AddImage(
        "DungeonInfoBox", L"Image/UIImage/DungeonUIState/DungeonInfoBox.png");
    //auto WaterTypeGifImage = manager.AddImage(
    //    "WaterType", L"Image/UIImage/DungeonUIState/waterType.gif", 1, 1, true);
    //auto FireTypeGifImage = manager.AddImage(
    //    "FireType", L"Image/UIImage/DungeonUIState/fireType.gif", 1, 1, true);

    // UI ������Ʈ ����
    DungeonInfoBox = new UIElementImage();
    DungeonInfoBox->SetImage(DungeonInfoBoxImage);
    DungeonInfoBox->SetLocalPos(25, 100);
    DungeonInfoBox->setAlpha(0.7f);
    DungeonInfoBox->SetParent(this);

    int parentWidth = DungeonInfoBox->GetImageWidth();

    // �ڽ� ��ü ���� waterType
    //WaterType = new UIElementImage();
    //WaterType->SetImage(WaterTypeGifImage);
    //WaterType->SetLocalPos(parentWidth - 120, OffsetY[0]);
    //WaterType->setAlpha(0.5f);
    //WaterType->SetSpeed(0.5f);
    //WaterType->setScale(0.17f, 0.17f);
    //WaterType->SetParent(DungeonInfoBox);

    // �ڽ� ��ü ���� waterTypeText
    IceTypeText = new UIElementText();
    IceTypeText->SetText(L"Water Dungeon");
    IceTypeText->SetLocalPos(50, OffsetY[0]);
    IceTypeText->SetParent(DungeonInfoBox);

    // �ڽ� ��ü ���� fireType
    //FireType = new UIElementImage();
    //FireType->SetImage(FireTypeGifImage);
    //FireType->SetLocalPos(parentWidth - 120, OffsetY[1]);
    //FireType->setAlpha(0.5f);
    //FireType->SetSpeed(0.5f);
    //FireType->setScale(0.17f, 0.17f);
    //FireType->SetParent(DungeonInfoBox);

    // �ڽ� ��ü ���� fireTypeText
    MagmaTypeText = new UIElementText();
    MagmaTypeText->SetText(L"Fire Dungeon");
    MagmaTypeText->SetLocalPos(50, OffsetY[1]);
    MagmaTypeText->SetParent(DungeonInfoBox);

    // �ڽ� ��ü ���� forestTypeText
    ForestTypeText = new UIElementText();
    ForestTypeText->SetText(L"Forest Dungeon");
    ForestTypeText->SetLocalPos(50, OffsetY[2]);
    ForestTypeText->SetParent(DungeonInfoBox);


    UpdateRealPos();
    return S_OK;
}

void DungeonUIState::Release()
{
}

void DungeonUIState::Update()
{
    if (WaterType)
    {
        WaterType->Update();
    }
    if (FireType)
    {
        FireType->Update();
    }
}

void DungeonUIState::Render(HDC hdc)
{
    if (DungeonInfoBox)
    {
        DungeonInfoBox->Render(hdc);
    }

    if (WaterType)
    {
        WaterType->Render(hdc);
    }
    if (FireType)
    {
        FireType->Render(hdc);
    }
}

DungeonUIState::~DungeonUIState()
{
}
