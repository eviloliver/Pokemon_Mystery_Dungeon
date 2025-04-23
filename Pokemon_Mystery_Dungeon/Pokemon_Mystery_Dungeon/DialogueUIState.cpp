#include "DialogueUIState.h"

#include "ImageGDIPlusManager.h"
#include "UIElementImage.h"
#include "UIElementText.h"
#include "UIManager.h"

DialogueUIState::~DialogueUIState()
{
    Release();
}

HRESULT DialogueUIState::Init()
{
    // ��ȭ ���� �̹��� ����
    dialogueBoxImage = new UIElementImage();
    dialogueBoxImage->SetImage(ImageGDIPlusManager::GetInstance()->AddImage(
        "dialogueBox", L"Image/UIImage/DialogueUIState/DialogueBoxImage.png", 1,
        1));

    dialogueBoxImage->SetLocalPos(dialogueBoxPosX, dialogueBoxPosY);
    dialogueBoxImage->setAlpha(0.7f);

    dialogueBoxImage->UpdateRealPos();

    mainText = new UIElementText();
    mainText->SetFont(20);
    mainText->SetTextLine(5.0f);
    mainText->SetTextColorRGB(28, 28, 132);
    mainText->SetLocalPos(20, 30);
    mainText->SetParent(dialogueBoxImage);

    return (dialogueBoxImage != nullptr) ? S_OK : E_FAIL;
}

void DialogueUIState::Release()
{
    delete dialogueBoxImage;  // �ڽ� �ڵ� ����
    dialogueBoxImage = nullptr;
}

void DialogueUIState::Update()
{
    if (dialogueBoxImage)
        dialogueBoxImage->Update();

    if (KeyManager::GetInstance()->IsOnceKeyDown(0x58))  // 'X' Ű
    {
        UIManager::GetInstance()->CloseUIStateBox("dialogueBox");
    }
}

void DialogueUIState::Update(float dt)
{
    if (dialogueBoxImage)
        dialogueBoxImage->Update(dt);



    if (KeyManager::GetInstance()->IsOnceKeyDown(0x58))  // 'X'
    {
        UIManager::GetInstance()->CloseUIStateBox("dialogueBox");
        UIManager::GetInstance()->ChangeState("IdleUI");
    }
}

void DialogueUIState::Render(HDC hdc)
{
    if (dialogueBoxImage)
        dialogueBoxImage->Render(hdc);
}

void DialogueUIState::PushDialogueLine(const wstring& text)
{
    auto* newText = new UIElementText();
    newText->SetText(text);
    newText->SetFont(18);
    newText->SetTextLine(5.0f);
    newText->SetLocalPos(10, 10);
    newText->SetParent(dialogueBoxImage);
}

void DialogueUIState::PushDialogueLine(const wstring& text,
                                       const map<wstring, wstring>& values)
{
    if (!mainText)
        return;

    const wstring& replaced = mainText->RenderDialogue(text, values);
    mainText->TypeEffect(replaced, 0.05f);
}