#pragma once
#include "UIState.h"
#include "UIElement.h"

class UIElementImage;
class UIElementText;
class YesOrNoUIState : public UIState, public UIElement
{
private:
	UIElementImage* YesOrNoBox = nullptr;
	UIElementText* YesText = nullptr;
	UIElementText* NoText = nullptr;
	UIElementImage* Cursor = nullptr;
	const int InfoBoxPosX = 40; // ���߿� �÷��̾� ��ġ�� ���缭 �ٲ����
	const int InfoBoxPosYOffset[2] = { 30,60 };

public:
	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;
	~YesOrNoUIState() override;
};

