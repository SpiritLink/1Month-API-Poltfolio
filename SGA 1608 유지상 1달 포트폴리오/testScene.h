#pragma once

#include "gameNode.h"
#include "player.h"

struct object
{
	float x;
	float y;
	RECT rc;
};
class testScene : public gameNode
{
private:
	image* _image;
	player* _player;
	object rect[3];
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	
	testScene();
	virtual ~testScene();
};

