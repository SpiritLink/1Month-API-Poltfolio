#include "stdafx.h"
#include "enemy.h"

#define ERISPEED 10
#define ERIDASHSPEED 20

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
	//��ӹ��� ���� �ʱ�ȭ
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
	//��ӹ��� ���� �ʱ�ȭ
	_tileMap = tileMap;
	x = (_tileMap->getTiles()[tileNum].rc.left + _tileMap->getTiles()[tileNum].rc.right) / 2;
	y = (_tileMap->getTiles()[tileNum].rc.top + _tileMap->getTiles()[tileNum].rc.bottom) / 2;
	inputTime = TIMEMANAGER->getWorldTime();
	currentTime = TIMEMANAGER->getWorldTime();
	_image = IMAGEMANAGER->addFrameImage("ghost", "IMAGE/enemy/ghost.bmp", 256, 128, 4, 2, true, RGB(255, 0, 255));
	frameCount = 0;

	//������� �ʱ�ȭ
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

HRESULT flower::init(int tileNum, tileMap * tileMap)
{
	//��ӹ��� ���� �ʱ�ȭ
	_tileMap = tileMap;
	x = (_tileMap->getTiles()[tileNum].rc.left + _tileMap->getTiles()[tileNum].rc.right) / 2;
	y = (_tileMap->getTiles()[tileNum].rc.top + _tileMap->getTiles()[tileNum].rc.bottom) / 2;
	inputTime = TIMEMANAGER->getWorldTime();
	currentTime = TIMEMANAGER->getWorldTime();
	_image = IMAGEMANAGER->addFrameImage("ghost", "IMAGE/enemy/flower.bmp", 1344, 64, 21, 1, true, RGB(255, 0, 255));
	frameCount = 0;
	return S_OK;
}

void flower::release()
{
}

void flower::update()
{
	_hitArea = RectMakeCenter(x, y, 30, 30);
	if (currentTime + 0.1f < TIMEMANAGER->getWorldTime())
	{
		currentTime = TIMEMANAGER->getWorldTime();
		++frameCount;
		if (frameCount > 20) frameCount = 0;
	}
}

void flower::render()
{
	_image->frameRender(getMemDC(), x, y, frameCount, 0);
}

flower::flower()
{
}

flower::~flower()
{
}


HRESULT eri::init(int tileNum, tileMap * tileMap)
{
	//��ӹ��� ���� �ʱ�ȭ
	inputTime = TIMEMANAGER->getWorldTime();
	currentTime = TIMEMANAGER->getWorldTime();
	_tileMap = tileMap;
	x = (_tileMap->getTiles()[tileNum].rc.left + _tileMap->getTiles()[tileNum].rc.right) / 2;
	y = (_tileMap->getTiles()[tileNum].rc.top + _tileMap->getTiles()[tileNum].rc.bottom) / 2;
	frameCount = 0;

	//��� ���� �ʱ�ȭ
	_image = IMAGEMANAGER->addFrameImage("eri", "IMAGE/enemy/eri.bmp", 768, 1334, 8, 14, true, RGB(0, 0, 255));
	dir = LEFT;
	status = ACTION_CHARGE;
	gravity = 0;
	hitTime = TIMEMANAGER->getWorldTime();
	finalActionTime = TIMEMANAGER->getWorldTime();
	invincible = false;	// ���� �������°� �ƴ�

	firstCollisionTileCheck();	//ó�� �浹Ÿ���� ������� Ȯ���մϴ�.
	return S_OK;
}

void eri::release()
{
}

void eri::update()
{
	_hitArea = RectMakeCenter(x, y, 50, 50);
	detectArea = RectMakeCenter(x, y, 1600, 300);
	gravity += GRAVITY;		//���� �߷� ó��
	DATABASE->setEriX(x);	//�̱������� ��ǥ�� ������
	DATABASE->setEriY(y);	//�̱������� ��ǥ�� ������
	//���� �������� ���´ٸ� ���� AI�� �����Ѵ�.
	if (PtInRect(&detectArea, PointMake(DATABASE->getPlayerX(), DATABASE->getPlayerY()))) eriAI();
	frameUpdate();
	collisionTileCheck();	//�浹 Ÿ�� ��ȣ�� ������Ʈ �մϴ�.
	eriGravity();				//Ÿ���� Ȯ���ϰ� �߷��� ó���մϴ�.
}

void eri::render()
{
	Rectangle(getMemDC(), detectArea.left, detectArea.top, detectArea.right, detectArea.bottom);
	switch (status)
	{
	case ACTION_NONE:
		if(dir == RIGHT)	_image->frameRender(getMemDC(), x - _image->getFrameWidth() / 2, y - _image->getFrameHeight() + 22, frameCount, 0);
		if(dir == LEFT)		_image->frameRender(getMemDC(), x - _image->getFrameWidth() / 2, y - _image->getFrameHeight() + 22, frameCount, 1);
		break;
	case ACTION_RUN:
		if (dir == RIGHT)	_image->frameRender(getMemDC(), x - _image->getFrameWidth() / 2, y - _image->getFrameHeight() + 22, frameCount, 2);
		if (dir == LEFT)	_image->frameRender(getMemDC(), x - _image->getFrameWidth() / 2, y - _image->getFrameHeight() + 22, frameCount, 3);
		break;
	case ACTION_SLASH_ATTACK:
		if (dir == RIGHT)	_image->frameRender(getMemDC(), x - _image->getFrameWidth() / 2, y - _image->getFrameHeight() + 32, frameCount, 4);
		if (dir == LEFT)	_image->frameRender(getMemDC(), x - _image->getFrameWidth() / 2, y - _image->getFrameHeight() + 32, frameCount, 5);
		break;
	case ACTION_CHARGE:
		if (dir == RIGHT)	_image->frameRender(getMemDC(), x - _image->getFrameWidth() / 2, y - _image->getFrameHeight() + 22, frameCount, 6);
		if (dir == LEFT)	_image->frameRender(getMemDC(), x - _image->getFrameWidth() / 2, y - _image->getFrameHeight() + 22, frameCount, 7);
		break;
	case ACTION_BACKDASH:
		if (dir == RIGHT)	_image->frameRender(getMemDC(), x - _image->getFrameWidth() / 2, y - _image->getFrameHeight() + 22, frameCount, 8);
		if (dir == LEFT)	_image->frameRender(getMemDC(), x - _image->getFrameWidth() / 2, y - _image->getFrameHeight() + 22, frameCount, 9);
		break;
	case ACTION_DASH:
		if (dir == RIGHT)	_image->frameRender(getMemDC(), x - _image->getFrameWidth() / 2, y - _image->getFrameHeight() + 22, frameCount, 10);
		if (dir == LEFT)	_image->frameRender(getMemDC(), x - _image->getFrameWidth() / 2, y - _image->getFrameHeight() + 22, frameCount, 11);
		break;
	case ACTION_THROW_ATTACK:
		if (dir == RIGHT)	_image->frameRender(getMemDC(), x - _image->getFrameWidth() / 2, y - _image->getFrameHeight() + 22, frameCount, 12);
		if (dir == LEFT)	_image->frameRender(getMemDC(), x - _image->getFrameWidth() / 2, y - _image->getFrameHeight() + 22, frameCount, 13);
		break;
	}
	RectangleMakeCenter(getMemDC(), x, y, 5, 5);
	testFunction();			//����� �Լ��Դϴ�.
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
			if (frameCount > 5)
			{
				finalActionTime = TIMEMANAGER->getWorldTime();
				frameCount = 0;
				status = ACTION_NONE;
			}
		}
		break;
	case ACTION_SLASH_ATTACK:
		if (currentTime + 0.05f < TIMEMANAGER->getWorldTime())
		{
			currentTime = TIMEMANAGER->getWorldTime();
			++frameCount;
			if (frameCount > 3) 
			{
				finalActionTime = TIMEMANAGER->getWorldTime();
				frameCount = 0;
				status = ACTION_NONE;
			}

		}
		break;
	case ACTION_CHARGE:
		if (currentTime + 0.05f < TIMEMANAGER->getWorldTime())
		{
			currentTime = TIMEMANAGER->getWorldTime();
			++frameCount;
			if (frameCount > 2)
			{
				frameCount = 0;
			}

		}
		break;
	case ACTION_BACKDASH:
		if (currentTime + 0.05f < TIMEMANAGER->getWorldTime())
		{
			currentTime = TIMEMANAGER->getWorldTime();
			++frameCount;
			if (frameCount > 7)
			{
				finalActionTime = TIMEMANAGER->getWorldTime();
				frameCount = 0;
				status = ACTION_NONE;
			}
		}
		break;
	case ACTION_DASH:
		if (currentTime + 0.05f < TIMEMANAGER->getWorldTime())
		{
			currentTime = TIMEMANAGER->getWorldTime();
			++frameCount;
			if (frameCount > 2)
			{
				frameCount = 0;
			}
		}
		break;
	case ACTION_THROW_ATTACK:
		if (currentTime + 0.05f < TIMEMANAGER->getWorldTime())
		{
			currentTime = TIMEMANAGER->getWorldTime();
			++frameCount;
			if (frameCount > 5)
			{
				finalActionTime = TIMEMANAGER->getWorldTime();
				frameCount = 0;
				status = ACTION_NONE;
			}
		}
		break;
	}
}

void eri::firstCollisionTileCheck()
{
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		if (PtInRect(&_tileMap->getTiles()[i].rc, PointMake(x, y)))
		{
			currentCollisionTile = i;
			break;
		}
	}
}

void eri::collisionTileCheck()
{
	//�浹������ �� ���� ����� ���� ������ ����.
	for (int i = currentCollisionTile - 2; i < currentCollisionTile + 2; ++i)
	{
		for (int j = -2; j < 3; ++j)
		{
			//ĳ���� �ֺ� 25���� Ÿ���� �浹�� ����Ѵ�. �̶� ������ ����� �ʵ��� ������ ������ ��� �Ѵ�.
			if (PtInRect(&_tileMap->getTiles()[i + j * TILEX].rc, PointMake(x, y)))
			{
				currentCollisionTile = i + j * TILEX;
				break;
			}
		}
	}
}

void eri::eriAI()
{
	////���� ������ ������ �����Ѵ� ���� �ӽ÷� ���⿡ ��ġ��.
	//if (x > DATABASE->getPlayerX()) dir = LEFT;
	//if (x < DATABASE->getPlayerX()) dir = RIGHT;

	if (finalActionTime + 0.2f < TIMEMANAGER->getWorldTime())	//������ �ൿ�� ���� 3�ʰ� �����ٸ�
	{
		switch (status)
		{
		case ACTION_NONE:						//�ƹ��͵� �ƴ� �����϶�
			switch (RND->getFromIntTo(0, 5))
			{
			case 0: status = ACTION_BACKDASH; break;
			case 1: status = ACTION_CHARGE; break;
			//case 2: status = ACTION_DASH; break;
			case 3: status = ACTION_THROW_ATTACK; break;
			case 4: status = ACTION_RUN; break;
			case 5:	status = ACTION_SLASH_ATTACK; break;
			}
			break;
		case ACTION_BACKDASH:
			if (!(frameCount >= 2 && frameCount <= 5)) break;
			checkXAndMove(dir, ERISPEED);
			break;
		case ACTION_CHARGE:
			if (finalActionTime + 2.0f < TIMEMANAGER->getWorldTime()) status = ACTION_DASH;
			break;
		case ACTION_DASH:
			if (checkXAndMove(dir, ERIDASHSPEED) == false)
			{
				if (x > DATABASE->getPlayerX()) dir = LEFT;
				if (x < DATABASE->getPlayerX()) dir = RIGHT;
				status = ACTION_NONE;
				finalActionTime = TIMEMANAGER->getWorldTime();
			}
			break;
		case ACTION_JUMP:
			break;
		case ACTION_RUN:
			checkXAndMove(dir, ERISPEED);
			break;
		case ACTION_SLASH_ATTACK:
			break;
		case ACTION_THROW_ATTACK:
			break;
		}
	}
}

bool eri::checkXAndMove(DIRECTION dir, int value)
{
	switch (dir)
	{
	case LEFT:
		if (PtInRect(&_tileMap->getTiles()[currentCollisionTile - 1].rc, PointMake(x - value, y)))
		{
			if (_tileMap->getTiles()[currentCollisionTile - 1].obj != OBJ_GROUND)
			{
				x -= value;
				return true;
			}
			if (_tileMap->getTiles()[currentCollisionTile - 1].obj == OBJ_GROUND)
				return false;
		}
		else
		{
			x -= value;
			return true;
		}
		break;
	case RIGHT:
		if (PtInRect(&_tileMap->getTiles()[currentCollisionTile + 1].rc, PointMake(x + value, y)))
		{
			if (_tileMap->getTiles()[currentCollisionTile + 1].obj != OBJ_GROUND)
			{
				x += value;
				return true;
			}
			if (_tileMap->getTiles()[currentCollisionTile + 1].obj == OBJ_GROUND) return false;
		}
		else
		{
			x += value;
			return true;
		}
		break;
	}
}

void eri::eriGravity()
{
	//������ ���� �浹������ ó��
	if (_tileMap->getTiles()[currentCollisionTile].obj == OBJ_GROUND)
	{
		if (gravity > 0) y = _tileMap->getTiles()[currentCollisionTile].rc.top - 1;		//�߷��� ������ ���Ҷ�
		if (gravity < 0) y = _tileMap->getTiles()[currentCollisionTile].rc.bottom + 1;	//�߷��� ���� ���Ҷ�
		gravity = 0;
	}

	//�߷� ����ó�� (������ ��������)
	if (gravity <= 1)
	{
		if (_tileMap->getTiles()[currentCollisionTile + TILEX].obj == OBJ_GROUND &&
			PtInRect(&_tileMap->getTiles()[currentCollisionTile + TILEX].rc, PointMake(x, y + gravity))) gravity = 0;
	}

	//�߷¿� �ش��ϴ� ����ŭ �����δ�.
	y += gravity;
}

void eri::testFunction()
{
	char str1[128];
	char str2[128];
	switch (status)
	{
	case ACTION_NONE: sprintf(str1, "ACTION_NONE"); break;
	case ACTION_RUN: sprintf(str1, "ACTION_RUN"); break;
	case ACTION_SLASH_ATTACK: sprintf(str1, "ACTION_SLASH_ATTACK"); break;
	case ACTION_CHARGE: sprintf(str1, "ACTION_CHARGE"); break;
	case ACTION_BACKDASH: sprintf(str1, "ACTION_BACKDASH"); break;
	case ACTION_DASH: sprintf(str1, "ACTION_DASH"); break;
	case ACTION_THROW_ATTACK: sprintf(str1, "ACTION_THROW_ATTACK"); break;
	}

	sprintf(str2, "%d", currentCollisionTile);
	TextOut(getMemDC(), 600, 100, str1, strlen(str1));
	TextOut(getMemDC(), 600, 130, str2, strlen(str2));
}

eri::eri()
{
}

eri::~eri()
{
}

