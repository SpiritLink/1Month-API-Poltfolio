#include "stdafx.h"
#include "gameNode.h"


gameNode::gameNode()
{
}


gameNode::~gameNode()
{
}

HRESULT gameNode::init()
{
	//타이머 생성
	SetTimer(_hWnd, 0, 10, NULL);

	//키 매니져 초기화
	KEYMANAGER->init();

	//이미지 매니져 초기화
	IMAGEMANAGER->init();

	//타임 매니져 초기화
	TIMEMANAGER->init();

	//텍스트 매니져 초기화
	TXTMANAGER->init();

	EFFECTMANAGER->init();

	SCENEMANAGER->init();

	DATABASE->init();

	FRAMEANIMANAGER->init();

	ACTIONMANAGER->init();

	KEYANIMANAGER->init();

	SOUNDMANAGER->init();

	//DC생성
	_hdc = GetDC(_hWnd);



	return S_OK;
}

void gameNode::release()
{
	_backBuffer->release();
	SAFE_DELETE(_backBuffer);

	//타이머 해제
	KillTimer(_hWnd, 0);

	//키 매니져 해제
	KEYMANAGER->release();
	KEYMANAGER->releaseSingleton();

	//이미지 매니져 해제
	IMAGEMANAGER->release();
	IMAGEMANAGER->releaseSingleton();

	//타임 매니져 해제
	TIMEMANAGER->release();
	TIMEMANAGER->releaseSingleton();

	//텍스트 매니져 해제
	TXTMANAGER->release();
	TXTMANAGER->releaseSingleton();


	EFFECTMANAGER->release();
	EFFECTMANAGER->releaseSingleton();

	SCENEMANAGER->release();
	SCENEMANAGER->releaseSingleton();

	DATABASE->release();
	DATABASE->releaseSingleton();

	FRAMEANIMANAGER->release();
	FRAMEANIMANAGER->releaseSingleton();

	ACTIONMANAGER->release();
	ACTIONMANAGER->releaseSingleton();

	KEYANIMANAGER->release();
	KEYANIMANAGER->releaseSingleton();

	SOUNDMANAGER->release();
	SOUNDMANAGER->releaseSingleton();

	//DC릴리즈
	ReleaseDC(_hWnd, _hdc);
}

void gameNode::update()
{

}

void gameNode::render()
{

}

LRESULT gameNode::MainProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_LBUTTONDOWN:
		_leftButtonDown = true;
		break;
	case WM_LBUTTONUP:
		_leftButtonDown = false;
		break;
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_ESCAPE:
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		}
	}

	break;
	case WM_MOUSEMOVE:

		_ptMouse.x = static_cast<float>LOWORD(lParam);
		_ptMouse.y = static_cast<float>HIWORD(lParam);

		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}
