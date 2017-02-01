#pragma once

#include "gameNode.h"
#include "tileMap.h"

class enemy : public gameNode
{
protected:
	float inputTime;	//삽입 시간
	float currentTime;	//특정 시간을 저장하기 위한 변수
	tileMap* _tileMap;	//타일맵을 가지고 있음. (이닛 좌표설정 , 충돌처리 목적)
	image* _image;	//이미지
	float x, y;		//좌표
	int HP;			//체력
	int frameCount;	//프레임 카운트
	
public:
	virtual HRESULT init(int tileNum, tileMap* _tileMap);
	virtual void release();
	virtual void update();
	virtual void render();

	void addEnemyX(int value) { x += value; }
	void addEnemyY(int value) { y += value; }

	enemy();
	virtual ~enemy();
};

class alien : public enemy
{
public:
	virtual HRESULT init(int tileNum, tileMap* _tileMap);
	virtual void release();
	virtual void update();
	virtual void render();

	alien();
	virtual ~alien();
};