#pragma once
#include "UIState.h"

// Intro Animation(����)
// �ٸ� UI ��� ���� �� �� �� ��.
class TitleUIState : public UIState
{
public:
	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;
	~TitleUIState() override;
};

