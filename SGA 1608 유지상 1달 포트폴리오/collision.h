#pragma once

#include "gameNode.h"
#include "player.h"
#include "attackManager.h"
#include "enemyManager.h"

class collision
{
private:
	player* _player;
	attackManager* _attackManager;
	enemyManager* _enemyManager;
public:
	virtual HRESULT init(player* PL, attackManager* ATK, enemyManager* EMG);
	virtual void release();
	virtual void update();
	virtual void render();

	collision();
	virtual ~collision();
};

