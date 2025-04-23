#pragma once
// clang-format off
#include "config.h"
// clang-format on

// UI ���� �������̽�
class UIState
{
public:
    virtual HRESULT Init() = 0;
    virtual void Release() = 0;
    virtual void Update() = 0;
    virtual void Update(float dt)
    {
        Update();
    };
    virtual void Render(HDC hdc)
    {
    }
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