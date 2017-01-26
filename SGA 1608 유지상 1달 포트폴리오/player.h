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
	int frameCount;	// 사용자의 프레임 
	DIRECTION direction;
	int ATK;
	int STR;
	int DEF;
	int SPEED;
	float gravity;

	int keyStatus;		//AND , OR 연산을 통한 검출
	int playerStatus;	//AND , OR 연산을 통한 검출
	//->키보드에서 해당 값을 빼내야 할때 만약 keyStatus & LEFT 면 keyStatus - LEFT하도록 처리해야 할것 같다.
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void keyboardInput();	//키보드를 입력하면 비트연산하는 함수
	void playerMove();		//플레이어의 움직임

	void testFunction();		//테스트중인 값을 확인하기 위한 함수
	void playerStatusCheck();	//플레이어의 상태를 확인하고 상태를 저장하는 함수.

	int getPlayerX() { return x; }
	int getPlayerY() { return y; }
	void addPlayerX(int value) { x += value; }
	void addPlayerY(int value) { y += value; }

	void setTileMapMemoryAddress(tileMap* tm) { _tileMap = tm; }
	void firstCollisionTileCheck();
	void collisionTileCheck();

	void playerRender();
	player();
	virtual ~player();
};

