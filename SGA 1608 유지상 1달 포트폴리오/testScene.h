#pragma once

#include "gameNode.h"
#include "player.h"

class testScene : public gameNode
{
private:
	tagTile _tiles[TILEX * TILEY];	//�׽�Ʈ ������ ������ Ÿ��
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
	void initTile();

	void tileRender();
	void moveTileX(int value);
	void moveTileY(int value);
	testScene();
	virtual ~testScene();
};

