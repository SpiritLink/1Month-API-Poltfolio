// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <stdio.h>		//스탠다드 입출력 헤더 인클루드 (printf, scanf, puts, gets등등)
#include <tchar.h>		//윈도우에서 사용할 문자열 출력 헤더 인클루드 (TextOut, DrawText, wsprintf등등)
//기본적으로 유니코드임
#include <vector>
#include <map>
#include <list>
#include <string>
#include <set>

using namespace std;

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
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

//윈도우 크기 및 스타일 설정
#define WINNAME (LPTSTR)(TEXT("SGA 1608 유지상 1달 포트폴리오"))
#define WINSTARTX 100
#define WINSTARTY 0
#define WINSIZEX 800
#define WINSIZEY 600
#define WINSTYLE WS_CAPTION | WS_SYSMENU | WS_CLIPCHILDREN

//모든 클래스에서 참조할 변수
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

//싱글톤 선언
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

//안전하게 삭제한다 메크로 함쑤~~
#define SAFE_DELETE(p)		{if(p) {delete (p); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p){if(p) {delete[] (p); (p) = NULL;}}
#define SAFE_RELEASE(p)		{if(p) {(p)->release(); (p) = NULL;}}

//전역변수 선언
extern HINSTANCE	_hInstance; //프로그램 인스터스
extern HWND			_hWnd;		//원도우 핸들
extern POINT		_ptMouse;   //마우스 포인트
extern BOOL			_leftButtonDown;

//공용 ENUM 선언
enum KEYBOARD
{//시프트 연산 사용
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

//프로젝트에서 사용될 define
#define SAMPLETILEX 27
#define SAMPLETILEY 24
#define TILESIZE 50
#define SAMPLETILESIZE 20
#define TILEX 150
#define TILEY 150
#define TILESIZEX (TILESIZE * TILEX)
#define TILESIZEY (TILESIZE * TILEY)

#define GRAVITY 0.5

//맵툴에서 사용되는 공용 구조체와 enum
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


