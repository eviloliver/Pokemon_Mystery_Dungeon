#pragma once
#include "ImageGDIPlus.h"
#include "UIElementImage.h"
#include "UIState.h"

// ��ų ���� UI
class SkillInfoUIState : public UIState, public UIElement
{
private:
    UIElementImage* SkillInfoBox = nullptr;

public:
    HRESULT Init() override;
    void Release() override;
    void Update() override;
    void Render(HDC hdc) override;
    ~SkillInfoUIState() override;
};
