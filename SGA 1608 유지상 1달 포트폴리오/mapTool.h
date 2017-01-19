#pragma once
#include "gameNode.h"

enum CTRL
{
	CTRL_TERRAINDRAW, CTRL_OBJDRAW, CTRL_OBJERASER, CTRL_TERRAINERASER, CTRL_END
};

enum OBJECT
{
	OBJ_BLOCK1, OBJ_BLOCK2, OBJ_NONE
};

enum TERRAIN
{
	TR_CEMENT, TR_EARTH, TR_GRASS, TR_WATER, TR_NONE
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
	image* _whiteBackground;
	image* _sampleTile;

	RECT _moveRight;
	RECT _moveLeft;
	RECT _moveUp;
	RECT _moveDown;

	RECT _saveTown;
	RECT _saveField1;
	RECT _saveField2;
	RECT _saveBoss;

	RECT _loadTown;
	RECT _loadField1;
	RECT _loadField2;
	RECT _loadBoss;

	HWND _btnTerrainDraw;
	HWND _btnObjDraw;
	HWND _btnTerrainEraser;
	HWND _btnObjEraser;

	tagCurrentTile _currentTile;
	tagTile _tiles[TILEX * TILEY];
	tagSampleTile _sampleTiles[SAMPLETILEX * SAMPLETILEY];
	int _ctrlSelect;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void mouseClick();
	void setup();
	void lineRender();

	OBJECT objSelect(int frameX, int frameY);
	TERRAIN terrainSelect(int frameX, int frameY);
	void load(const char * fileName);
	void save(const char * fileName);

	mapTool();
	virtual ~mapTool();
};

