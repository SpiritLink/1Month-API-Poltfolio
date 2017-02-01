#include "stdafx.h"
#include "attack.h"


HRESULT attack::init(float inputX, float inputY)
{
	return S_OK;
}

void attack::release()
{
}

void attack::update()
{
}

void attack::render()
{
}

attack::attack()
{
}


attack::~attack()
{
}

HRESULT playerSlash::init(float inputX, float inputY)
{
	inputTime = TIMEMANAGER->getWorldTime();
	x = inputX;
	y = inputY;
	return S_OK;
}

void playerSlash::release()
{
}

void playerSlash::update()
{
	_RECT = RectMakeCenter(x, y, 50, 50);
}

void playerSlash::render()
{
	Rectangle(getMemDC(), _RECT.left, _RECT.top, _RECT.right, _RECT.bottom);
}

playerSlash::playerSlash()
{
}

playerSlash::~playerSlash()
{
}
