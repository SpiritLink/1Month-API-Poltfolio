#pragma once

#include "gameNode.h"
#include "player.h"
#include "tileMap.h"
#include "playerUI.h"
#include "attackManager.h"
#include "enemyManager.h"
#include "objectManager.h"
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
	objectManager* _objectManager;

	RECT Background;

	image* _black;
	image* _white;
	int alphaValue;				//화면의 페이드인 , 페이드 아웃을 표시하기 위한 변수
	SCREENSTATUS screenStatus;	//페이드 인 , 페이드 아웃이 끝났음을 확인하기 위한 변수.

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void changeAlphaValue();
	void portal();
	void cameraMove();
	void cameraInit();
	void initEnemyAndObject();

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

	image* _black;
	image* _white;
	int alphaValue;	//화면의 페이드인 , 페이드 아웃을 표시하기 위한 변수
	SCREENSTATUS screenStatus;	//페이드 인 , 페이드 아웃이 끝났음을 확인하기 위한 변수.

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void initEnemyAndObject();
	void cameraMove();
	void cameraInit();
	void changeAlphaValue();
	void portal();

	field1Scene();
	virtual ~field1Scene();
};

class endingScene : public gameNode
{
private:
	image* _IMG1;
	image* _IMG2;
	image* _IMG3;
	image* _IMG4;

	image* _black;

	int alphaValue;
	int IMGNumber;
	bool fadein;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

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