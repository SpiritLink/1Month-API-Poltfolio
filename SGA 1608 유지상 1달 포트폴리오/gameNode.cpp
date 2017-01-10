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
	//Ÿ�̸� ����
	SetTimer(_hWnd, 0, 10, NULL);

	//Ű �Ŵ��� �ʱ�ȭ
	KEYMANAGER->init();

	//�̹��� �Ŵ��� �ʱ�ȭ
	IMAGEMANAGER->init();

	//Ÿ�� �Ŵ��� �ʱ�ȭ
	TIMEMANAGER->init();

	//�ؽ�Ʈ �Ŵ��� �ʱ�ȭ
	TXTMANAGER->init();

	EFFECTMANAGER->init();

	SCENEMANAGER->init();

	DATABASE->init();

	FRAMEANIMANAGER->init();

	ACTIONMANAGER->init();

	KEYANIMANAGER->init();

	SOUNDMANAGER->init();

	//DC����
	_hdc = GetDC(_hWnd);



	return S_OK;
}

void gameNode::release()
{
	_backBuffer->release();
	SAFE_DELETE(_backBuffer);

	//Ÿ�̸� ����
	KillTimer(_hWnd, 0);

	//Ű �Ŵ��� ����
	KEYMANAGER->release();
	KEYMANAGER->releaseSingleton();

	//�̹��� �Ŵ��� ����
	IMAGEMANAGER->release();
	IMAGEMANAGER->releaseSingleton();

	//Ÿ�� �Ŵ��� ����
	TIMEMANAGER->release();
	TIMEMANAGER->releaseSingleton();

	//�ؽ�Ʈ �Ŵ��� ����
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

	//DC������
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
