#include "CameraManager.h"

void CameraManager::Init(int width, int height)
{
	screenHeight = height;
	screenWidth = width;
	SetCameraPos(0, 0);
}

void CameraManager::SetCameraPos(int x, int y)
{
	cameraPos.x = x;
	cameraPos.y = y;

	int halfWidth = screenWidth / 2;
	int halfHeight = screenHeight / 2;

	// ī�޶��� ��ġ�� ����
	viewPos.left = x - halfWidth;
	viewPos.top = y - halfHeight;
	viewPos.right = viewPos.left + screenWidth;
	viewPos.bottom = viewPos.top + screenHeight;

	// ī�޶��� ��ġ�� ȭ���� ����� �ʵ��� ����
	if (viewPos.left < 0) {
		viewPos.left = 0;
		viewPos.right = screenWidth;
		cameraPos.x = screenWidth / 2;
	}
	if (viewPos.top < 0) {
		viewPos.top = 0;
		viewPos.bottom = screenHeight;
		cameraPos.y = screenHeight / 2;
	}

	if (viewPos.right > TILEMAPTOOL_X) {
		viewPos.right = TILEMAPTOOL_X;
		viewPos.left = TILEMAPTOOL_X - screenWidth;
		cameraPos.x = TILEMAPTOOL_X - screenWidth / 2;
	}
	if (viewPos.bottom > TILEMAPTOOL_Y) {
		viewPos.bottom = TILEMAPTOOL_Y;
		viewPos.top = TILEMAPTOOL_Y - screenHeight;
		cameraPos.y = TILEMAPTOOL_Y - screenHeight / 2;
	}
}
