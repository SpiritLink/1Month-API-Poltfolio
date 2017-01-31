#pragma once

#include "gameNode.h"
#include "tileMap.h"

#define DEFAULT_SPEED 5
class player : public gameNode
{
private:
	tileMap* _tileMap;
	image* playerIMG;

	float x;
	float y;
	float currentTime;			//���� �ð��� �����ϴ� ����
	RECT PlayerRect;
	DIRECTION direction;		//������ Ȯ���ϴ� ����

	int currentCollisionTile;
	int frameCount;	// ������� ������ 
	int HP;
	int MP;
	int ATK;
	int SPEED;
	float gravity;

	int keyStatus;		//AND , OR ������ ���� ���� ���� Ű�Է� Ȯ���ϴ� ����
	int playerStatus;	//AND , OR ������ ���� ���� ���� ���¸� Ȯ���ϴ� ����
	int Action;			//AND , OR ������ ���� ���� ���� �ൿ�� Ȯ���ϴ� ����

	//->Ű���忡�� �ش� ���� ������ �Ҷ� ���� keyStatus & LEFT �� keyStatus - LEFT�ϵ��� ó���ؾ� �Ұ� ����.
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void keyboardInput();	//Ű���带 �Է��ϸ� ��Ʈ�����ϴ� �Լ�
	void playerMove();		//�÷��̾��� ������
	void playerAttack();	//�÷��̾��� ������ ó��

	void testFunction();		//�׽�Ʈ���� ���� Ȯ���ϱ� ���� �Լ�
	void playerStatusCheck();	//�÷��̾��� ���¸� Ȯ���ϰ� ���¸� �����ϴ� �Լ�.

	int getPlayerX() { return x; }
	int getPlayerY() { return y; }
	void addPlayerX(int value) { x += value; }
	void addPlayerY(int value) { y += value; }

	void setTileMapMemoryAddress(tileMap* tm) { _tileMap = tm; }
	void setPlayerTilePosition(int timeNum);	//�÷��̾ Ÿ�� ��ȣ�� ������.
	void firstCollisionTileCheck();
	void collisionTileCheck();

	void playerRender();
	player();
	virtual ~player();
};

