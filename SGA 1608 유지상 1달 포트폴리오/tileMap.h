#pragma once
#include "gameNode.h"

class tileMap : public gameNode
{
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	tileMap();
	virtual ~tileMap();
};