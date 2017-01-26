#pragma once

#include "gameNode.h"
#include "tileMap.h"

#define DEFAULT_STR 1
#define DEFAULT_DEF 1
#define DEFAULT_SPEED 5
class player : public gameNode
{
private:
	tileMap* _tileMap;
	image* playerIMG;

	float x;
	float y;
	RECT PlayerRect;
	
	int currentCollisionTile;
	int frameCount;	// ������� ������ 
	DIRECTION direction;
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

	void keyboardInput();	//Ű���带 �Է��ϸ� ��Ʈ�����ϴ� �Լ�
	void playerMove();		//�÷��̾��� ������

	void testFunction();		//�׽�Ʈ���� ���� Ȯ���ϱ� ���� �Լ�

	int getPlayerX() { return x; }
	int getPlayerY() { return y; }
	void addPlayerX(int value) { x += value; }
	void addPlayerY(int value) { y += value; }

	void setTileMapMemoryAddress(tileMap* tm) { _tileMap = tm; }
	void firstCollisionTileCheck();
	void collisionTileCheck();
	player();
	virtual ~player();
};

