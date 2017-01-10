#pragma once

#include "gameNode.h"
#include "player.h"

class testScene : public gameNode
{
private:
	image* _image;
	player* _player;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	
	testScene();
	virtual ~testScene();
};

