#pragma once
#include "UIState.h"

// ��ų ���� UI
class SkillSelectUIState : public UIState
{
public:
	void Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;
	~SkillSelectUIState() override;
};

