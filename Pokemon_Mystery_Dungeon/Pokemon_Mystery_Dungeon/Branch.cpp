#include "Branch.h"

HRESULT Branch::Init()
{
	x = 0; y = 0;
	branchDamage = rand() % 4; // *�������� �������������� �÷��̾ ����ϴ°�ü�� ���ݷ¸�ŭ�� ���������

	name = "Branch";

	image = ImageManager::GetInstance()->AddImage(
		"Branch", TEXT("Image/ItemImage.bmp"), 1, 1, 1, 1,
		true, RGB(255, 0, 255));
}

void Branch::Update()
{
}

void Branch::Render(HDC hdc)
{
	image = ImageManager::GetInstance()->FindImage("Branch");
	if (image)
	{
		image->FrameRender(hdc, x, y, 1, 0, false, true);
	}
}

void Branch::Release()
{
}

void Branch::Use()
{
}

void Branch::SetPosition(int newX, int newY)
{
	x = newX;
	y = newY;
}
