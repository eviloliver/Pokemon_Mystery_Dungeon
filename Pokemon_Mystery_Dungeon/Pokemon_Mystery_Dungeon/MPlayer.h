#pragma once
#include <Windows.h>

class MPlayer
{
private:
    POINT pos;
    SIZE size;
    RECT rect;
    float speed;
    POINT prevPos;  // ���� ������ ��ġ

public:
    MPlayer();
    ~MPlayer();

    HRESULT Init();
    void Release();
    void Update();
    void Render(HDC hdc);

    void Move();        // ����Ű �Է� ó��
    void UpdateRect();  // RECT ����
    void SavePrevPos()
    {
        prevPos = pos;
    }
    void UndoMove()
    {
        pos = prevPos;
        UpdateRect();
    }

    RECT GetRect() const
    {
        return rect;
    }
    POINT GetPos() const
    {
        return pos;
    }
};
