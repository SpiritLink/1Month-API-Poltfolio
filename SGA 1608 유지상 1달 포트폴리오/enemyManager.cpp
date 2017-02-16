#include "stdafx.h"
#include "enemyManager.h"


HRESULT enemyManager::init(tileMap* tileMap, attackManager* _ATM)
{
	_tileMap = tileMap;
	_attackManager = _ATM;
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
		//죽고나서 렌더가 끝났는지 확인하고 지우게 처리해야 할듯
		if ((*_viEnemy)->getEnemyDie()) _viEnemy = _vEnemy.erase(_viEnemy);
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
		//좌표를 벗어난다면 렌더하지 않게 변경하자.
		(*_viEnemy)->render();
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
