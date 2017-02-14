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
	tileMap* _tileMap;				//�ʰ��� �浹�� ó���ϱ� ���ؼ� �ʿ�
	attackManager* _attackManager;	//������ �����ϱ� ���ؼ�
	image* playerIMG;

	float x;
	float y;
	float currentTime;				//���� �ð��� �����ϴ� ����
	float invincibleTime;			//���� �ð��� �����ϴ� ����
	float countTime;
	RECT PlayerRect;
	DIRECTION direction;			//������ Ȯ���ϴ� ����
	bool attackType;				//������ ������ �ٲ��ִ� ����

	int currentCollisionTile;
	int frameCount;	// ������� ������ 
	int HP;			//���� ü��
	int MAXHP;		//�ִ� ü��
	int MP;
	int ATK;
	int SPEED;
	float gravity;

	int keyStatus;		//AND , OR ������ ���� ���� ���� Ű�Է� Ȯ���ϴ� ����
	int playerStatus;	//AND , OR ������ ���� ���� ���� ���¸� Ȯ���ϴ� ����
	int Action;			//AND , OR ������ ���� ���� ���� �ൿ�� Ȯ���ϴ� ����

	//->Ű���忡�� �ش� ���� ������ �Ҷ� ���� keyStatus & LEFT �� keyStatus - LEFT�ϵ��� ó���ؾ� �Ұ� ����.

	int alphaValue;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void keyboardInput();			//Ű���带 �Է��ϸ� ��Ʈ�����ϴ� �Լ�
	void playerMove();				//�÷��̾��� ������
	void playerAttack();			//�÷��̾��� ������ ó��
	void testPlayerMove();			//���� Ž���ϱ� ���� �׽�Ʈ �Լ�

	void testFunction();			//�׽�Ʈ���� ���� Ȯ���ϱ� ���� �Լ�
	void playerStatusCheck();		//�÷��̾��� ���¸� Ȯ���ϰ� ���¸� �����ϴ� �Լ�.
	void sendDataToSingleton();		//�̱������� �����͸� �����ϴ� �Լ�
	void firstCollisionTileCheck();	//��ó�� Ÿ���� �浹�� Ȯ���ϴ� �Լ�
	void collisionTileCheck();		//���� Ÿ���� �浹�� Ȯ���ϴ� �Լ� (Ȯ���ϴ� ������ �پ��ϴ�.)

	void playerRender();			//���¿� ���� �÷��̾ �����ϴ� �Լ�

	int getPlayerX() { return x; }
	int getPlayerY() { return y; }
	void addPlayerX(int value) { x += value; }
	void addPlayerY(int value) { y += value; }
	int getCollisionTile() { return currentCollisionTile; }
	RECT getPlayerRect() { return PlayerRect;}

	void setTileMapMemoryAddress(tileMap* tm) { _tileMap = tm; }
	void setAttackManagerMemoryAddress(attackManager* ATM) { _attackManager = ATM; }
	void setPlayerTilePosition(int timeNum);	//�÷��̾ Ÿ�� ��ȣ�� ������.
	void setPlayerHit(float countTime);
	player();
	virtual ~player();
};

