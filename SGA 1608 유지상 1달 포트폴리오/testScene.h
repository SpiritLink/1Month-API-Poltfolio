#pragma once

#include "gameNode.h"
#include "player.h"
#include "tileMap.h"
#include "playerUI.h"
#include "attackManager.h"
#include "enemyManager.h"

class testScene : public gameNode
{
private:
	tileMap* _tileMap;
	attackManager* _attackManager;
	enemyManager* _enemyManager;
	image* _image;
	player* _player;
	playerUI* _playerUI;

	float cameraX;
	float cameraY;
	RECT Background;

	image* _test;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	
	void cameraMove();
	void cameraInit();
	void portal();
	testScene();
	virtual ~testScene();
};

