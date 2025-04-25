#include "YesOrNoUIState.h"

#include "ImageGDIPlusManager.h"
#include "UIElementImage.h"
#include "UIElementText.h"
#include "UIManager.h"

HRESULT YesOrNoUIState::Init()
{
    auto& manager = *ImageGDIPlusManager::GetInstance();
    auto YesOrNoBoxImage = manager.AddImage(
        "YesOrNoBox", L"Image/UIImage/YesOrNoUIState/YesOrNoBox.png");
    auto CursorImage =
        manager.AddImage("Cursor", L"Image/UIImage/YesOrNoUIState/Cursor.png");
    // UI ������Ʈ ����
    YesOrNoBox = new UIElementImage();
    YesText = new UIElementText();
    NoText = new UIElementText();
    Cursor = new UIElementImage();

    // UI ������Ʈ ����
    YesOrNoBox->SetImage(YesOrNoBoxImage);
    Cursor->SetImage(CursorImage);

    YesText->SetText(L"Yes");
    NoText->SetText(L"No");

    // UI ������Ʈ ��ġ ����
    YesOrNoBox->SetLocalPos(InfoBoxPosX, 200);
    YesText->SetLocalPos(50, InfoBoxPosYOffset[0]);
    NoText->SetLocalPos(50, InfoBoxPosYOffset[1]);

    Cursor->SetLocalPos(20, InfoBoxPosYOffset[0] + 5);

    // ����
    YesOrNoBox->setAlpha(0.7f);

    // �θ� ����
    YesOrNoBox->SetParent(this);

    // �ڽ�
    YesText->SetParent(YesOrNoBox);
    NoText->SetParent(YesOrNoBox);
    Cursor->SetParent(YesOrNoBox);

    UpdateRealPos();
    return S_OK;
}

void YesOrNoUIState::Release()
{
}

void YesOrNoUIState::Update()
{
    fadeOutTime += TimerManager::GetInstance()->GetDeltaTime();
    fadeInTime = (sinf(fadeOutTime * 6.0f) * 0.5f) + 0.5f;

    if (KeyManager::GetInstance()->IsOnceKeyDown(VK_DOWN))
    {
        SoundManager::GetInstance()->PlaySFX("button");
        YIndex = (YIndex + 1) % 2;
        Cursor->SetLocalPos(CursorPosX, InfoBoxPosYOffset[YIndex]);
        Cursor->UpdateRealPos();
    }
    else if (KeyManager::GetInstance()->IsOnceKeyDown(VK_UP))
    {
        SoundManager::GetInstance()->PlaySFX("button");
        YIndex = (YIndex - 1 + 2) % 2;
        Cursor->SetLocalPos(CursorPosX, InfoBoxPosYOffset[YIndex]);
        Cursor->UpdateRealPos();
    }

    if (KeyManager::GetInstance()->IsOnceKeyDown(0x58))  // 'X' Ű
    {
        UIManager::GetInstance()->ChangeState("defaultUI");
    }

    Cursor->setAlpha(fadeInTime);
}

void YesOrNoUIState::Render(HDC hdc)
{
    YesOrNoBox->Render(hdc);
}

YesOrNoUIState::~YesOrNoUIState()
{
}
