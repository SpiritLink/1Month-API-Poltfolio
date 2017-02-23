#pragma once

#include "gameNode.h"
#include "enemy.h"
#include "tileMap.h"
#include "attackManager.h"
#include "objectManager.h"

class enemyManager : public gameNode
{
private:
	vector<enemy*> _vEnemy;				//���ʹ̸� ������ ����
	vector<enemy*>::iterator _viEnemy;	//���ʹ̸� ã�� ���ͷ�����
	tileMap* _tileMap;					//���ʹ��� ��ǥ �浹ó���� ���� Ÿ�ϸ�
	attackManager* _attackManager;		//���ʹ��� ������ ���� ���øŴ���
	objectManager* _objectManager;		//���ʹ̰� ������ ������ ������ ���� ������Ʈ �Ŵ���
public:
	virtual HRESULT init(tileMap* _tileMap, attackManager* _ATM, objectManager* _OBJ);
	virtual void release();
	virtual void update();
	virtual void render();

	void setAlien(int tileNum);		//Alien ��ġ
	void setGhost(int tileNum);		//Ghost ��ġ
	void setMiniGhost(int tileNum);	//miniGhost ��ġ
	void setFlower(int tileNum);	//Flower ��ġ
	void setOko(int tileNum);		//Oko ��ġ
	void setBomb(int tileNum);		//Bomb ��ġ
	void setRotateCube(int tileNum);//RotateCube ��ġ
	void setEri(int tileNum);		//Eri (����) ��ġ

	void addEnemyX(int value);		//��� ���� X��ǥ�� �Ķ���͸�ŭ �߰�
	void addEnemyY(int value);		//���� ���� Y��ǥ�� �Ķ���͸�ŭ �߰�

	vector<enemy*> getEnemyVector() { return _vEnemy; }	//���� ��� ���͸� ��ȯ�Ѵ�.

	enemyManager();
	virtual ~enemyManager();
};

