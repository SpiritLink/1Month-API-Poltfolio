#pragma once

#include "gameNode.h"

class attack : public gameNode			//����� ���� �뵵
{
protected:
	float inputTime;		//������ ���Ե� �ð�
	bool checkCollision;	//�浹�� ó�� ����� Ȯ���ϴ� ����
	ATTACKTYPE _attackType;	//������ ������ �����ϱ� ���� ����
	image* _image;			//�̹���
	RECT _RECT;				//�浹��Ʈ
	float x, y;				//��ǥ
	float speed;			//�̵� �ӵ�
	
public:
	virtual HRESULT init(float inputX, float inputY);
	virtual void release();
	virtual void update();
	virtual void render();

	float getInputTime() { return inputTime; }
	ATTACKTYPE getAttackType() { return _attackType; }
	bool getCheckCollision() { return checkCollision; }

	void setAttackType(ATTACKTYPE Type) { _attackType = Type; }
	void collisionTrue() { checkCollision = true; }
	void addX(int value) { x += value; }
	void addY(int value) { y += value; }
	attack();
	virtual ~attack();
};

class playerSlash : public attack
{
public:
	virtual HRESULT init(float inputX, float inputY);
	virtual void release();
	virtual void update();
	virtual void render();

	playerSlash();
	virtual ~playerSlash();
};

class playerThrow : public attack
{
public:
	virtual HRESULT init(float inputX, float inputY);
	virtual void release();
	virtual void update();
	virtual void render();

	playerThrow();
	virtual ~playerThrow();

};

class eriWave : public attack
{
public:
	virtual HRESULT init(float inputX, float inputY);
	virtual void release();
	virtual void update();
	virtual void render();

	eriWave();
	virtual ~eriWave();
};