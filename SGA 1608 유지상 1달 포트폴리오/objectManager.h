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

	objectManager();
	~objectManager();
};

