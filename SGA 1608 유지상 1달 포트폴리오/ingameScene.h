#pragma once

#include "gameNode.h"
#include "player.h"
#include "tileMap.h"
#include "playerUI.h"
#include "attackManager.h"
#include "enemyManager.h"
#include "objectManager.h"
#include "collision.h"


class ingameScene : public gameNode
{
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	ingameScene();
	virtual ~ingameScene();
};

class townScene : public gameNode
{
private:
	tileMap* _tileMap;
	attackManager* _attackManager;
	enemyManager* _enemyManager;
	player* _player;
	playerUI*	_playerUI;
	collision*	_collision;
	objectManager* _objectManager;

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

class field1Scene : public gameNode
{
private:
	tileMap* _tileMap;
	attackManager* _attackManager;
	enemyManager* _enemyManager;
	player* _player;
	playerUI* _playerUI;
	objectManager* _objectManager;
	collision* _collision;
	RECT Background;				//임계영역 설정 (접근 불가)
	image* _backIMG;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void initEnemy();
	void cameraMove();
	void cameraInit();
	void portal();

	field1Scene();
	virtual ~field1Scene();
};

class endingScene : public gameNode
{
private:
	tileMap* _tileMap;
	attackManager* _attackManager;
	enemyManager* _enemyManager;
	player* _player;
	playerUI* _playerUI;

	RECT Background;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void cameraMove();
	void cameraInit();
	endingScene();
	virtual ~endingScene();
};

class testScene : public gameNode
{
private:
	tileMap* _tileMap;
	attackManager* _attackManager;
	enemyManager* _enemyManager;
	image* _image;
	player* _player;
	playerUI* _playerUI;
	collision* _collision;
	objectManager* _objectManager;

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