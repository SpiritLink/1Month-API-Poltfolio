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
#define WINNAME (LPTSTR)(TEXT("SGA 1608 유지상"))
#define WINSTARTX 100
#define WINSTARTY 0
#define WINSIZEX 853
#define WINSIZEY 480
#define WINSTYLE WS_CAPTION | WS_SYSMENU | WS_CLIPCHILDREN

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