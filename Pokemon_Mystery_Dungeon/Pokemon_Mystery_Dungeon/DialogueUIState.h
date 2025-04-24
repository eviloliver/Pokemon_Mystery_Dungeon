#pragma once
#include "UIState.h"
#include <queue>

class UIElementImage;
class UIElementText;
class DialogueUIState : public UIState
{
private:
    UIElementImage* dialogueBoxImage = nullptr;
    UIElementText* mainText = nullptr;


    const int dialogueBoxPosX = 25;
    const int dialogueBoxPosY = 220;

    float closeTimer = 0.0f;
    bool dialogueFullyShown = false;

    queue<pair<wstring, map<wstring, wstring>>> dialogueQueue;

    bool isActive = false;
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

    void QueueDialogueLine(const wstring& text,
                           const map<wstring, wstring>& values);

    void PopNextDialogueLine();
};
