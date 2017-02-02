#include "stdafx.h"
#include "enemy.h"


HRESULT enemy::init(int tileNum, tileMap* _tileMap)
{
	return S_OK;
}

void enemy::release()
{
}

void enemy::update()
{
}

void enemy::render()
{
}

enemy::enemy()
{
}


enemy::~enemy()
{
}

HRESULT alien::init(int tileNum, tileMap* tileMap)
{
	//상속받은 변수 초기화
	_tileMap = tileMap;
	x = (_tileMap->getTiles()[tileNum].rc.left + _tileMap->getTiles()[tileNum].rc.right) / 2;
	y = (_tileMap->getTiles()[tileNum].rc.top + _tileMap->getTiles()[tileNum].rc.bottom) / 2;
	inputTime = TIMEMANAGER->getWorldTime();
	currentTime = TIMEMANAGER->getWorldTime();
	_image = IMAGEMANAGER->addFrameImage("alien", "IMAGE/enemy/alien.bmp", 288, 32, 9, 1, true, RGB(0, 255, 255));
	frameCount = 0;
	return S_OK;
}

void alien::release()
{
}

void alien::update()
{
	_hitArea = RectMakeCenter(x, y, 30, 30);
	if (currentTime + 0.1f < TIMEMANAGER->getWorldTime())
	{
		currentTime = TIMEMANAGER->getWorldTime();
		++frameCount;
		if (frameCount > 8) frameCount = 0;
	}
}

void alien::render()
{
	_image->frameRender(getMemDC(), x, y,frameCount, 0);
	Rectangle(getMemDC(), _hitArea.left, _hitArea.top, _hitArea.right, _hitArea.bottom);
}

alien::alien()
{
}

alien::~alien()
{
}

HRESULT ghost::init(int tileNum, tileMap * tileMap)
{
	//상속받은 변수 초기화
	_tileMap = tileMap;
	x = (_tileMap->getTiles()[tileNum].rc.left + _tileMap->getTiles()[tileNum].rc.right) / 2;
	y = (_tileMap->getTiles()[tileNum].rc.top + _tileMap->getTiles()[tileNum].rc.bottom) / 2;
	inputTime = TIMEMANAGER->getWorldTime();
	currentTime = TIMEMANAGER->getWorldTime();
	_image = IMAGEMANAGER->addFrameImage("ghost", "IMAGE/enemy/ghost.bmp", 256, 128, 4, 2, true, RGB(255, 0, 255));
	frameCount = 0;

	//멤버변수 초기화
	dir = LEFT;

	return S_OK;
}

void ghost::release()
{
}

void ghost::update()
{
	_hitArea = RectMakeCenter(x, y, 30, 30);
	if (currentTime + 0.1f < TIMEMANAGER->getWorldTime())
	{
		currentTime = TIMEMANAGER->getWorldTime();
		++frameCount;
		if (frameCount > 3)
		{
			switch (dir)
			{
			case RIGHT: dir = LEFT; break;
			case LEFT: dir = RIGHT; break;
			}
			frameCount = 0;
		}
	}
}

void ghost::render()
{
	switch (dir)
	{
	case RIGHT:_image->frameRender(getMemDC(), x, y, frameCount, 0); break;
	case LEFT: _image->frameRender(getMemDC(), x, y, frameCount, 1); break;
	}
}

ghost::ghost()
{
}

ghost::~ghost()
{
}

HRESULT eri::init(int tileNum, tileMap * tileMap)
{
	//상속받은 변수 초기화
	inputTime = TIMEMANAGER->getWorldTime();
	currentTime = TIMEMANAGER->getWorldTime();
	_tileMap = tileMap;
	x = (_tileMap->getTiles()[tileNum].rc.left + _tileMap->getTiles()[tileNum].rc.right) / 2;
	y = (_tileMap->getTiles()[tileNum].rc.top + _tileMap->getTiles()[tileNum].rc.bottom) / 2;
	frameCount = 0;

	//멤버 변수 초기화
	_image = IMAGEMANAGER->addFrameImage("eri", "IMAGE/enemy/eri.bmp", 768, 1334, 8, 14, true, RGB(0, 0, 255));
	dir = LEFT;
	status = ACTION_THROW_ATTACK;

	return S_OK;
}

void eri::release()
{
}

void eri::update()
{
	_hitArea = RectMakeCenter(x, y, 50, 50);
	frameUpdate();
}

void eri::render()
{
	Rectangle(getMemDC(), _hitArea.left, _hitArea.top, _hitArea.right, _hitArea.bottom);
	switch (status)
	{
	case ACTION_NONE:
		if(dir == RIGHT)	_image->frameRender(getMemDC(), x, y, frameCount, 0);
		if(dir == LEFT)		_image->frameRender(getMemDC(), x, y, frameCount, 1);
		break;
	case ACTION_RUN:
		if (dir == RIGHT)	_image->frameRender(getMemDC(), x, y, frameCount, 2);
		if (dir == LEFT)	_image->frameRender(getMemDC(), x, y, frameCount, 3);
		break;
	case ACTION_SLASH_ATTACK:
		if (dir == RIGHT)	_image->frameRender(getMemDC(), x, y, frameCount, 4);
		if (dir == LEFT)	_image->frameRender(getMemDC(), x, y, frameCount, 5);
		break;
	case ACTION_CHARGE:
		if (dir == RIGHT)	_image->frameRender(getMemDC(), x, y, frameCount, 6);
		if (dir == LEFT)	_image->frameRender(getMemDC(), x, y, frameCount, 7);
		break;
	case ACTION_BACKDASH:
		if (dir == RIGHT)	_image->frameRender(getMemDC(), x, y, frameCount, 8);
		if (dir == LEFT)	_image->frameRender(getMemDC(), x, y, frameCount, 9);
		break;
	case ACTION_DASH:
		if (dir == RIGHT)	_image->frameRender(getMemDC(), x, y, frameCount, 10);
		if (dir == LEFT)	_image->frameRender(getMemDC(), x, y, frameCount, 11);
		break;
	case ACTION_THROW_ATTACK:
		if (dir == RIGHT)	_image->frameRender(getMemDC(), x, y, frameCount, 12);
		if (dir == LEFT)	_image->frameRender(getMemDC(), x, y, frameCount, 13);
		break;
	}
}

void eri::frameUpdate()
{
	switch (status)
	{
	case ACTION_NONE:
		frameCount = 0;
		break;
	case ACTION_RUN:
		if (currentTime + 0.05f < TIMEMANAGER->getWorldTime())
		{
			currentTime = TIMEMANAGER->getWorldTime();
			++frameCount;
			if (frameCount > 5) frameCount = 0;
		}
		break;
	case ACTION_SLASH_ATTACK:
		if (currentTime + 0.05f < TIMEMANAGER->getWorldTime())
		{
			currentTime = TIMEMANAGER->getWorldTime();
			++frameCount;
			if (frameCount > 3) frameCount = 0;			//최대 프레임일때
		}
		break;
	case ACTION_CHARGE:
		if (currentTime + 0.05f < TIMEMANAGER->getWorldTime())
		{
			currentTime = TIMEMANAGER->getWorldTime();
			++frameCount;
			if (frameCount > 2) frameCount = 0;
		}
		break;
	case ACTION_BACKDASH:
		if (currentTime + 0.05f < TIMEMANAGER->getWorldTime())
		{
			currentTime = TIMEMANAGER->getWorldTime();
			++frameCount;
			if (frameCount > 7) frameCount = 0;
		}
		break;
	case ACTION_DASH:
		if (currentTime + 0.05f < TIMEMANAGER->getWorldTime())
		{
			currentTime = TIMEMANAGER->getWorldTime();
			++frameCount;
			if (frameCount > 2) frameCount = 0;
		}
		break;
	case ACTION_THROW_ATTACK:
		if (currentTime + 0.05f < TIMEMANAGER->getWorldTime())
		{
			currentTime = TIMEMANAGER->getWorldTime();
			++frameCount;
			if (frameCount > 5) frameCount = 0;			//최대 프레임일때
		}
		break;
	}
}

eri::eri()
{
}

eri::~eri()
{
}

