#pragma once

#include "gameNode.h"
#include "tileMap.h"
#include "attackManager.h"


#define DEFAULT_SPEED 6
#define IMAGESIZEX 336
#define IMAGESIZEY 576
#define PLAYERAREAX 20
#define PLAYERAREAY	40
class player : public gameNode
{
private:
	tileMap* _tileMap;				//맵과의 충돌을 처리하기 위해서 필요
	attackManager* _attackManager;	//공격을 생성하기 위해서
	image* playerIMG;

	float x;
	float y;
	float currentTime;				//현재 시간을 저장하는 변수
	float invincibleTime;			//무적 시간을 저장하는 변수
	float countTime;
	RECT PlayerRect;
	DIRECTION direction;			//방향을 확인하는 변수
	bool attackType;				//공격의 종류를 바꿔주는 변수

	int currentCollisionTile;
	int frameCount;	// 사용자의 프레임 
	int HP;			//현재 체력
	int MAXHP;		//최대 체력
	int MP;
	int ATK;
	int SPEED;
	float gravity;

	int keyStatus;		//AND , OR 연산을 통한 검출 현재 키입력 확인하는 변수
	int playerStatus;	//AND , OR 연산을 통한 검출 현재 상태를 확인하는 변수
	int Action;			//AND , OR 연산을 통한 검출 현재 행동을 확인하는 변수

	//->키보드에서 해당 값을 빼내야 할때 만약 keyStatus & LEFT 면 keyStatus - LEFT하도록 처리해야 할것 같다.

	int alphaValue;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void keyboardInput();			//키보드를 입력하면 비트연산하는 함수
	void playerMove();				//플레이어의 움직임
	void playerAttack();			//플레이어의 공격을 처리
	void testPlayerMove();			//맵을 탐색하기 위한 테스트 함수

	void testFunction();			//테스트중인 값을 확인하기 위한 함수
	void playerStatusCheck();		//플레이어의 상태를 확인하고 상태를 저장하는 함수.
	void sendDataToSingleton();		//싱글톤으로 데이터를 전송하는 함수
	void firstCollisionTileCheck();	//맨처음 타일의 충돌을 확인하는 함수
	void collisionTileCheck();		//이후 타일의 충돌을 확인하는 함수 (확인하는 범위가 줄어듭니다.)

	void playerRender();			//상태에 따라서 플레이어를 렌더하는 함수

	int getPlayerX() { return x; }
	int getPlayerY() { return y; }
	void addPlayerX(int value) { x += value; }
	void addPlayerY(int value) { y += value; }
	int getCollisionTile() { return currentCollisionTile; }
	RECT getPlayerRect() { return PlayerRect;}

	void setTileMapMemoryAddress(tileMap* tm) { _tileMap = tm; }
	void setAttackManagerMemoryAddress(attackManager* ATM) { _attackManager = ATM; }
	void setPlayerTilePosition(int timeNum);	//플레이어를 타일 번호에 생성함.
	void setPlayerHit(float countTime);
	player();
	virtual ~player();
};

