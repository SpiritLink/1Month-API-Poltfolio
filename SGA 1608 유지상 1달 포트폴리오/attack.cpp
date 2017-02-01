#include "stdafx.h"
#include "attack.h"


HRESULT attack::init(float inputX, float inputY)
{
	inputTime = TIMEMANAGER->getWorldTime();
	checkCollision = false;
	x = inputX;
	y = inputY;
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
	checkCollision = false;
	x = inputX;
	y = inputY;
	return S_OK;
}

void playerSlash::release()
{
}

void playerSlash::update()
{
	switch (_attackType)
	{
	case ATTACK_PLAYER_SLASH_LEFT: 	_RECT = RectMakeCenter(DATABASE->getPlayerX() - 30, DATABASE->getPlayerY() - 15, 50, 50);
		break;
	case ATTACK_PLAYER_SLASH_RIGHT:	_RECT = RectMakeCenter(DATABASE->getPlayerX() + 30, DATABASE->getPlayerY() - 15, 50, 50);
		break;
	}
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
