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

HRESULT playerThrow::init(float inputX, float inputY)
{
	inputTime = TIMEMANAGER->getWorldTime();
	checkCollision = false;
	x = inputX;
	y = inputY;
	return S_OK;
}

void playerThrow::release()
{
}

void playerThrow::update()
{
	_RECT = RectMakeCenter(x, y, 50, 50);
	switch (_attackType)
	{
	case ATTACK_PLAYER_THROW_LEFT:
		x -= 10;
		break;
	case ATTACK_PLAYER_THROW_RIGHT:
		x += 10;
		break;
	}
}

void playerThrow::render()
{
	Rectangle(getMemDC(), _RECT.left, _RECT.top, _RECT.right, _RECT.bottom);
}

playerThrow::playerThrow()
{
}

playerThrow::~playerThrow()
{
}

HRESULT eriWave::init(float inputX, float inputY)
{
	inputTime = TIMEMANAGER->getWorldTime();
	checkCollision = false;
	x = inputX;
	y = inputY;
	return S_OK;
}

void eriWave::release()
{
}

void eriWave::update()
{
	_RECT = RectMakeCenter(x, y, 50, 100);
	switch (_attackType)
	{
	case ATTACK_ERI_WAVE_LEFT:
		x -= 10;
		break;
	case ATTACK_ERI_WAVE_RIGHT:
		x += 10;
		break;
	}
}

void eriWave::render()
{
	Rectangle(getMemDC(), _RECT.left, _RECT.top, _RECT.right, _RECT.bottom);
}

eriWave::eriWave()
{
}

eriWave::~eriWave()
{
}
