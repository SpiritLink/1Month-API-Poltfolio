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
	bool die;						//�׾����� Ȯ���ϴ� ����
	bool alive;						//����ִ��� Ȯ���ϴ� ���� ->�״� ������ Ȯ���ϱ� ���� ������ �߰�
	
public:
	virtual HRESULT init(int tileNum, tileMap* _tileMap, attackManager* ATM);
	virtual void release();
	virtual void update();
	virtual void render();

	void addEnemyX(int value) { x += value; }	//���ʹ��� X��ǥ�� �Ķ���͸�ŭ ���� ���Ѵ�.
	void addEnemyY(int value) { y += value; }	//���ʹ��� Y��ǥ�� �Ķ���͸�ŭ ���� ���Ѵ�.
	void addEnemyHP(int value) { HP += value; }	//���ʹ��� HP�� �Ķ���͸�ŭ ���� ���Ѵ�.
	void setAliveFalse() { alive = false; }		//���ʹ��� ������ false�� �ٲ۴�.
	void setFrameCountZero() { frameCount = 0; }//���ʹ��� ������ ī��Ʈ�� 0���� �ٲ۴�. 

	RECT getEnemyRect() { return _hitArea; }	//���� RECT�� ��ȯ�Ѵ�.
	int getEnemyHP() { return HP; }				//���ʹ��� HP�� ��ȯ�Ѵ�.
	bool getEnemyDie() { return die; };			//���ʹ��� ���� ���θ� ��ȯ�Ѵ�.
	bool getEnemyAlive() { return alive; }		//���ʹ��� ���� ���θ� ��ȯ�Ѵ�.
	int getEnemyX() { return x; }				//���ʹ��� X��ǥ�� ��ȯ�Ѵ�.
	int getEnemyY() { return y; }				//���ʹ��� Y��ǥ�� ��ȯ�Ѵ�.

	enemy();
	virtual ~enemy();
};

class alien : public enemy		//�Ϲ� ���� (���ĸ�)
{
private:
	RECT detectArea;
	float angle;
	float patternTime;
	bool nowDetect;
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

class miniGhost : public enemy
{
private:
	int status;					//���� , �ϰ� , ��� ���� ������ ���� ����
	int currentCollisionTile;	//���� �浹���� Ÿ���� Ȯ���� ����

public:
	virtual HRESULT init(int tileNum, tileMap* _tileMap, attackManager* ATM);
	virtual void release();
	virtual void update();
	virtual void render();

	void fristCollisionTileCheck();
	void collisionTileCheck();
	void miniGhostMove();
	miniGhost();
	virtual ~miniGhost();
};

class rotateCube : public enemy
{
private:
	int status;
	int currentCollisionTile;	//���� �浹���� Ÿ���� Ȯ���� ����
	float patternTime;			//���� ������ ���� ����
	bool pattern;				//���� ������ Ȯ���ϱ� ���� ����
	float updateTime;			//������Ʈ �ð� ������ ���� ����
public:
	virtual HRESULT init(int tileNum, tileMap* _tileMap, attackManager* ATM);
	virtual void release();
	virtual void update();
	virtual void render();

	void initStatus();				//Ÿ���� ���¸� Ȯ���ϰ� ����������� �������� �����մϴ�.
	void firstCollisionTileCheck();
	void collisionTileCheck();
	void rotateCubeMove();

	rotateCube();
	virtual ~rotateCube();
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

	bool dieCheck;
	float dieTime;
public:
	virtual HRESULT init(int tileNum, tileMap* _tileMap, attackManager* ATM);
	virtual void release();
	virtual void update();
	virtual void render();

	void frameUpdate();				//������ �ൿ�� ���� ������ ������Ʈ �ӵ��� �ٸ��� �մϴ�.
	void firstCollisionTileCheck();	//ó�� ���Ÿ�ϰ� �浹�� üũ�մϴ�.
	void collisionTileCheck();		//���� �ֺ� Ÿ�ϰ� �浹�� üũ�մϴ�.
	void eriAI();					//�������� eri�� AI�Դϴ�.
	bool checkXAndMove(DIRECTION dir,int value);	//X��ǥ������ ���¸� Ȯ���ϰ� �̵���Ŵ.
	void eriGravity();				// ������ �̵� �Լ�
	void testFunction();			//�׽�Ʈ�� �Լ��Դϴ�.

	eri();
	virtual ~eri();
};