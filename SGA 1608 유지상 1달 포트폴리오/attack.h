#pragma once

#include "gameNode.h"

class attack : public gameNode			//상속을 위한 용도
{
protected:
	float inputTime;		//공격이 삽입된 시간
	bool checkCollision;	//충돌이 처리 됬는지 확인하는 변수
	bool die;				//공격삭제를 확인하기 위한 변수
	ATTACKTYPE _attackType;	//공격의 종류를 구분하기 위한 변수
	image* _image;			//이미지
	RECT _RECT;				//충돌렉트
	float x, y;				//좌표
	float speed;			//이동 속도
	float angle;			//각도는 칼에서만 사용됩니다.
	int frameCount;			//공용 프레임 카운트
	
public:
	virtual HRESULT init(float inputX, float inputY);
	virtual void release();
	virtual void update();
	virtual void render();

	float getInputTime() { return inputTime; }
	ATTACKTYPE getAttackType() { return _attackType; }
	bool getCheckCollision() { return checkCollision; }
	bool getDie() { return die; }
	RECT getAttackRect() { return _RECT; }
	float getAttackX() { return x; }
	float getAttackY() { return y; }

	void setAttackType(ATTACKTYPE Type) { _attackType = Type; }
	void setFrameCountZero() { frameCount = 0; }
	void collisionTrue() { checkCollision = true; }
	void addX(int value) { x += value; }
	void addY(int value) { y += value; }
	void setAngle(float _angle) { angle = _angle; }
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
private:
	float currentTime;
	bool alive;
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
private:
	int frameCount;
	float countTime;
public:
	virtual HRESULT init(float inputX, float inputY);
	virtual void release();
	virtual void update();
	virtual void render();

	eriWave();
	virtual ~eriWave();
};

class eriKnives : public attack
{
public:
	virtual HRESULT init(float inputX, float inputY);
	virtual void release();
	virtual void update();
	virtual void render();

	eriKnives();
	virtual ~eriKnives();
};