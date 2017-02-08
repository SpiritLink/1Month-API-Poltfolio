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

	if (inputTime + 0.1f < TIMEMANAGER->getWorldTime()) collisionTrue();
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
	currentTime = TIMEMANAGER->getWorldTime();
	_image = IMAGEMANAGER->addFrameImage("shuriken", "IMAGE/attack/shuriken.bmp", 208, 52, 4, 1, true, RGB(255, 255, 255));
	frameCount = 0;
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
	if (currentTime + 0.25f < TIMEMANAGER->getWorldTime())
	{

	}
	switch (_attackType)
	{
	case ATTACK_PLAYER_THROW_LEFT:
		x -= 20;
		break;
	case ATTACK_PLAYER_THROW_RIGHT:
		x += 20;
		break;
	}

	if (inputTime + 2.0f < TIMEMANAGER->getWorldTime()) collisionTrue();
}

void playerThrow::render()
{
	Rectangle(getMemDC(), _RECT.left, _RECT.top, _RECT.right, _RECT.bottom);
	_image->frameRender(getMemDC(), x - _image->getFrameWidth() / 2, y - _image->getFrameHeight() / 2,frameCount,0);
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
	if (inputTime + 2.5f < TIMEMANAGER->getWorldTime()) collisionTrue();
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

HRESULT eriKnives::init(float inputX, float inputY)
{
	inputTime = TIMEMANAGER->getWorldTime();
	checkCollision = false;
	x = inputX;
	y = inputY;
	_image = IMAGEMANAGER->addFrameImage("knives", "IMAGE/attack/knives.bmp", 768, 64, 12, 1, true, RGB(255, 255, 255));

	return S_OK;
}

void eriKnives::release()
{
}

void eriKnives::update()
{
	x += cosf(angle) * 10.0f;
	y += -sinf(angle) * 10.0f;
	_RECT = RectMakeCenter(x, y, 10, 10);
	if (inputTime + 2.5f < TIMEMANAGER->getWorldTime()) collisionTrue();
}

void eriKnives::render()
{
	Rectangle(getMemDC(), _RECT.left, _RECT.top, _RECT.right, _RECT.bottom);
	_image->frameRender(getMemDC(), x - _image->getFrameWidth() / 2, y - _image->getFrameHeight() / 2, angle / (PI / 6.0f), 0);
}

eriKnives::eriKnives()
{
}

eriKnives::~eriKnives()
{
}
