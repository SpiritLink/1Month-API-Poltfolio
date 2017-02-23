#include "stdafx.h"
#include "enemyManager.h"


HRESULT enemyManager::init(tileMap* tileMap, attackManager* _ATM, objectManager* _OBJ)
{
	_tileMap = tileMap;
	_attackManager = _ATM;
	_objectManager = _OBJ;
	return S_OK;
}

void enemyManager::release()
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end();)
	{
		(*_viEnemy)->release();
		SAFE_DELETE(*_viEnemy);
		_viEnemy = _vEnemy.erase(_viEnemy);
	}
}

void enemyManager::update()
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end();)
	{
		if ((*_viEnemy)->getEnemyDie())
		{
			//적이 죽었을때 20퍼센트 확률로 체력회복 아이템, 50퍼센트 확률로 수리검, 30퍼센트 확률로 꽝이 생성된다.
			switch (RND->getFromIntTo(1, 10))
			{
			case 1:	_objectManager->setHeart((*_viEnemy)->getEnemyX(), (*_viEnemy)->getEnemyY()); break;
			case 2:	_objectManager->setHeart((*_viEnemy)->getEnemyX(), (*_viEnemy)->getEnemyY()); break;
			case 3:	_objectManager->setShuriken((*_viEnemy)->getEnemyX(), (*_viEnemy)->getEnemyY()); break;
			case 4:	_objectManager->setShuriken((*_viEnemy)->getEnemyX(), (*_viEnemy)->getEnemyY()); break;
			case 5:	_objectManager->setShuriken((*_viEnemy)->getEnemyX(), (*_viEnemy)->getEnemyY()); break;
			case 6: _objectManager->setShuriken((*_viEnemy)->getEnemyX(), (*_viEnemy)->getEnemyY()); break;
			case 7:	_objectManager->setShuriken((*_viEnemy)->getEnemyX(), (*_viEnemy)->getEnemyY()); break;
			case 8:		break;
			case 9:		break;
			case 10:	break;
			}
			_viEnemy = _vEnemy.erase(_viEnemy);
		}
		else
		{
			//화면 내의 좌표에 있다면 업데이트 합니다.
			if ((*_viEnemy)->getEnemyX() < WINSIZEX + TILESIZE && (*_viEnemy)->getEnemyX() > -TILESIZE &&
				(*_viEnemy)->getEnemyY() < WINSIZEY + TILESIZE && (*_viEnemy)->getEnemyY() > -TILESIZE)
			{
				(*_viEnemy)->update();
			}
			//체력이 0미만으로 떨어진다면
			if ((*_viEnemy)->getEnemyHP() <= 0 && (*_viEnemy)->getEnemyAlive())		//피가 0이하로 떨어지면 죽는 모션을 연출하게 한다.
			{
				(*_viEnemy)->setAliveFalse();
				(*_viEnemy)->setFrameCountZero();
			}
			//다음 적을 확인합니다.
			++_viEnemy;
		}
	}
}

void enemyManager::render()
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		//화면 + TILESIZE 좌표 안에 있는 적들만 그립니다. (부하 최소화)
		if ((*_viEnemy)->getEnemyX() < WINSIZEX + 50 && (*_viEnemy)->getEnemyX() > -TILESIZE &&
			(*_viEnemy)->getEnemyY() < WINSIZEY + 50 && (*_viEnemy)->getEnemyY() > -TILESIZE)
		{
			(*_viEnemy)->render();
		}
	}
}

void enemyManager::setAlien(int tileNum)
{
	enemy* Enemy;
	Enemy = new alien;
	Enemy->init(tileNum, _tileMap,_attackManager);
	_vEnemy.push_back(Enemy);
}

void enemyManager::setGhost(int tileNum)
{
	enemy* Enemy;
	Enemy = new ghost;
	Enemy->init(tileNum, _tileMap,_attackManager);
	_vEnemy.push_back(Enemy);
}

void enemyManager::setMiniGhost(int tileNum)
{
	enemy* Enemy;
	Enemy = new miniGhost;
	Enemy->init(tileNum, _tileMap, _attackManager);
	_vEnemy.push_back(Enemy);
}

void enemyManager::setFlower(int tileNum)
{
	enemy* Enemy;
	Enemy = new flower;
	Enemy->init(tileNum, _tileMap, _attackManager);
	_vEnemy.push_back(Enemy);
}

void enemyManager::setOko(int tileNum)
{
	enemy* Enemy;
	Enemy = new oko;
	Enemy->init(tileNum, _tileMap, _attackManager);
	_vEnemy.push_back(Enemy);
}

void enemyManager::setBomb(int tileNum)
{
	enemy* Enemy;
	Enemy = new bomb;
	Enemy->init(tileNum, _tileMap, _attackManager);
	_vEnemy.push_back(Enemy);
}

void enemyManager::setRotateCube(int tileNum)
{
	enemy* Enemy;
	Enemy = new rotateCube;
	Enemy->init(tileNum, _tileMap, _attackManager);
	_vEnemy.push_back(Enemy);
}

void enemyManager::setEri(int tileNum)
{
	enemy* Enemy;
	Enemy = new eri;
	Enemy->init(tileNum, _tileMap, _attackManager);
	_vEnemy.push_back(Enemy);
}

void enemyManager::addEnemyX(int value)
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		(*_viEnemy)->addEnemyX(value);
	}
}

void enemyManager::addEnemyY(int value)
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		(*_viEnemy)->addEnemyY(value);
	}
}

enemyManager::enemyManager()
{
}


enemyManager::~enemyManager()
{
}
