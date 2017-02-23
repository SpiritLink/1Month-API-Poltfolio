#pragma once

#include "gameNode.h"
#include "enemy.h"
#include "tileMap.h"
#include "attackManager.h"
#include "objectManager.h"

class enemyManager : public gameNode
{
private:
	vector<enemy*> _vEnemy;				//에너미를 저장할 벡터
	vector<enemy*>::iterator _viEnemy;	//에너미를 찾을 이터레이터
	tileMap* _tileMap;					//에너미의 좌표 충돌처리를 위한 타일맵
	attackManager* _attackManager;		//에너미의 공격을 위한 어택매니저
	objectManager* _objectManager;		//에너미가 죽을때 아이템 생성을 위한 오브젝트 매니저
public:
	virtual HRESULT init(tileMap* _tileMap, attackManager* _ATM, objectManager* _OBJ);
	virtual void release();
	virtual void update();
	virtual void render();

	void setAlien(int tileNum);		//Alien 배치
	void setGhost(int tileNum);		//Ghost 배치
	void setMiniGhost(int tileNum);	//miniGhost 배치
	void setFlower(int tileNum);	//Flower 배치
	void setOko(int tileNum);		//Oko 배치
	void setBomb(int tileNum);		//Bomb 배치
	void setRotateCube(int tileNum);//RotateCube 배치
	void setEri(int tileNum);		//Eri (보스) 배치

	void addEnemyX(int value);		//모든 적의 X좌표를 파라미터만큼 추가
	void addEnemyY(int value);		//모즉 적의 Y좌표를 파라미터만큼 추가

	vector<enemy*> getEnemyVector() { return _vEnemy; }	//적이 담긴 벡터를 반환한다.

	enemyManager();
	virtual ~enemyManager();
};

