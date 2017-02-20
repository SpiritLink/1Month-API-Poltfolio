#pragma once

#include "item.h"

class objectManager : public gameNode
{
private:
	vector<item*> _vItem;
	vector<item*>::iterator _viItem;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setHeart(float x, float y);
	void setShuriken(float x, float y);

	void addItemX(int value);
	void addItemY(int value);

	vector<item*> getItemVector() { return _vItem; }
	objectManager();
	~objectManager();
};

