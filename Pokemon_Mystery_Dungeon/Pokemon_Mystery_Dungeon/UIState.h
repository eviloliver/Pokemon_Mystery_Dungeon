#pragma once
#include "Config.h"

// UI ���� �������̽�
class UIState
{
public:
	virtual void Init() = 0;
	virtual void Release() = 0;
	virtual void Update() = 0;
	virtual void Render(HDC hdc) {}
	virtual ~UIState() {};
};

/*
* 
  UIManager�� ���� ��ȯ�� �����ϴ� Ŭ����

* UIState ��� Ŭ����
    [�����]
	Ÿ��Ʋ ȭ�� ��ü		TitleUIState
	�κ��丮 â				InventoryUIState
	��ų ���� â			SkillInfoUIState
	��ų ���� â			SkillSelectUIState


	[���� �ȸ���]
	���� â 				StatusUIState
	�����̻� �� ���� â	StatusEffectInfoUIState
	��ȭâ 					DialogueUIState
*/