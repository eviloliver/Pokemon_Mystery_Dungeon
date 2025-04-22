#pragma once
#include <Windows.h>
#include <gdiplus.h>
#include <gdiplusimaging.h>

#include "config.h"
#pragma comment(lib, "gdiplus.lib")

// 5100�� GIF���� '������ ������ ����'�� �������� ���� ID�� - �� �������� ������
// �ð�(������)
#define PropertyTagFrameDelay 0x5100

class ImageGDIPlus
{
public:
    enum IMAGE_LOAD_TYPE
    {
        Resource,  // ������Ʈ ��ü�� ���� ��ų �̹���
        File,      // �ܺο��� �ε��� �̹���
        Empty,     // ��ü ������ �̹���
        End
    };

private:
    Gdiplus::Image* image = nullptr;

    int width = 0;
    int height = 0;
    int maxFrameX = 1;
    int maxFrameY = 1;
    int frameWidth = 0;
    int frameHeight = 0;
    int currFrameX = 0;
    int currFrameY = 0;

    bool isGif = false;
    GUID gifFrameDimension = {};
    UINT gifFrameCount = 1;
    UINT gifCurrentFrame = 0;

    vector<UINT> gifFrameDelay;
    float gifElapsedTime = 0.0f;
    float gifSpeedMultiplier = 3.0f;

public:
    HRESULT Init(const wchar_t* filePath, int maxFrameX, int maxFrameY,
                 bool ifGif = false);

    void Release();

    // x��ǥ, y��ǥ, ȸ������, x�� ���� ����, y�� ���� ����, ����
    void Render(HDC hdc, float x, float y, float angle = 0.0f,
                bool flipX = false, bool flipY = false, float alpha = 1.0f);

    // �ڵ� ũ�� ����? - ����
    // void RenderScale(HDC hdc, float x, float y, float alpha = 1.0f);

    void RenderScale(HDC hdc, float x, float y, float scaleX, float scaleY,
                     float angle = 0.0f, bool flipX = false, bool flipY = false,
                     float alpha = 1.0f);
    // x��ǥ, y��ǥ, ���ι���, ���� ����, ȸ������, x�� ���� ����, y�� ����
    // ����, ����

    // x��ǥ, y��ǥ, ������ �ε���, ȸ������, x�� ���� ����, y�� ���� ����,
    // ����
    void RenderFrame(HDC hdc, float x, float y, int frameIndex,
                     float angle = 0.0f, bool flipX = false, bool flipY = false,
                     float alpha = 1.0f);

    // x��ǥ, y��ǥ, ���ι���, ���� ����, ������ �ε���, ȸ������, x�� ����
    // ����, y�� ���� ����, ����
    void RenderFrameScale(HDC hdc, float x, float y, float scaleX, float scaleY,
                          int frameIndex, float angle = 0.0f,
                          bool flipX = false, bool flipY = false,
                          float alpha = 1.0f);

    // x��ǥ, y��ǥ, ��� �������� �׸��� ����(0.0 ~ 1.0), ����
    void RenderLeftToRight(HDC hdc, float x, float y, float percent,
                           float alpha = 1.0f);

    void Update(float deltaTime);

    void SetGifFrame(UINT frameIndex);
    UINT GetGifFrameCount() const;

    inline int GetWidth() const
    {
        return width;
    }
    inline int GetHeight() const
    {
        return height;
    }
    inline int GetFrameWidth() const
    {
        return frameWidth;
    }
    inline int GetFrameHeight() const
    {
        return frameHeight;
    }
    inline int GetMaxFrameX() const
    {
        return maxFrameX;
    }
    inline int GetMaxFrameY() const
    {
        return maxFrameY;
    }
    inline int GetCurrFrameX() const
    {
        return currFrameX;
    }
    inline int GetCurrFrameY() const
    {
        return currFrameY;
    }
    void SetGifSpeed(float multiplier)
    {
        gifSpeedMultiplier = multiplier;
    }
};
