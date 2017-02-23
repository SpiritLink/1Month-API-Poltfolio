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

	void addItemX(int value) { x += value; }		//�������� X��ǥ�� �Ķ���� ��ŭ �߰�
	void addItemY(int value) { y += value; }		//�������� Y��ǥ�� �Ķ���� ��ŭ �߰�
	int getItemX() { return x; }					//�������� X��ǥ ��ȯ
	int getItemY() { return y; }					//�������� Y��ǥ ��ȯ
	bool getItemCollision() { return collision; }	//�������� �浹 ���� ��ȯ (�÷��̾ �����ߴ���)
	RECT getItemRect() { return itemRect; }			//�������� �浹 ���� ��ȯ 
	ITEMTYPE getItemType() { return itemType; }		//�������� ���� ��ȯ
	
	void setItemCollision() { collision = true; }	//�������� �浹��Ű�� �Լ�
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