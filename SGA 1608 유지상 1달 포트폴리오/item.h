#pragma once

#include "gameNode.h"

class item : public gameNode
{
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	item();
	~item();
};

