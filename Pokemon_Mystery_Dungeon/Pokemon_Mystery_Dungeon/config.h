// config.h

#pragma once
#define _HAS_STD_BYTE 0
#pragma comment(lib, "Winmm.lib")

#include <Windows.h>
#include <string>
#include <iostream>
#include <bitset>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <vector>

using namespace std;

#include "KeyManager.h"
#include "ImageManager.h"
#include "TimerManager.h"
#include "SceneManager.h"
#include "CollisionManager.h"

/*
	�����Ϸ����� �ش� �ڵ带 �ڿ� ���ǵ� �ڵ�� �����Ѵ�.
*/
#define WINSIZE_X	800
#define WINSIZE_Y	400

#define GameViewSize_X	500
#define GameViewSize_Y	400

#define TILEMAPTOOL_X	1420
#define TILEMAPTOOL_Y	700
#define SAMPLE_TILE_X	21
#define SAMPLE_TILE_Y	24
#define TILE_SIZE	24
#define TILE_SELECT_SIZE 25

//���� �� Ÿ�� ũ�� 25Ÿ�� * 25Ÿ��  
#define TILE_X	25
#define TILE_Y	25

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

enum class Direction
{
    SOUTH,      // ��
    SOUTHEAST,  // ����
    EAST,       // ��
    NORTHEAST,  // �ϵ�
    NORTH,      // ��
    NORTHWEST,  // �ϼ�
    WEST,       // ��
    SOUTHWEST,  // ����
    LENGTH,
};

// ���ϸ� �ִϸ��̼� ������
const vector<string> animTypes = { "Attack", "Hurt", "Idle", "Rotate", "Swing", "Walk" };

/*
    extern Ű���� : ������ �Լ��� �ٸ� ���Ͽ� ���ǵǾ� �ִ� ���
    ����� �˸��� Ű����.
*/
extern HWND g_hWnd;
extern HINSTANCE g_hInstance;
extern POINT g_ptMouse;
