#pragma once
#include "UIState.h"

// �κ��丮 â
class InventoryUIState : public UIState
{
public:
	void Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;
	~InventoryUIState() override;
};

