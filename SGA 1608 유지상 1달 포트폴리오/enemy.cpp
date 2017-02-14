#include "stdafx.h"
#include "enemy.h"

#define ERISPEED 10
#define ERIDASHSPEED 20

HRESULT enemy::init(int tileNum, tileMap* _tileMap, attackManager* ATM)
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

HRESULT alien::init(int tileNum, tileMap* tileMap, attackManager* ATM)
{
	//��ӹ��� ���� �ʱ�ȭ
	_tileMap = tileMap;
	_attackManager = ATM;
	x = (_tileMap->getTiles()[tileNum].rc.left + _tileMap->getTiles()[tileNum].rc.right ) / 2;
	y = (_tileMap->getTiles()[tileNum].rc.top + _tileMap->getTiles()[tileNum].rc.bottom) / 2;
	inputTime = TIMEMANAGER->getWorldTime();
	currentTime = TIMEMANAGER->getWorldTime();
	_image = IMAGEMANAGER->addFrameImage("alien", "IMAGE/enemy/alien.bmp", 576, 64, 9, 1, true, RGB(0, 255, 255));
	frameCount = 0;
	HP = 3;
	die = false;
	alive = true;
	return S_OK;
}

void alien::release()
{
}

void alien::update()
{
	_hitArea = RectMakeCenter(x, y, _image->getFrameWidth() - 30, _image->getFrameHeight() - 20);
	if (currentTime + 0.1f < TIMEMANAGER->getWorldTime() && alive)
	{
		currentTime = TIMEMANAGER->getWorldTime();
		++frameCount;
		if (frameCount > 8) frameCount = 0;
	}

	if (currentTime + 0.02f < TIMEMANAGER->getWorldTime() && !(alive))
	{
		currentTime = TIMEMANAGER->getWorldTime();
		++frameCount;
		if (frameCount > 9) die = true;
	}
}

void alien::render()
{
	_image->frameRender(getMemDC(), x - _image->getFrameWidth() / 2, y - _image->getFrameHeight() / 2,frameCount, 0);
	if (!(alive)) IMAGEMANAGER->findImage("boomEffect")->frameRender(getMemDC(), x - IMAGEMANAGER->findImage("boomEffect")->getFrameWidth() / 2,
		y - IMAGEMANAGER->findImage("boomEffect")->getFrameHeight() / 2, frameCount, 0);
}

alien::alien()
{
}

alien::~alien()
{
}

HRESULT ghost::init(int tileNum, tileMap * tileMap, attackManager* ATM)
{
	//��ӹ��� ���� �ʱ�ȭ
	_tileMap = tileMap;
	_attackManager = ATM;
	x = (_tileMap->getTiles()[tileNum].rc.left + _tileMap->getTiles()[tileNum].rc.right) / 2;
	y = (_tileMap->getTiles()[tileNum].rc.top + _tileMap->getTiles()[tileNum].rc.bottom) / 2;
	inputTime = TIMEMANAGER->getWorldTime();
	currentTime = TIMEMANAGER->getWorldTime();
	_image = IMAGEMANAGER->addFrameImage("ghost", "IMAGE/enemy/ghost.bmp", 256, 128, 4, 2, true, RGB(255, 0, 255));
	frameCount = 0;
	HP = 3;
	die = false;
	alive = true;
	//������� �ʱ�ȭ
	dir = LEFT;
	

	return S_OK;
}

void ghost::release()
{
}

void ghost::update()
{
	_hitArea = RectMakeCenter(x, y, 30, 40);
	if (currentTime + 0.1f < TIMEMANAGER->getWorldTime() && alive)
	{
		currentTime = TIMEMANAGER->getWorldTime();
		++frameCount;
	}
	if (currentTime + 0.02f < TIMEMANAGER->getWorldTime() && !(alive))
	{
		currentTime = TIMEMANAGER->getWorldTime();
		++frameCount;
		if (frameCount > 9) die = true;
	}
}

void ghost::render()
{
	switch (dir)
	{
	case RIGHT:_image->frameRender(getMemDC(), x - _image->getFrameWidth() / 2, y - _image->getFrameHeight() / 2, frameCount, 0); break;
	case LEFT: _image->frameRender(getMemDC(), x - _image->getFrameWidth() / 2, y - _image->getFrameHeight() / 2, frameCount, 1); break;
	}
	if (!(alive))IMAGEMANAGER->findImage("boomEffect")->frameRender(getMemDC(), x - IMAGEMANAGER->findImage("boomEffect")->getFrameWidth() / 2,
		y - IMAGEMANAGER->findImage("boomEffect")->getFrameHeight() / 2, frameCount, 0);
}

ghost::ghost()
{
}

ghost::~ghost()
{
}

HRESULT flower::init(int tileNum, tileMap * tileMap, attackManager* ATM)
{
	//��ӹ��� ���� �ʱ�ȭ
	IMAGEMANAGER->addFrameImage("boomEffect", "IMAGE/EFFECT/boomEffect.bmp", 590, 59, 10, 1, true, RGB(255, 255, 255));
	_tileMap = tileMap;
	_attackManager = ATM;
	x = (_tileMap->getTiles()[tileNum].rc.left + _tileMap->getTiles()[tileNum].rc.right) / 2;
	y = _tileMap->getTiles()[tileNum].rc.bottom;
	inputTime = TIMEMANAGER->getWorldTime();
	currentTime = TIMEMANAGER->getWorldTime();
	_image = IMAGEMANAGER->addFrameImage("flower", "IMAGE/enemy/flower.bmp", 1344, 64, 21, 1, true, RGB(255, 0, 255));
	frameCount = 0;
	HP = 3;
	die = false;
	alive = true;
	return S_OK;
}

void flower::release()
{
}

void flower::update()
{
	_hitArea = RectMake(x - _image->getFrameWidth() / 2, y - _image->getFrameHeight() + 10, _image->getFrameWidth() - 20, _image->getFrameHeight() - 10);
		
	if (currentTime + 0.05f < TIMEMANAGER->getWorldTime() && alive)
	{
		currentTime = TIMEMANAGER->getWorldTime();
		++frameCount;
		if (frameCount > 20) frameCount = 0;
	}

	if (currentTime + 0.02f < TIMEMANAGER->getWorldTime() && !(alive))
	{
		currentTime = TIMEMANAGER->getWorldTime();
		++frameCount;
		if (frameCount > 9) die = true;
	}
}

void flower::render()
{
	_image->frameRender(getMemDC(), x - IMAGEMANAGER->findImage("boomEffect")->getFrameWidth() / 2, y - IMAGEMANAGER->findImage("boomEffect")->getFrameHeight(), frameCount, 0);
	if(!(alive))IMAGEMANAGER->findImage("boomEffect")->frameRender(getMemDC(), _hitArea.left, 
		_hitArea.top,frameCount, 0);
}

flower::flower()
{
}

flower::~flower()
{
}

HRESULT oko::init(int tileNum, tileMap * tileMap, attackManager * ATM)
{
	//��ӹ��� ���� �ʱ�ȭ
	_tileMap = tileMap;
	_attackManager = ATM;
	x = (_tileMap->getTiles()[tileNum].rc.left + _tileMap->getTiles()[tileNum].rc.right) / 2;
	y = (_tileMap->getTiles()[tileNum].rc.top + _tileMap->getTiles()[tileNum].rc.bottom) / 2;
	inputTime = TIMEMANAGER->getWorldTime();
	currentTime = TIMEMANAGER->getWorldTime();
	_image = IMAGEMANAGER->addFrameImage("oko", "IMAGE/enemy/oko.bmp", 600, 50, 12, 1, true, RGB(0, 0, 0));
	frameCount = 0;
	HP = 9999;
	die = false;
	alive = true;
	//��� ���� �ʱ�ȭ
	status = 0;

	//��� �Լ��� ���� �ʱ�ȭ
	firstCollisionTileCheck();
	return S_OK;
}

void oko::release()
{
}

void oko::update()
{
	_detectArea = RectMake(x - _image->getFrameWidth() / 2, y - _image->getFrameHeight() / 2, 50, 400);
	_hitArea = RectMakeCenter(x, y, _image->getFrameWidth() - 10, _image->getFrameHeight() - 10);
	collisionTileCheck();	//�浹���� Ÿ���� Ȯ���Ѵ�.
	if (currentTime + 0.25f < TIMEMANAGER->getWorldTime())
	{
		frameCount++;
		if (frameCount > 11) frameCount = 0;
	}

	//�÷��̾ ���� ������ ��´ٸ� ���¸� 1�� �����Ѵ�.
	if (PtInRect(&_detectArea, PointMake(DATABASE->getPlayerX(), DATABASE->getPlayerY())) && status == 0) status = 1;
	okoMove();
}

void oko::render()
{
	_image->frameRender(getMemDC(), x - _image->getFrameWidth() / 2, y - _image->getFrameHeight() / 2, frameCount, 0);
}

void oko::firstCollisionTileCheck()
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

void oko::collisionTileCheck()
{
	//�浹������ �� ���� ����� ���� ������ ����.
	for (int i = currentCollisionTile - 1; i < currentCollisionTile + 2; ++i)
	{
		for (int j = -1; j < 2; ++j)
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

void oko::okoMove()
{
	switch (status)
	{
	case 0:
		break;
	case 1:
		if (PtInRect(&_tileMap->getTiles()[currentCollisionTile + TILEX].rc, PointMake(x, y + TILESIZE / 2)))
		{
			if (_tileMap->getTiles()[currentCollisionTile + TILEX].obj != OBJ_GROUND)
			{
				y += 10;
			}
			else
			{
				status = 2;
			}
		}
		else
		{
			y += 10;
		}
		break;
	case 2:
		if (PtInRect(&_tileMap->getTiles()[currentCollisionTile - TILEX].rc, PointMake(x, y - TILESIZE / 2)))
		{
			if (_tileMap->getTiles()[currentCollisionTile - TILEX].obj != OBJ_GROUND)
			{
				y -= 10;
			}
			else
			{
				status = 0;
			}
		}
		else
		{
			y -= 10;
		}
		break;
	}
}

oko::oko()
{
}

oko::~oko()
{
}

HRESULT bomb::init(int tileNum, tileMap * tileMap, attackManager * ATM)
{
	//��ӹ��� ���� �ʱ�ȭ
	_tileMap = tileMap;
	_attackManager = ATM;
	x = (_tileMap->getTiles()[tileNum].rc.left + _tileMap->getTiles()[tileNum].rc.right) / 2;
	y = (_tileMap->getTiles()[tileNum].rc.top + _tileMap->getTiles()[tileNum].rc.bottom) / 2;
	inputTime = TIMEMANAGER->getWorldTime();
	currentTime = TIMEMANAGER->getWorldTime();
	_image = IMAGEMANAGER->addImage("bomb", "IMAGE/enemy/bomb.bmp", 50, 50,true, RGB(0, 0, 0));
	frameCount = 0;
	die = false;
	alive = true;
	HP = 99999;
	return S_OK;
}

void bomb::release()
{
}

void bomb::update()
{
	RectangleMakeCenter(getMemDC(), x, y, 10, 10);
	_hitArea = RectMakeCenter(x, y, _image->getWidth(), _image->getHeight());
}

void bomb::render()
{
	_image->render(getMemDC(), x - _image->getWidth() / 2, y - _image->getHeight() / 2);
	Rectangle(getMemDC(), _hitArea.left, _hitArea.top, _hitArea.right, _hitArea.bottom);
}

bomb::bomb()
{
}

bomb::~bomb()
{
}

HRESULT miniGhost::init(int tileNum, tileMap * tileMap, attackManager * ATM)
{
	//��ӹ��� ���� �ʱ�ȭ
	_tileMap = tileMap;
	_attackManager = ATM;
	x = (_tileMap->getTiles()[tileNum].rc.left + _tileMap->getTiles()[tileNum].rc.right) / 2;
	y = (_tileMap->getTiles()[tileNum].rc.top + _tileMap->getTiles()[tileNum].rc.bottom) / 2;
	inputTime = TIMEMANAGER->getWorldTime();
	currentTime = TIMEMANAGER->getWorldTime();
	_image = IMAGEMANAGER->addFrameImage("miniGhost", "IMAGE/enemy/miniGhost.bmp", 52, 27, 4, 1, true, RGB(0, 128, 128));
	frameCount = 0;
	HP = 2;
	die = false;
	alive = true;

	//������� �ʱ�ȭ
	fristCollisionTileCheck();
	status = 0;
	return S_OK;
}

void miniGhost::release()
{
}

void miniGhost::update()
{
	_hitArea = RectMakeCenter(x, y, _image->getFrameWidth(), _image->getFrameHeight());
	if (currentTime + 0.02f < TIMEMANAGER->getWorldTime() && !(alive))
	{
		currentTime = TIMEMANAGER->getWorldTime();
		frameCount++;
		if (frameCount > 9) die = true;
	}
	if (currentTime + 0.2f < TIMEMANAGER->getWorldTime() && alive)
	{
		currentTime = TIMEMANAGER->getWorldTime();
		frameCount++;
		if (frameCount > 3) frameCount = 0;
	}
	miniGhostMove();		//miniGhost�� �����̴� �Լ�
	collisionTileCheck();								//Ÿ�� �浹�� ������Ʈ
}

void miniGhost::render()
{
	_image->frameRender(getMemDC(), x - _image->getFrameWidth() / 2, y - _image->getFrameHeight() / 2, frameCount, 0);
	if (!(alive)) IMAGEMANAGER->findImage("boomEffect")->frameRender(getMemDC(), x - IMAGEMANAGER->findImage("boomEffect")->getFrameWidth() / 2,
		y - IMAGEMANAGER->findImage("boomEffect")->getFrameHeight() / 2, frameCount, 0);
}

void miniGhost::fristCollisionTileCheck()
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

void miniGhost::collisionTileCheck()
{
	//�浹������ �� ���� ����� ���� ������ ����.
	for (int i = currentCollisionTile - 1; i < currentCollisionTile + 2; ++i)
	{
		for (int j = -1; j < 2; ++j)
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

void miniGhost::miniGhostMove()
{
	switch (status)
	{
	case 0:
		if (PtInRect(&_tileMap->getTiles()[currentCollisionTile + TILEX].rc, PointMake(x, y + _image->getFrameHeight() / 2)))
		{
			if (_tileMap->getTiles()[currentCollisionTile + TILEX].obj != OBJ_GROUND)
			{
				y += 10;
			}
			else
			{
				status = 1;
			}
		}
		else
		{
			y += 10;
		}
		break;
	case 1:
		if (PtInRect(&_tileMap->getTiles()[currentCollisionTile - TILEX].rc, PointMake(x, y - _image->getFrameHeight() / 2)))
		{
			if (_tileMap->getTiles()[currentCollisionTile - TILEX].obj != OBJ_GROUND)
			{
				y -= 10;
			}
			else
			{
				status = 0;
			}
		}
		else
		{
			y -= 10;
		}
		break;
	}
}

miniGhost::miniGhost()
{
}

miniGhost::~miniGhost()
{
}

HRESULT rotateCube::init(int tileNum, tileMap * tileMap, attackManager * ATM)
{
	//��ӹ��� ���� �ʱ�ȭ
	_tileMap = tileMap;
	_attackManager = ATM;
	x = _tileMap->getTiles()[tileNum].rc.left;
	y = (_tileMap->getTiles()[tileNum].rc.top + _tileMap->getTiles()[tileNum].rc.bottom) / 2;
	inputTime = TIMEMANAGER->getWorldTime();
	currentTime = TIMEMANAGER->getWorldTime();
	_image = IMAGEMANAGER->addImage("rotateCube", "IMAGE/enemy/rotateCube.bmp", 33, 33, true, RGB(0, 0, 0));
	frameCount = 0;
	HP = 2;
	die = false;
	alive = true;

	//������� �ʱ�ȭ
	firstCollisionTileCheck();
	initStatus();
	patternTime = TIMEMANAGER->getWorldTime();
	pattern = false;
	return S_OK;
}

void rotateCube::release()
{
}

void rotateCube::update()
{
	_hitArea = RectMakeCenter(x, y, 30, 30);
	pattern = (patternTime + 0.3f < TIMEMANAGER->getWorldTime()) ? true : false;
	if (updateTime + 0.1f < TIMEMANAGER->getWorldTime())
	{
		updateTime = TIMEMANAGER->getWorldTime();	//������Ʈ �ð� ����
		collisionTileCheck();						//�浹�ǰ� �ִ� Ÿ���� üũ�մϴ�.
	}
	rotateCubeMove();
}

void rotateCube::render()
{
	Rectangle(getMemDC(), _hitArea.left, _hitArea.top, _hitArea.right, _hitArea.bottom);
	_image->render(getMemDC(), x - _image->getWidth() / 2, y - _image->getHeight() / 2);
}

void rotateCube::initStatus()
{
	//�ڽ��� �������� ���� ��� ��ġ�� �ֳĿ� ���� ��������� �����մϴ�.
	status = -1;				//init�� ����� ����� �ȉ���� Ȯ���ϱ� ���� -1�� ���� �����մϴ�.
	if (_tileMap->getTiles()[currentCollisionTile + TILEX].obj == OBJ_GROUND) status = 0;	//�� Ÿ���� ���̸�
	if (_tileMap->getTiles()[currentCollisionTile - 1].obj == OBJ_GROUND) status = 1;		//���� Ÿ���� ���̸�
	if (_tileMap->getTiles()[currentCollisionTile - TILEX].obj == OBJ_GROUND) status = 2;	//���� Ÿ���� ���̸�
	if (_tileMap->getTiles()[currentCollisionTile + 1].obj == OBJ_GROUND) status = 3;		//������ Ÿ���� ���̸�
}

void rotateCube::firstCollisionTileCheck()
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

void rotateCube::collisionTileCheck()
{
	//�浹������ �� ���� ����� ���� ������ ����.
	for (int i = currentCollisionTile - 1; i < currentCollisionTile + 2; ++i)
	{
		for (int j = -1; j < 2; ++j)
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

void rotateCube::rotateCubeMove()
{
	switch (status)
	{
	case 0:			//���������� �����϶�
		x += 5;
		if (_tileMap->getTiles()[currentCollisionTile + TILEX].obj != OBJ_GROUND && pattern)
		{
			patternTime = TIMEMANAGER->getWorldTime();
			status = 1;
		}
		break;
	case 1:			//������ �����϶�
		y += 5;
		if (_tileMap->getTiles()[currentCollisionTile - 1].obj != OBJ_GROUND&& pattern)
		{
			patternTime = TIMEMANAGER->getWorldTime();
			status = 2;
		}
		break;
	case 2:			//�������� �����϶�
		x -= 5;
		if (_tileMap->getTiles()[currentCollisionTile - TILEX].obj != OBJ_GROUND&& pattern)
		{
			patternTime = TIMEMANAGER->getWorldTime();
			status = 3;
		}
		break;
	case 3:			//�������� �����϶�
		y -= 5;
		if (_tileMap->getTiles()[currentCollisionTile + 1].obj != OBJ_GROUND&& pattern)
		{
			patternTime = TIMEMANAGER->getWorldTime();
			status = 0;
		}
		break;
	}
}

rotateCube::rotateCube()
{
}

rotateCube::~rotateCube()
{
}


HRESULT eri::init(int tileNum, tileMap * tileMap, attackManager* ATM)
{
	//��ӹ��� ���� �ʱ�ȭ
	_tileMap = tileMap;
	_attackManager = ATM;
	inputTime = TIMEMANAGER->getWorldTime();
	currentTime = TIMEMANAGER->getWorldTime();
	x = (_tileMap->getTiles()[tileNum].rc.left + _tileMap->getTiles()[tileNum].rc.right )/ 2;
	y = (_tileMap->getTiles()[tileNum].rc.top + _tileMap->getTiles()[tileNum].rc.bottom) / 2;
	frameCount = 0;
	HP = 40;
	die = false;
	alive = true;

	//��� ���� �ʱ�ȭ
	_image = IMAGEMANAGER->addFrameImage("eri", "IMAGE/enemy/eri.bmp", 768, 1536, 8, 16, true, RGB(0, 0, 255));
	chargeAura = IMAGEMANAGER->addFrameImage("chargeAura", "IMAGE/EFFECT/chargeAura(dark).bmp", 312, 52, 6, 1, true, RGB(0, 0, 0));
	auraCount = 0;
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
	//Rectangle(getMemDC(), detectArea.left, detectArea.top, detectArea.right, detectArea.bottom);
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
		chargeAura->frameRender(getMemDC(), x - chargeAura->getFrameWidth() / 2, y - chargeAura->getFrameHeight(), auraCount, 0);
		if (dir == RIGHT)	_image->frameRender(getMemDC(), x - _image->getFrameWidth() / 2, y - _image->getFrameHeight() + 22, frameCount, 6);
		if (dir == LEFT)	_image->frameRender(getMemDC(), x - _image->getFrameWidth() / 2, y - _image->getFrameHeight() + 22, frameCount, 7);
		break;
	case ACTION_BACKDASH:
		if (dir == RIGHT)	_image->frameRender(getMemDC(), x - _image->getFrameWidth() / 2, y - _image->getFrameHeight() + 22, frameCount, 9);
		if (dir == LEFT)	_image->frameRender(getMemDC(), x - _image->getFrameWidth() / 2, y - _image->getFrameHeight() + 22, frameCount, 8);
		break;
	case ACTION_DASH:
		if (dir == RIGHT)	_image->frameRender(getMemDC(), x - _image->getFrameWidth() / 2, y - _image->getFrameHeight() + 22, frameCount, 10);
		if (dir == LEFT)	_image->frameRender(getMemDC(), x - _image->getFrameWidth() / 2, y - _image->getFrameHeight() + 22, frameCount, 11);
		break;
	case ACTION_THROW_ATTACK:
		if (dir == RIGHT)	_image->frameRender(getMemDC(), x - _image->getFrameWidth() / 2, y - _image->getFrameHeight() + 22, frameCount, 12);
		if (dir == LEFT)	_image->frameRender(getMemDC(), x - _image->getFrameWidth() / 2, y - _image->getFrameHeight() + 22, frameCount, 13);
		break;
	case ACTION_DIZZY:
		if (dir == RIGHT)	_image->frameRender(getMemDC(), x - _image->getFrameWidth() / 2, y - _image->getFrameHeight() + 22, frameCount, 14);
		if (dir == LEFT)	_image->frameRender(getMemDC(), x - _image->getFrameWidth() / 2, y - _image->getFrameHeight() + 22, frameCount, 15);
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
				frameCount = 0;
			}
		}
		break;
	case ACTION_CHARGE:
		if (currentTime + 0.05f < TIMEMANAGER->getWorldTime())
		{
			currentTime = TIMEMANAGER->getWorldTime();
			++frameCount;
			++auraCount;
			if (frameCount > 2) frameCount = 0;
			if (auraCount > 5) auraCount = 0;

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
	case ACTION_SLASH_ATTACK:
		if (currentTime + 0.05f < TIMEMANAGER->getWorldTime())
		{
			currentTime = TIMEMANAGER->getWorldTime();
			++frameCount;
			if (frameCount == 1)	_attackManager->eriWaveAttack(x, y, dir);
			if (frameCount > 3)
			{
				finalActionTime = TIMEMANAGER->getWorldTime();
				frameCount = 0;
				status = ACTION_NONE;
			}

		}
		break;
	case ACTION_THROW_ATTACK:
		if (currentTime + 0.05f < TIMEMANAGER->getWorldTime())
		{
			currentTime = TIMEMANAGER->getWorldTime();
			++frameCount;
			if (frameCount == 2)		_attackManager->eriKnivesAttack(x, y, dir);
			if (frameCount > 5)
			{
				finalActionTime = TIMEMANAGER->getWorldTime();
				frameCount = 0;
				status = ACTION_NONE;
			}
		}
		break;
	case ACTION_DIZZY:
		if (currentTime + 0.05f < TIMEMANAGER->getWorldTime())
		{
			currentTime = TIMEMANAGER->getWorldTime();
			++frameCount;
			if (frameCount > 7)
			{
				frameCount = 0;
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
	switch (status)
	{
	case ACTION_NONE:
		if (finalActionTime + 0.2f < TIMEMANAGER->getWorldTime()) //������ �ൿ�� 1�ʰ� �����ٸ�
		{
			switch (RND->getFromIntTo(0, 6))
			{
			//case 0: status = ACTION_BACKDASH; break;
			case 1: status = ACTION_CHARGE; break;
				//case 2: status = ACTION_DASH; break;
				//case 3: status = ACTION_THROW_ATTACK; break;
			//case 4: status = ACTION_RUN; break;
			//case 5:	status = ACTION_SLASH_ATTACK; break;
			//case 6: status = ACTION_THROW_ATTACK; break;
			}

			finalActionTime = TIMEMANAGER->getWorldTime();
		}
		break;
	case ACTION_BACKDASH:
		if (!(frameCount >= 2 && frameCount <= 5)) break;
		checkXAndMove(dir, ERISPEED);
		break;
	case ACTION_CHARGE:
		if (finalActionTime + 2.0f < TIMEMANAGER->getWorldTime())	//������ 2�ʵ��� �ѵ�
		{
			frameCount = 0;
			switch (RND->getFromIntTo(0, 1))
			{
			case 0: status = ACTION_DASH; break;
			case 1: status = ACTION_THROW_ATTACK;	break;
			}
			finalActionTime = TIMEMANAGER->getWorldTime();
		}
		break;
	case ACTION_DASH:
		if (checkXAndMove(dir, ERIDASHSPEED) == false)
		{
			status = ACTION_DIZZY;
			finalActionTime = TIMEMANAGER->getWorldTime();
		}
		break;
	case ACTION_JUMP:
		break;
	case ACTION_RUN:
		if (checkXAndMove(dir, ERISPEED) == false || finalActionTime + 1.0f < TIMEMANAGER->getWorldTime())
		{
			if (x > DATABASE->getPlayerX()) dir = LEFT;
			if (x < DATABASE->getPlayerX()) dir = RIGHT;
			status = ACTION_NONE;
			finalActionTime = TIMEMANAGER->getWorldTime();
		}
		break;
	case ACTION_SLASH_ATTACK:
		break;
	case ACTION_THROW_ATTACK:
		break;
	case ACTION_DIZZY:
		if (finalActionTime + 2.5f < TIMEMANAGER->getWorldTime())
		{
			if (x > DATABASE->getPlayerX()) dir = LEFT;
			if (x < DATABASE->getPlayerX()) dir = RIGHT;
			status = ACTION_NONE;
			finalActionTime = TIMEMANAGER->getWorldTime();
		}
		break;
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
	case ACTION_DIZZY: sprintf(str1, "ACTION_DIZZY"); break;
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

