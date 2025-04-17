#include "PPHeal.h"
#include "ISkill.h"

HRESULT PPHeal::Init()
{
	x = 0; y = 0;

	healPP = 10; // *�������� : pp���� �÷��̾ ����ϴ� ��ų�� ���� PP���� �����ͼ� ��ġ��ŭ ������
	name = "PPHeal";

	image = ImageManager::GetInstance()->AddImage(
		"PPHeal", TEXT("Image/ItemImage.bmp"), 1, 1, 1, 1,
		true, RGB(255, 0, 255));
}

void PPHeal::Update()
{
}

void PPHeal::Render(HDC hdc)
{
	image = ImageManager::GetInstance()->FindImage("PPHeal");
	if (image)
	{
		image->FrameRender(hdc, x, y, 1, 0, false, true);
	}
}

void PPHeal::Release()
{
}

void PPHeal::Use()
{
	//�÷��̾ ������ �ִ� ��ų�� PP���� �����ͼ� += healPP;
}

void PPHeal::SetPosition(int newX, int newY)
{
	x = newX;
	y = newY;
}
