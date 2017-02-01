#pragma once

#include "gameNode.h"

class attack : public gameNode			//상속을 위한 용도
{
protected:
	float inputTime;//공격이 삽입된 시간
	image* _image;	//이미지
	RECT _RECT;		//충돌렉트
	float x, y;		//좌표
	float speed;	//이동 속도
	
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