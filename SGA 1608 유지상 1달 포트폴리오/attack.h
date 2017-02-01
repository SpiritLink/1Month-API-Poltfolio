#pragma once

#include "gameNode.h"

class attack : public gameNode			//����� ���� �뵵
{
protected:
	float inputTime;//������ ���Ե� �ð�
	image* _image;	//�̹���
	RECT _RECT;		//�浹��Ʈ
	float x, y;		//��ǥ
	float speed;	//�̵� �ӵ�
	
public:
	virtual HRESULT init(float inputX, float inputY);
	virtual void release();
	virtual void update();
	virtual void render();

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