#pragma once
#include "UIState.h"

class UIElementImage;
class UIElementText;
class DialogueUIState : public UIState
{
private:
    UIElementImage* dialogueBoxImage = nullptr;
    UIElementText* mainText = nullptr;

    const int dialogueBoxPosX = 25;
    const int dialogueBoxPosY = 220;

public:
    HRESULT Init() override;
    void Release() override;
    void Update() override;
    void Update(float dt) override;
    void Render(HDC hdc) override;
    ~DialogueUIState() override;

    // �ܺο��� �ؽ�Ʈ 1�� �߰�
    void PushDialogueLine(const wstring& text);

    void PushDialogueLine(const wstring& text,
                          const map<wstring, wstring>& values);
};
