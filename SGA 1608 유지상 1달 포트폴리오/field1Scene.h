#pragma once

#include "gameNode.h"
#include "player.h"
#include "tileMap.h"
#include "playerUI.h"
#include "attackManager.h"
#include "enemyManager.h"
#include "collision.h"

class field1Scene : public gameNode
{
private:
	tileMap* _tileMap;
	attackManager* _attackManager;
	enemyManager* _enemyManager;
	player* _player;
	playerUI* _playerUI;
	collision* _collision;
	RECT Background;				//임계영역 설정 (접근 불가)
	image* _backIMG;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void cameraMove();
	void cameraInit();
	void portal();

	field1Scene();
	virtual ~field1Scene();
};

