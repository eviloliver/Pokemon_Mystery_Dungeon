#pragma once
#include <Windows.h>

#include "Singleton.h"

class Camera : public Singleton<Camera>
{
private:
    POINT cameraPos;   // ���� ī�޶� ��ġ
    POINT mapSize;     // ��ü �� ũ��
    POINT screenSize;  // ���� ȭ�� ũ�� (������ ũ��)

public:
    void SetCameraPos(POINT focus);
    POINT GetCameraPos() const;

    void SetMapSize(POINT size)
    {
        mapSize = size;
    }
    void SetScreenSize(POINT size)
    {
        screenSize = size;
    }
};
