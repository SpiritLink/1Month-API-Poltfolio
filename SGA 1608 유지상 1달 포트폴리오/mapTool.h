#pragma once
#include "gameNode.h"

enum CTRL
{
	CTRL_TERRAINDRAW, CTRL_OBJDRAW, CTRL_ERASER, CTRL_END
};

enum OBJECT
{
	OBJ_BLOCK1, OBJ_BLOCK2, OBJ_TANK1, OBJ_TANK2, OBJ_NONE
};

struct tagTile
{
	OBJECT obj;
	RECT rc;
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
	image* _whiteBackground;
	image* _sampleTile;
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
	void lineRender();

	OBJECT objSelect(int frameX, int frameY);

	void load(const char * fileName);
	void save(const char * fileName);

	mapTool();
	virtual ~mapTool();
};

