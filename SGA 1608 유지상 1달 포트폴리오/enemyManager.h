#pragma once

#include "gameNode.h"
#include "enemy.h"
#include "tileMap.h"

class enemyManager : public gameNode
{
private:
	vector<enemy*> _vEnemy;
	vector<enemy*>::iterator _viEnemy;
	tileMap* _tileMap;		//���ʹ� ��ü���� Ÿ�ϸ��� �Ѱ��ֱ� ���ؼ� ������ �ִ´�.
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

