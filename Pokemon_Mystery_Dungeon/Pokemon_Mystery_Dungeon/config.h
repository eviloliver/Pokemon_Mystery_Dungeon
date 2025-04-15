// config.h

#pragma once
#pragma comment(lib, "Winmm.lib")

#include <Windows.h>
#include <string>
#include <iostream>
#include <bitset>
#include <map>
#include <unordered_map>
#include <vector>

using namespace std;

#include "KeyManager.h"
#include "ImageManager.h"
#include "TimerManager.h"
#include "SceneManager.h"

/*
	�����Ϸ����� �ش� �ڵ带 �ڿ� ���ǵ� �ڵ�� �����Ѵ�. 
*/
#define WINSIZE_X	1080
#define WINSIZE_Y	500
#define TILEMAPTOOL_X	1420
#define TILEMAPTOOL_Y	700
#define SAMPLE_TILE_X	21
#define SAMPLE_TILE_Y	24
#define TILE_SIZE	24
#define TILE_SELECT_SIZE 25

#define DEG_TO_RAD(degree) ((3.14 / 180.0) * degree)
#define RAD_TO_DEG(radian) ((180.0 / 3.14) * radian)

// IV => ��ü��, EV = ���ġ
#define IV 30
#define EV 20

typedef struct tagFPOINT
{
	float x;
	float y;
} FPOINT;

// ���ϸ� �⺻ ������
struct PokemonData {
	int idNumber;
	string name;
	int hp, atk, def, spAtk, spDef, speed, sum, average;
	vector<string> types;
};
/*
	extern Ű���� : ������ �Լ��� �ٸ� ���Ͽ� ���ǵǾ� �ִ� ���
	����� �˸��� Ű����.
*/
extern HWND g_hWnd;
extern HINSTANCE g_hInstance;
extern POINT g_ptMouse;
