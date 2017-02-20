#pragma once

#include "gameNode.h"

class item : public gameNode
{
protected:
	ITEMTYPE itemType;	//�������� ������  Ȯ���ϱ� ���� ����
	image* _IMG;	//�����۵��� ���� ������ �̹���
	RECT itemRect;	//������ �浹 ����
	float x, y;		//������ ��ǥ
	bool collision;	//�������� �浹�ߴ��� Ȯ���ϱ� ���� ����
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