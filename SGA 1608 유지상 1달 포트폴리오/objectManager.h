#pragma once

#include "item.h"
#include "tileMap.h"

class objectManager : public gameNode
{
private:
	vector<item*> _vItem;
	vector<item*>::iterator _viItem;
	tileMap* _tileMap;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setTileMapMemoryAddress(tileMap* TM) { _tileMap = TM; }
	void setHeart(float x, float y);
	void setShuriken(float x, float y);
	void setSavebell(int tileNum);

	void addItemX(int value);
	void addItemY(int value);

	vector<item*> getItemVector() { return _vItem; }
	objectManager();
	~objectManager();
};

