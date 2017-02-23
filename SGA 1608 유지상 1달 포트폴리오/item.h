#pragma once

#include "gameNode.h"

class item : public gameNode
{
protected:
	ITEMTYPE itemType;	//아이템의 종류를  확인하기 위한 변수
	image* _IMG;	//아이템들이 가질 아이템 이미지
	RECT itemRect;	//아이템 충돌 영역
	float x, y;		//아이템 좌표
	bool collision;	//아이템이 충돌했는지 확인하기 위한 변수
public:
	virtual HRESULT init(float inputX, float inputY);
	virtual void release();
	virtual void update();
	virtual void render();

	void addItemX(int value) { x += value; }		//아이템의 X좌표에 파라미터 만큼 추가
	void addItemY(int value) { y += value; }		//아이템의 Y좌표에 파라미터 만큼 추가
	int getItemX() { return x; }					//아이템의 X좌표 바환
	int getItemY() { return y; }					//아이템의 Y좌표 반환
	bool getItemCollision() { return collision; }	//아이템의 충돌 여부 반환 (플레이어가 습득했는지)
	RECT getItemRect() { return itemRect; }			//아이템의 충돌 영역 반환 
	ITEMTYPE getItemType() { return itemType; }		//아이템의 종류 반환
	
	void setItemCollision() { collision = true; }	//아이템을 충돌시키는 함수
	item();
	virtual ~item();
};

class heart : public item
{
private:
	int frameCount;
public:
	virtual HRESULT init(float inputX, float inputY);
	virtual void release();
	virtual void update();
	virtual void render();
	heart();
	virtual ~heart();
};

class shuriken : public item
{
public:
	virtual HRESULT init(float inputX, float inputY);
	virtual void release();
	virtual void update();
	virtual void render();
	shuriken();
	virtual ~shuriken();
};

class saveBell : public item
{
public:
	virtual HRESULT init(float inputX, float inputY);
	virtual void release();
	virtual void update();
	virtual void render();

	saveBell();
	virtual ~saveBell();
};