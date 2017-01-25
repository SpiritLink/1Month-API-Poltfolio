#pragma once

#include "gameNode.h"
#include "player.h"
#include "tileMap.h"
class testScene : public gameNode
{
private:
	tileMap* _tileMap;
	image* _image;
	player* _player;

	float cameraX;
	float cameraY;
	RECT Background;

	image* _test;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	
	void cameraMove();
	testScene();
	virtual ~testScene();
};

