#pragma once

#include "gameNode.h"
#include "tileMap.h"
#include "attackManager.h"


class enemy : public gameNode
{
protected:
	float inputTime;				//���� �ð�
	float currentTime;				//Ư�� �ð��� �����ϱ� ���� ����
	tileMap* _tileMap;				//Ÿ�ϸ��� ������ ����. (�̴� ��ǥ���� , �浹ó�� ����)
	attackManager* _attackManager;	//���ݰ�ü ������ ����
	image* _image;					//�̹���
	RECT _hitArea;					//���� ��Ʈ�ڽ�
	float x, y;						//��ǥ
	int HP;							//ü��
	int frameCount;					//������ ī��Ʈ
	
public:
	virtual HRESULT init(int tileNum, tileMap* _tileMap, attackManager* ATM);
	virtual void release();
	virtual void update();
	virtual void render();

	void addEnemyX(int value) { x += value; }
	void addEnemyY(int value) { y += value; }
	
	RECT getEnemyRect() { return _hitArea; }	//���� RECT�� ��ȯ�Ѵ�.

	enemy();
	virtual ~enemy();
};

class alien : public enemy		//�Ϲ� ���� (���ĸ�)
{
public:
	virtual HRESULT init(int tileNum, tileMap* _tileMap, attackManager* ATM);
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
	virtual HRESULT init(int tileNum, tileMap* _tileMap, attackManager* ATM);
	virtual void release();
	virtual void update();
	virtual void render();

	ghost();
	virtual ~ghost();
};

class flower : public enemy
{
public:
	virtual HRESULT init(int tileNum, tileMap* _tileMap, attackManager* ATM);
	virtual void release();
	virtual void update();
	virtual void render();

	flower();
	virtual ~flower();
};

class oko : public enemy
{
private:
	RECT _detectArea;	//������ ���� Rect����
	int status;			//���� , �ϰ� , ��� ���� ������ ���� ����

	int currentCollisionTile;	//���� �浹���� Ÿ���� Ȯ���� ����
public:
	virtual HRESULT init(int tileNum, tileMap* _tileMap, attackManager* ATM);
	virtual void release();
	virtual void update();
	virtual void render();

	void firstCollisionTileCheck();
	void collisionTileCheck();
	void okoMove();

	oko();
	virtual ~oko();
};

class bomb : public enemy
{
public:
	virtual HRESULT init(int tileNum, tileMap* _tileMap, attackManager* ATM);
	virtual void release();
	virtual void update();
	virtual void render();

	bomb();
	virtual ~bomb();
};
class eri : public enemy		//ù��° ���� ����
{
private:
	float gravity;				//������ ������ �߷�
	DIRECTION dir;				//����
	ACTION status;				//���¸� ǥ���� �뵵
	RECT detectArea;			//�÷��̾ ���� ������ �ִ��� Ȯ���ϱ� ���� �뵵

	float finalActionTime;		//������ ������ ���� �ð��� ����Ѵ�. (���� ���̿� ���� �α� ���ؼ�)
	float hitTime;				//������ ������ �������� �ѹ��� ���� ���ϰ� ó���Ѵ�.
	bool invincible;			//���� ���¸� ǥ���ϴ� ����

	int currentCollisionTile;	//���� �浹���� Ÿ���� Ȯ���� ����

	image* chargeAura;			//���� ���� ���� ����Ʈ
	int auraCount;				//���� �������� �ѱ�� ���� ���� ī��Ʈ

public:
	virtual HRESULT init(int tileNum, tileMap* _tileMap, attackManager* ATM);
	virtual void release();
	virtual void update();
	virtual void render();

	void frameUpdate();				//������ �ൿ�� ���� ������ ������Ʈ �ӵ��� �ٸ��� �մϴ�.
	void firstCollisionTileCheck();	//ó�� ���Ÿ�ϰ� �浹�� üũ�մϴ�.
	void collisionTileCheck();		//���� �ֺ� Ÿ�ϰ� �浹�� üũ�մϴ�.
	void eriAI();					//�������� eri�� AI�Դϴ�.
	bool checkXAndMove(DIRECTION dir,int value);		//X��ǥ������ ���¸� Ȯ���ϰ� �̵���Ŵ.

	void eriGravity();				// ������ �̵� �Լ�

	void testFunction();		//�׽�Ʈ�� �Լ��Դϴ�.


	eri();
	virtual ~eri();
};