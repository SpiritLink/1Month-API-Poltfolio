#pragma once

#include "image.h"

static image* _backBuffer = IMAGEMANAGER->addImage("backBuffer",
	WINSIZEX, WINSIZEY);

class gameNode
{
private:

	HDC _hdc;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setBackBuffer();
	image* getBackBuffer() { return _backBuffer; }
	HDC getMemDC() { return _backBuffer->getMemDC(); }
	HDC getHDC() { return _hdc; }

	//메시지 프로시져
	LRESULT MainProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	gameNode();
	virtual ~gameNode();
};

