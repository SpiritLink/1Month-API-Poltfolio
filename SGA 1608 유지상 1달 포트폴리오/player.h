#pragma once

#include "gameNode.h"

#define DEFAULT_STR 1
#define DEFAULT_DEF 1
#define DEFAULT_SPEED 10
class player : public gameNode
{
private:
	float x;
	float y;
	RECT PlayerRect;

	int ATK;
	int STR;
	int DEF;
	int SPEED;

	int keyStatus;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void keyboardInput();	//Ű���带 �Է��ϸ� ��Ʈ�����ϴ� �Լ�
	void playerMove();		//�÷��̾��� ������

	void testFunction();		//�׽�Ʈ���� ���� Ȯ���ϱ� ���� �Լ�

	float getPlayerX() { return x; }
	float getPlayerY() { return y; }
	void addPlayerX(float value) { x += value; }
	void addPlayerY(float value) { y += value; }
	player();
	virtual ~player();
};

