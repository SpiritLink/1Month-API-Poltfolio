#pragma once

#include "item.h"
#include "tileMap.h"

class objectManager : public gameNode
{
private:
	vector<item*> _vItem;				//아이템을 저장할 벡터
	vector<item*>::iterator _viItem;	//아이템을 찾을 이터레이터
	tileMap* _tileMap;					//타일맵 (좌표에 해당 아이템을 배치하기 위해 필요합니다)
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setTileMapMemoryAddress(tileMap* TM) { _tileMap = TM; }	//타일맵의 메모리 주소를 설정합니다.
	void setHeart(float x, float y);								//체력 회복아이템을 배치합니다.
	void setShuriken(float x, float y);								//수리검 아이템 배치
	void setSavebell(int tileNum);									//저장 장소 배치

	void addItemX(int value);										//모든 아이템의 X좌표 추가
	void addItemY(int value);										//모든 아이템의 Y좌표 추가

	vector<item*> getItemVector() { return _vItem; }				//아이템 벡터를 반환하는 함수

	objectManager();
	~objectManager();
};

