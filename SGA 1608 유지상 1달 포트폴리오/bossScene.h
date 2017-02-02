#pragma once

#include "gameNode.h"
#include "player.h"
#include "tileMap.h"
#include "playerUI.h"
#include "attackManager.h"
#include "enemyManager.h"


class bossScene : public gameNode
{
private:
	tileMap* _tileMap;
	attackManager* _attackManager;
	enemyManager* _enemyManager;
	player* _player;
	playerUI* _playerUI;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	bossScene();
	virtual ~bossScene();
};

