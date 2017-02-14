#pragma once

#include "gameNode.h"
#include "tileMap.h"
#include "attackManager.h"


class enemy : public gameNode
{
protected:
	float inputTime;				//삽입 시간
	float currentTime;				//특정 시간을 저장하기 위한 변수
	tileMap* _tileMap;				//타일맵을 가지고 있음. (이닛 좌표설정 , 충돌처리 목적)
	attackManager* _attackManager;	//공격객체 생성을 위해
	image* _image;					//이미지
	RECT _hitArea;					//몬스터 히트박스
	float x, y;						//좌표
	int HP;							//체력
	int frameCount;					//프레임 카운트
	bool die;						//죽었는지 확인하는 변수
	bool alive;						//살아있는지 확인하는 변수 ->죽는 과정을 확인하기 위해 별도로 추가
	
public:
	virtual HRESULT init(int tileNum, tileMap* _tileMap, attackManager* ATM);
	virtual void release();
	virtual void update();
	virtual void render();

	void addEnemyX(int value) { x += value; }
	void addEnemyY(int value) { y += value; }
	void addEnemyHP(int value) { HP += value; }
	void setAliveFalse() { alive = false; }
	void setFrameCountZero() { frameCount = 0; }

	RECT getEnemyRect() { return _hitArea; }	//적의 RECT를 반환한다.
	int getEnemyHP() { return HP; }
	bool getEnemyDie() { return die; };
	bool getEnemyAlive() { return alive; }

	enemy();
	virtual ~enemy();
};

class alien : public enemy		//일반 몬스터 (해파리)
{
public:
	virtual HRESULT init(int tileNum, tileMap* _tileMap, attackManager* ATM);
	virtual void release();
	virtual void update();
	virtual void render();

	alien();
	virtual ~alien();
};

class ghost : public enemy		//일반 몬스터 (유령)
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
	RECT _detectArea;	//감지를 위한 Rect영역
	int status;			//멈춤 , 하강 , 상승 상태 변경을 위한 변수
	int currentCollisionTile;	//현재 충돌중인 타일을 확인할 변수
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
	int status;					//멈춤 , 하강 , 상승 상태 변경을 위한 변수
	int currentCollisionTile;	//현재 충돌중인 타일을 확인할 변수

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
	int currentCollisionTile;	//현재 충돌중인 타일을 확인할 변수
	float patternTime;			//패턴 조정을 위한 변수
	bool pattern;				//패턴 변경을 확인하기 위한 변수
	float updateTime;			//업데이트 시간 조절을 위한 변수
public:
	virtual HRESULT init(int tileNum, tileMap* _tileMap, attackManager* ATM);
	virtual void release();
	virtual void update();
	virtual void render();

	void initStatus();				//타일의 상태를 확인하고 어느방향으로 움직일지 결정합니다.
	void firstCollisionTileCheck();
	void collisionTileCheck();
	void rotateCubeMove();

	rotateCube();
	virtual ~rotateCube();
};

class eri : public enemy		//첫번째 보스 몬스터
{
private:
	float gravity;				//보스가 가지는 중력
	DIRECTION dir;				//방향
	ACTION status;				//상태를 표시할 용도
	RECT detectArea;			//플레이어가 공격 범위에 있는지 확인하기 위한 용도

	float finalActionTime;		//마지막 동작을 끝낸 시간을 기록한다. (패턴 사이에 텀을 두기 위해서)
	float hitTime;				//공격을 받을때 여러개를 한번에 받지 못하게 처리한다.
	bool invincible;			//무적 상태를 표시하는 변수

	int currentCollisionTile;	//현재 충돌중인 타일을 확인할 변수

	image* chargeAura;			//보스 전용 차지 이펙트
	int auraCount;				//오라 프레임을 넘기기 위한 전용 카운트
public:
	virtual HRESULT init(int tileNum, tileMap* _tileMap, attackManager* ATM);
	virtual void release();
	virtual void update();
	virtual void render();

	void frameUpdate();				//보스의 행동에 따라서 프레임 업데이트 속도를 다르게 합니다.
	void firstCollisionTileCheck();	//처음 모든타일과 충돌을 체크합니다.
	void collisionTileCheck();		//이후 주변 타일과 충돌을 체크합니다.
	void eriAI();					//보스몬스터 eri의 AI입니다.
	bool checkXAndMove(DIRECTION dir,int value);		//X좌표지점의 상태를 확인하고 이동시킴.

	void eriGravity();				// 보스용 이동 함수

	void testFunction();		//테스트용 함수입니다.


	eri();
	virtual ~eri();
};