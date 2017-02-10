#pragma once

#include "gameNode.h"
#include "enemy.h"
#include "tileMap.h"
#include "attackManager.h"

class enemyManager : public gameNode
{
private:
	vector<enemy*> _vEnemy;
	vector<enemy*>::iterator _viEnemy;
	tileMap* _tileMap;		//에너미 객체에게 타일맵을 넘겨주기 위해서 가지고 있는다.
	attackManager* _attackManager;
public:
	virtual HRESULT init(tileMap* _tileMap, attackManager* _ATM);
	virtual void release();
	virtual void update();
	virtual void render();

	void setAlien(int tileNum);
	void setGhost(int tileNum);
	void setMiniGhost(int tileNum);
	void setFlower(int tileNum);
	void setOko(int tileNum);
	void setBomb(int tileNum);
	void setRotateCube(int tileNum);
	void setEri(int tileNum);

	void addEnemyX(int value);
	void addEnemyY(int value);

	vector<enemy*> getEnemyVector() { return _vEnemy; }

	enemyManager();
	virtual ~enemyManager();
};

