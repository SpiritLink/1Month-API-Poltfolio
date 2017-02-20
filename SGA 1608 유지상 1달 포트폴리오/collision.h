#pragma once

#include "gameNode.h"
#include "player.h"
#include "attack.h"
#include "enemy.h"
#include "attackManager.h"
#include "enemyManager.h"

class collision
{
private:
	player* _player;
	attackManager* _attackManager;
	enemyManager* _enemyManager;
	vector<enemy*>::iterator _viEnemy;
	vector<attack*>::iterator _viAttack;
	float currentTime;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update(player* _player, vector<enemy*> _vEnemy, vector<attack*> _vAttack);
	virtual void render();

	collision();
	virtual ~collision();
};

