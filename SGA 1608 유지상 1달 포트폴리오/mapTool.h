#pragma once
#include "gameNode.h"

#define SAMPLETILEX 27
#define SAMPLETILEY 33

#define TILESIZE 16
#define TILEX 20
#define TILEY 20
#define TILESIZEX (TILESIZE * TILEX)
#define TILESIZEY (TILESIZE * TILEY)

enum CTRL
{
	CTRL_TERRAINDRAW, CTRL_OBJDRAW, CTRL_ERASER, CTRL_END
};

enum OBJECT
{
	OBJ_BLOCK1, OBJ_BLOCK2, OBJ_TANK1, OBJ_TANK2, OBJ_NONE
};

enum TERRAIN
{
	TR_CEMENT, TR_EARTH, TR_GRASS, TR_WATER, TR_END
};

struct tagTile
{
	TERRAIN terrain;
	OBJECT obj;
	RECT rc;
	int terrainFrameX;
	int terrainFrameY;
	int objFrameX;
	int objFrameY;
};

struct tagSampleTile
{
	RECT rc;
	int terrainFrameX;
	int terrainFrameY;
};

struct tagCurrentTile
{
	int x;
	int y;
};

class mapTool : public gameNode
{
private:
	HWND _btnSave;
	HWND _btnLoad;
	HWND _btnTerrainDraw;
	HWND _btnObjDraw;
	HWND _btnEraser;

	tagCurrentTile _currentTile;
	tagTile _tiles[TILEX * TILEY];
	tagSampleTile _sampleTiles[SAMPLETILEX * SAMPLETILEY];
	int _ctrlSelect;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setMap();
	void setup();

	TERRAIN terrainSelect(int frameX ,int frameY);
	OBJECT objSelect(int frameX, int frameY);

	void load();
	void save();

	mapTool();
	virtual ~mapTool();
};

