#pragma once

#include "gameNode.h"
#include "enemy.h"
#include "tileMap.h"

class enemyManager : public gameNode
{
private:
	vector<enemy*> _vEnemy;
	vector<enemy*>::iterator _viEnemy;
	tileMap* _tileMap;		//에너미 객체에게 타일맵을 넘겨주기 위해서 가지고 있는다.
public:
	virtual HRESULT init(tileMap* _tileMap);
	virtual void release();
	virtual void update();
	virtual void render();

	void setAlien(int tileNum);
	void setGhost(int tileNum);
	void setEri(int tileNum);

	void addEnemyX(int value);
	void addEnemyY(int value);

	enemyManager();
	virtual ~enemyManager();
};

