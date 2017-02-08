#pragma once

#include "gameNode.h"
#include "player.h"
#include "tileMap.h"
#include "playerUI.h"
#include "collision.h"

class townScene : public gameNode
{
private:
	tileMap* _tileMap;
	attackManager* _attackManager;
	enemyManager* _enemyManager;
	player* _player;
	playerUI*	_playerUI;
	collision*	_collision;

	RECT Background;
	image* _backIMG;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void cameraMove();
	void cameraInit();
	townScene();
	virtual ~townScene();
};

