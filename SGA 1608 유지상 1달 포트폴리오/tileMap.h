#pragma once
#include "gameNode.h"

class tileMap : public gameNode
{
private:
	tagTile _tiles[TILEX * TILEY];
public:
	virtual HRESULT init(const char* fileName);
	virtual void release();
	virtual void update();
	virtual void render();

	void moveTileX(int value);
	void moveTileY(int value);

	tagTile* getTiles() { return _tiles; }

	tileMap();
	virtual ~tileMap();
};