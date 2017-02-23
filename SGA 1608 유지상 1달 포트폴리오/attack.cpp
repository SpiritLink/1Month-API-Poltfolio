#include "stdafx.h"
#include "attack.h"


HRESULT attack::init(float inputX, float inputY)
{
	inputTime = TIMEMANAGER->getWorldTime();
	checkCollision = false;
	x = inputX;
	y = inputY;
	die = false;
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
	die = false;
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
	if (checkCollision) die = true;
}

void playerSlash::render()
{
	//Rectangle(getMemDC(), _RECT.left, _RECT.top, _RECT.right, _RECT.bottom);
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
	_image = IMAGEMANAGER->addFrameImage("shuriken", "IMAGE/attack/shuriken.bmp", 180, 30, 6, 1, true, RGB(255, 255, 255));
	IMAGEMANAGER->addFrameImage("playerThrowEffect", "IMAGE/effect/playerThrowEffect.bmp", 640, 128, 5, 1, true, RGB(0, 0, 0));
	frameCount = 0;
	checkCollision = false;
	x = inputX;
	y = inputY;
	alive = true;
	die = false;
	return S_OK;
}

void playerThrow::release()
{
}

void playerThrow::update()
{
	//충돌영역을 리사이즈 합니다.
	_RECT = RectMakeCenter(x, y, _image->getFrameWidth() - 10, _image->getFrameHeight() - 10);
	if (currentTime + 0.01f < TIMEMANAGER->getWorldTime())
	{
		currentTime = TIMEMANAGER->getWorldTime();
		frameCount++;
		if (frameCount > 5) frameCount = 0;
	}

	//공격의 종류에 따라 표창의 속도를 다르게 합니다.
	if (_attackType == ATTACK_PLAYER_THROW_LEFT && !(checkCollision)) x -= 20;
	if (_attackType == ATTACK_PLAYER_THROW_RIGHT && !(checkCollision)) x += 20;

	if (inputTime + 4.0f < TIMEMANAGER->getWorldTime()) collisionTrue();
	if (checkCollision && frameCount > 4) die = true;
}

void playerThrow::render()
{
	//Rectangle(getMemDC(), _RECT.left, _RECT.top, _RECT.right, _RECT.bottom);
	_image->frameRender(getMemDC(), x - _image->getFrameWidth() / 2, y - _image->getFrameHeight() / 2,frameCount,0);
	if (checkCollision) IMAGEMANAGER->findImage("playerThrowEffect")->frameRender(getMemDC(), x - IMAGEMANAGER->findImage("playerThrowEffect")->getFrameWidth() / 2, 
		y - IMAGEMANAGER->findImage("playerThrowEffect")->getFrameHeight() / 2, frameCount, 0);
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
	die = false;

	frameCount = 0;
	countTime = TIMEMANAGER->getWorldTime();
	_image = IMAGEMANAGER->addFrameImage("eriWave", "IMAGE/attack/eriWave.bmp", 224, 112, 4, 2, true, RGB(0, 128, 128));
	return S_OK;
}

void eriWave::release()
{
}

void eriWave::update()
{
	if (countTime + 0.05f < TIMEMANAGER->getWorldTime())
	{
		countTime = TIMEMANAGER->getWorldTime();
		++frameCount;
		if (frameCount > 3) frameCount = 0;
	}
	_RECT = RectMakeCenter(x, y, 56, 56);
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
	switch (_attackType)
	{
	case ATTACK_ERI_WAVE_LEFT:_image->frameRender(getMemDC(), x - _image->getFrameWidth() / 2, y - _image->getFrameHeight() / 2, frameCount, 1); break;
	case ATTACK_ERI_WAVE_RIGHT: _image->frameRender(getMemDC(), x - _image->getFrameWidth() / 2, y - _image->getFrameHeight() / 2, frameCount, 0); break;
	}
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
	_image = IMAGEMANAGER->addFrameImage("knives", "IMAGE/attack/knives.bmp", 768, 64, 12, 1, true, RGB(0, 0, 0));
	die = false;
	return S_OK;
}

void eriKnives::release()
{
}

void eriKnives::update()
{
	x += cosf(angle) * 15.0f;
	y += -sinf(angle) * 15.0f;
	_RECT = RectMakeCenter(x, y, 10, 10);
	if (inputTime + 2.5f < TIMEMANAGER->getWorldTime()) collisionTrue();
	if (checkCollision) die = true;
}

void eriKnives::render()
{
	_image->frameRender(getMemDC(), x - _image->getFrameWidth() / 2, y - _image->getFrameHeight() / 2, angle / (PI / 6.0f), 0);
}

eriKnives::eriKnives()
{
}

eriKnives::~eriKnives()
{
}
