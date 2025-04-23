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
    newText->SetFont(L"Arial", 18);
    newText->SetTextLine(5.0f);
    newText->SetLocalPos(10, 10);
    newText->SetParent(dialogueBoxImage);
}

void DialogueUIState::PushDialogueLine(const wstring& text,
                                       const map<wstring, wstring>& values)
{
    auto* newText = new UIElementText();
    newText->RenderDialogue(text, values);  // ���ø� ġȯ ����
    newText->TypeEffect(text, 0.05f);

    newText->SetFont(L"Arial", 20);
    newText->SetTextLine(5.0f);
    newText->SetTextColor(28, 28, 132, 255);  // #1C1C84
    newText->SetLocalPos(20, 30);
    newText->SetParent(dialogueBoxImage);
}