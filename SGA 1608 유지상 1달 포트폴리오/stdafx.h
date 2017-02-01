// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <stdio.h>		//���Ĵٵ� ����� ��� ��Ŭ��� (printf, scanf, puts, gets���)
#include <tchar.h>		//�����쿡�� ����� ���ڿ� ��� ��� ��Ŭ��� (TextOut, DrawText, wsprintf���)
//�⺻������ �����ڵ���
#include <vector>
#include <map>
#include <list>
#include <string>
#include <set>

using namespace std;

// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
#include "commonMacroFunction.h"
#include "randomFunction.h"
#include "keyManager.h"
#include "imageManager.h"
#include "utils.h"
#include "timeManager.h"
#include "txtDataManager.h"
#include "effectManager.h"
#include "sceneManager.h"
#include "database.h"
#include "frameAnimationManager.h"
#include "actionManager.h"
#include "keyAniManager.h"
#include "soundManager.h"

using namespace MY_UTIL;

//������ ũ�� �� ��Ÿ�� ����
#define WINNAME (LPTSTR)(TEXT("SGA 1608 ������ 1�� ��Ʈ������"))
#define WINSTARTX 100
#define WINSTARTY 0
#define WINSIZEX 800
#define WINSIZEY 600
#define WINSTYLE WS_CAPTION | WS_SYSMENU | WS_CLIPCHILDREN

//��� Ŭ�������� ������ ����
#define DEG_TO_RAD	0.017453f
#define PI			3.141592654f
#define PI2			6.283185308f

#define PI_8 float(PI/8.0f)
#define PI_16 float(PI/16.0f)
#define PI_32 float(PI/32.0f)
#define PI_64 float(PI/64.0f)
#define PI_128 float(PI/128.0f)

#define FLOAT_EPSILON	0.001f;
#define FLOAT_TO_INT(f1) static_cast<int>(f1+ FLOAT_EPSILON)
#define FLOAT_EQUAL(f1,f2) (fabs(f1-f2) <= FLOAT_EPSILON)

//�̱��� ����
#define RND randomFunction::getSingleton()
#define KEYMANAGER keyManager::getSingleton()
#define IMAGEMANAGER imageManager::getSingleton()
#define TIMEMANAGER timeManager::getSingleton()
#define TXTMANAGER txtDataManager::getSingleton()
#define EFFECTMANAGER effectManager::getSingleton()
#define SCENEMANAGER sceneManager::getSingleton()
#define DATABASE database::getSingleton()
#define FRAMEANIMANAGER frameAnimationManager::getSingleton()
#define ACTIONMANAGER actionManager::getSingleton()
#define KEYANIMANAGER keyAniManager::getSingleton()
#define SOUNDMANAGER soundManager::getSingleton()

//�����ϰ� �����Ѵ� ��ũ�� �Ծ�~~
#define SAFE_DELETE(p)		{if(p) {delete (p); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p){if(p) {delete[] (p); (p) = NULL;}}
#define SAFE_RELEASE(p)		{if(p) {(p)->release(); (p) = NULL;}}

//�������� ����
extern HINSTANCE	_hInstance; //���α׷� �ν��ͽ�
extern HWND			_hWnd;		//������ �ڵ�
extern POINT		_ptMouse;   //���콺 ����Ʈ
extern BOOL			_leftButtonDown;

//���� ENUM ����
enum KEYBOARD
{//����Ʈ ���� ���
	KEYBOARD_LEFT = 1,			
	KEYBOARD_RIGHT = 1 << 1,
	KEYBOARD_UP = 1 << 2,
	KEYBOARD_DOWN = 1 << 3,
	KEYBOARD_Z = 1 << 4,
	KEYBOARD_X = 1 << 5,
	KEYBOARD_C = 1 << 6
};

enum STATUS
{
	STATUS_STAND = 1,
	STATUS_RUN = 1 << 1,
	STATUS_JUMP = 1 << 2,
	STATUS_LAND = 1 << 3,
	STATUS_ATTACK = 1 << 4
};

enum ACTION
{
	ACTION_NONE = 1,
	ACTION_JUMP = 1 << 1,
	ACTION_ATTACK = 1 << 2
};

enum ATTACKTYPE
{
	ATTACK_PLAYER_SLASH_LEFT,
	ATTACK_PLAYER_SLASH_RIGHT
};

//������Ʈ���� ���� define
#define SAMPLETILEX 27
#define SAMPLETILEY 24
#define TILESIZE 50
#define SAMPLETILESIZE 20
#define TILEX 150
#define TILEY 150
#define TILESIZEX (TILESIZE * TILEX)
#define TILESIZEY (TILESIZE * TILEY)

#define GRAVITY 0.5

//�������� ���Ǵ� ���� ����ü�� enum
enum CTRL
{
	CTRL_TERRAINDRAW, CTRL_OBJDRAW, CTRL_OBJERASER, CTRL_TERRAINERASER, CTRL_END
};

enum OBJECT
{
	OBJ_GROUND, OBJ_BLOCK2, OBJ_NONE
};

enum TERRAIN
{
	TR_CEMENT, TR_EARTH, TR_GRASS, TR_WATER, TR_NONE
};

enum DIRECTION
{
	RIGHT, UP, LEFT, DOWN, NONE
};
struct tagTile
{
	TERRAIN terrain;
	OBJECT obj;
	RECT rc;
	int terrainFrameX;
	int terrainFrameY;
	int objFrameX;
	int objFrameY;
};

struct tagSampleTile
{
	RECT rc;
	int terrainFrameX;
	int terrainFrameY;
};

struct tagCurrentTile
{
	int x;
	int y;
};


