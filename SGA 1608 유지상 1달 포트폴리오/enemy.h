#pragma once

#include "gameNode.h"
#include "tileMap.h"

class enemy : public gameNode
{
protected:
	float inputTime;	//���� �ð�
	float currentTime;	//Ư�� �ð��� �����ϱ� ���� ����
	tileMap* _tileMap;	//Ÿ�ϸ��� ������ ����. (�̴� ��ǥ���� , �浹ó�� ����)
	image* _image;		//�̹���
	RECT _hitArea;		//���� ��Ʈ�ڽ�
	float x, y;			//��ǥ
	int HP;				//ü��
	int frameCount;		//������ ī��Ʈ
	
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

class alien : public enemy		//�Ϲ� ���� (���ĸ�)
{
public:
	virtual HRESULT init(int tileNum, tileMap* _tileMap);
	virtual void release();
	virtual void update();
	virtual void render();

	alien();
	virtual ~alien();
};

class ghost : public enemy		//�Ϲ� ���� (����)
{
private:
	DIRECTION dir;
public:
	virtual HRESULT init(int tileNum, tileMap* _tileMap);
	virtual void release();
	virtual void update();
	virtual void render();

	ghost();
	virtual ~ghost();
};

class flower : public enemy
{
public:
	virtual HRESULT init(int tileNum, tileMap* _tileMap);
	virtual void release();
	virtual void update();
	virtual void render();

	flower();
	virtual ~flower();
};
class eri : public enemy		//ù��° ���� ����
{
private:
	DIRECTION dir;				//����
	ACTION status;				//���¸� ǥ���� �뵵
public:
	virtual HRESULT init(int tileNum, tileMap* _tileMap);
	virtual void release();
	virtual void update();
	virtual void render();

	void frameUpdate();			//������ �ൿ�� ���� ������ ������Ʈ �ӵ��� �ٸ��� �մϴ�.

	eri();
	virtual ~eri();
};