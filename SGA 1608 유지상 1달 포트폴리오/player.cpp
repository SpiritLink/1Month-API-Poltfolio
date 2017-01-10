#include "stdafx.h"
#include "player.h"


HRESULT player::init()
{
	x = WINSIZEX / 2;
	y = WINSIZEY / 2;
	PlayerRect = RectMakeCenter(x, y, 50, 50);
	STR = DEFAULT_STR;
	DEF = DEFAULT_DEF;
	ATK = STR * 3;

	return E_NOTIMPL;
}

void player::release()
{
}

void player::update()
{
	keyboardInput();
	PlayerRect = RectMakeCenter(x, y, 50, 50);
}

void player::render()
{
	Rectangle(getMemDC(), PlayerRect.left, PlayerRect.top, PlayerRect.right, PlayerRect.bottom);
}

void player::keyboardInput()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		x -= 3;
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		x += 3;
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		y -= 3;
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		y += 3;
	}

}

player::player()
{
}


player::~player()
{
}
