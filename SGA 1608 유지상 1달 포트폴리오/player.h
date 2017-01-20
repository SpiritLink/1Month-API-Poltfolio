#pragma once

#include "gameNode.h"

#define DEFAULT_STR 1
#define DEFAULT_DEF 1
#define DEFAULT_SPEED 10
class player : public gameNode
{
private:
	int x;
	int y;
	RECT PlayerRect;

	int ATK;
	int STR;
	int DEF;
	int SPEED;
	float gravity;

	int keyStatus;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void keyboardInput();	//키보드를 입력하면 비트연산하는 함수
	void playerMove();		//플레이어의 움직임

	void testFunction();		//테스트중인 값을 확인하기 위한 함수

	int getPlayerX() { return x; }
	int getPlayerY() { return y; }
	void addPlayerX(int value) { x += value; }
	void addPlayerY(int value) { y += value; }
	player();
	virtual ~player();
};

