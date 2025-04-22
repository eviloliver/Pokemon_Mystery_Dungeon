#pragma once
// clang-format off
#include "config.h"
// clang-format on

class GameObject
{
public:
    virtual HRESULT Init();        // ��� ������ �ʱ�ȭ, �޸� �Ҵ�
    virtual void Release();        // �޸� ����
    virtual void Update();         // ������ ������ ���� ���� ����(������ ���)
    virtual void Render(HDC hdc);  // ������ ������ ���(�̹���, �ؽ�Ʈ ��)

    GameObject();
    virtual ~GameObject();
};
