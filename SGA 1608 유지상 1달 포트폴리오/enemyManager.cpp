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
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		(*_viEnemy)->update();
	}
}

void enemyManager::render()
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
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
