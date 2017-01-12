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
#define WINNAME (LPTSTR)(TEXT("SGA 1608 ������"))
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