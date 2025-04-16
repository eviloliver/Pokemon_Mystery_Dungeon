#pragma once
#include <Windows.h>
#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")

class ImageGDIPlus
{
public:
	enum IMAGE_LOAD_TYPE
	{
		Resource,	// ������Ʈ ��ü�� ���� ��ų �̹���
		File,		// �ܺο��� �ε��� �̹���
		Empty,		// ��ü ������ �̹���
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

public:
	HRESULT Init(const wchar_t* filePath, int maxFrameX, int maxFrameY);
	
	void Release();

	// x��ǥ, y��ǥ, ȸ������, x�� ���� ����, y�� ���� ����, ����
	void Render(HDC hdc, float x, float y, float angle = 0.0f, bool flipX = false, bool flipY = false, float alpha = 1.0f);

	// x��ǥ, y��ǥ, ���ι���, ���� ����, ȸ������, x�� ���� ����, y�� ���� ����, ����
	void RenderScale(HDC hdc, float x, float y, float scaleX, float scaleY, float angle = 0.0f, bool flipX = false, bool flipY = false, float alpha = 1.0f);

	// x��ǥ, y��ǥ, ������ �ε���, ȸ������, x�� ���� ����, y�� ���� ����, ����
	void RenderFrame(HDC hdc, float x, float y, int frameIndex, float angle = 0.0f, bool flipX = false, bool flipY = false, float alpha = 1.0f);

	// x��ǥ, y��ǥ, ���ι���, ���� ����, ������ �ε���, ȸ������, x�� ���� ����, y�� ���� ����, ����
	void RenderFrameScale(HDC hdc, float x, float y, float scaleX, float scaleY, int frameIndex, float angle = 0.0f, bool flipX = false, bool flipY = false, float alpha = 1.0f);

	// x��ǥ, y��ǥ, ��� �������� �׸��� ����(0.0 ~ 1.0), ����
	void RenderLeftToRight(HDC hdc, float x, float y, float percent, float alpha = 1.0f);


	inline int GetWidth() const { return width; }
	inline int GetHeight() const { return height; }
	inline int GetFrameWidth() const { return frameWidth; }
	inline int GetFrameHeight() const { return frameHeight; }
	inline int GetMaxFrameX() const { return maxFrameX; }
	inline int GetMaxFrameY() const { return maxFrameY; }
	inline int GetCurrFrameX() const { return currFrameX; }
	inline int GetCurrFrameY() const { return currFrameY; }
};

