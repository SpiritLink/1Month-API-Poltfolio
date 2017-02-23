#pragma once

#include "gameNode.h"
#include "tileMap.h"
#include "attackManager.h"


#define DEFAULT_SPEED 6
#define IMAGESIZEX 816
#define IMAGESIZEY 704
#define PLAYERAREAX 20
#define PLAYERAREAY	30
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
	float saveTime;					//���̺긦 ���ѽ�Ű�� ���� ����


	RECT PlayerRect;
	DIRECTION direction;			//������ Ȯ���ϴ� ����
	bool attackType;				//������ ������ �ٲ��ִ� ����

	int currentCollisionTile;
	int frameCount;	// ������� ������ 
	int HP;			//���� ü��
	int MAXHP;		//�ִ� ü��
	int MP;
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

	void addPlayerX(int value) { x += value; }
	void addPlayerY(int value) { y += value; }
	void addPlayerHP(int value) { HP += value; }
	void addPlayerMP(int value) { MP += value; }

	int getPlayerX() { return x; }
	int getPlayerY() { return y; }
	int getCollisionTile() { return currentCollisionTile; }
	RECT getPlayerRect() { return PlayerRect;}

	void setTileMapMemoryAddress(tileMap* tm) { _tileMap = tm; }
	void setAttackManagerMemoryAddress(attackManager* ATM) { _attackManager = ATM; }
	void setPlayerTilePosition(int timeNum);	//�÷��̾ Ÿ�� ��ȣ�� ������.
	void setPlayerHit(float countTime);
	player();
	virtual ~player();
};

