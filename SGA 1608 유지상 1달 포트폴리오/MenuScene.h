#pragma once

#include "gameNode.h"
class MenuScene : public gameNode
{
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	MenuScene();
	virtual ~MenuScene();
};

