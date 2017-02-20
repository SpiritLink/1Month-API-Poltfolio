#pragma once

#include "gameNode.h"
#include "player.h"
#include "attack.h"
#include "enemy.h"
#include "attackManager.h"
#include "enemyManager.h"
#include "objectManager.h"

class collision
{
private:
	player* _player;
	vector<enemy*>::iterator _viEnemy;
	vector<attack*>::iterator _viAttack;
	vector<item*>::iterator _viItem;
	float currentTime;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update(player* _player, vector<enemy*> _vEnemy, vector<attack*> _vAttack,vector<item*> _vItem);
	virtual void render();

	collision();
	virtual ~collision();
};

