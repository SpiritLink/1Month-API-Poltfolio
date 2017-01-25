#pragma once

#include "gameNode.h"
#include "player.h"
#include "tileMap.h"

class townScene : public gameNode
{
private:
	player* _player;
	tileMap* _tileMap;

	RECT Background;
	image* _backIMG;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void cameraMove();
	townScene();
	~townScene();
};

