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

	void addItemX(int value) { x += value; }
	void addItemY(int value) { y += value; }
	int getItemX() { return x; }
	int getItemY() { return y; }
	bool getItemCollision() { return collision; }
	RECT getItemRect() { return itemRect; }
	ITEMTYPE getItemType() { return itemType; }
	
	void setItemCollision() { collision = true; }
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