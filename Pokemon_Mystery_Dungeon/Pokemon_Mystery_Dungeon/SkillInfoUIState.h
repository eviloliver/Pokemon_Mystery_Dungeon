#pragma once
#include "UIState.h"

// ��ų ���� UI
class SkillInfoUIState : public UIState
{
public:
	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;
	~SkillInfoUIState() override;
};

