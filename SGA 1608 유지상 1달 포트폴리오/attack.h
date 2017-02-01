#pragma once

#include "gameNode.h"

class attack : public gameNode			//����� ���� �뵵
{
protected:
	float inputTime;//������ ���Ե� �ð�
	ATTACKTYPE _attackType;	//������ ������ �����ϱ� ���� ����
	image* _image;	//�̹���
	RECT _RECT;		//�浹��Ʈ
	float x, y;		//��ǥ
	float speed;	//�̵� �ӵ�
	
public:
	virtual HRESULT init(float inputX, float inputY);
	virtual void release();
	virtual void update();
	virtual void render();

	float getInputTime() { return inputTime; }
	void setAttackType(ATTACKTYPE Type) { _attackType = Type; }

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