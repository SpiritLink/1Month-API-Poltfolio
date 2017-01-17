#include "stdafx.h"
#include "mapTool.h"


mapTool::mapTool()
{
}


mapTool::~mapTool()
{
}

HRESULT mapTool::init()
{
	IMAGEMANAGER->addFrameImage("tileMap", "IMAGE/tile/tile.bmp", 0, 0, 432, 528, SAMPLETILEX, SAMPLETILEY, true, RGB(0, 0, 0));

	setup();

	_ctrlSelect = CTRL_TERRAINDRAW;
	SendMessage(_btnTerrainDraw, BM_SETCHECK, BST_CHECKED, 0);

	return S_OK;
}

void mapTool::release()
{
}

void mapTool::update()
{
	if (SendMessage(_btnTerrainDraw, BM_GETCHECK, BST_CHECKED, 0))
	{
		_ctrlSelect = CTRL_TERRAINDRAW;
	}
	else if (SendMessage(_btnObjDraw, BM_GETCHECK, BST_CHECKED, 0))
	{
		_ctrlSelect = CTRL_OBJDRAW;
	}
	else if (SendMessage(_btnEraser, BM_GETCHECK, BST_CHECKED, 0))
	{
		_ctrlSelect = CTRL_ERASER;
	}

	if (SendMessage(_btnSave, BM_GETSTATE, BST_PUSHED, 0))
	{
		SendMessage(_btnTerrainDraw, BM_SETCHECK, BST_UNCHECKED, 0);
		SendMessage(_btnObjDraw, BM_SETCHECK, BST_UNCHECKED, 0);
		SendMessage(_btnEraser, BM_SETCHECK, BST_UNCHECKED, 0);
		_ctrlSelect = CTRL_END;
		save();
	}
	if (SendMessage(_btnLoad, BM_GETSTATE, BST_PUSHED, 0))
	{
		SendMessage(_btnTerrainDraw, BM_SETCHECK, BST_UNCHECKED, 0);
		SendMessage(_btnObjDraw, BM_SETCHECK, BST_UNCHECKED, 0);
		SendMessage(_btnEraser, BM_SETCHECK, BST_UNCHECKED, 0);
		_ctrlSelect = CTRL_END;
		load();
	}

	setMap();
}

void mapTool::render()
{
	IMAGEMANAGER->render("tileMap", getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("tileMap")->getWidth(), 0);

	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		IMAGEMANAGER->frameRender("tileMap", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top,
			_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
	}

	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		IMAGEMANAGER->frameRender("tileMap", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top,
			_tiles[i].objFrameX, _tiles[i].objFrameY);
	}
}

void mapTool::setMap()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; ++i)
		{
			if (PtInRect(&_sampleTiles[i].rc, _ptMouse))
			{
				_currentTile.x = _sampleTiles[i].terrainFrameX;
				_currentTile.y = _sampleTiles[i].terrainFrameY;
				break;
			}
		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < TILEX * TILEY; ++i)
		{
			if (PtInRect(&_tiles[i].rc, _ptMouse))
			{
				switch (_ctrlSelect)
				{
				case CTRL_TERRAINDRAW:
					_tiles[i].terrainFrameX = _currentTile.x;
					_tiles[i].terrainFrameY = _currentTile.y;
					_tiles[i].terrain = terrainSelect(_currentTile.x, _currentTile.y);
					break;
				case CTRL_OBJDRAW:
					_tiles[i].objFrameX = _currentTile.x;
					_tiles[i].objFrameY = _currentTile.y;
					_tiles[i].obj = objSelect(_currentTile.x, _currentTile.y);
					break;
				case CTRL_ERASER:
					_tiles[i].objFrameX = 0;
					_tiles[i].objFrameY = 0;
					_tiles[i].obj = OBJ_NONE;
					break;
				}
				break;
			}
		}
	}
}

void mapTool::setup()
{
	_btnSave = CreateWindow("button", "save", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		700, 500, 100, 30, _hWnd, HMENU(0), _hInstance, NULL);

	_btnLoad = CreateWindow("button", "load", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		800, 500, 100, 30, _hWnd, HMENU(1), _hInstance, NULL);

	_btnTerrainDraw = CreateWindow("button", "terrainDraw", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
		700, 350, 140, 30, _hWnd, HMENU(2), _hInstance, NULL);

	_btnObjDraw = CreateWindow("button", "objDraw", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
		700, 380, 140, 30, _hWnd, HMENU(3), _hInstance, NULL);

	_btnEraser = CreateWindow("button", "지우개", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
		700, 410, 140, 30, _hWnd, HMENU(4), _hInstance, NULL);

	//오른쪽 샘플타일의 렉트 설정한다
	for (int i = 0; i < SAMPLETILEY; ++i)
	{
		for (int j = 0; j < SAMPLETILEX; ++j)
		{
			_sampleTiles[i*SAMPLETILEX + j].terrainFrameX = j;
			_sampleTiles[i*SAMPLETILEX + j].terrainFrameY = i;
			SetRect(&_sampleTiles[i*SAMPLETILEX + j].rc,
				(WINSIZEX - IMAGEMANAGER->findImage("tileMap")->getWidth()) + j * TILESIZE, i*TILESIZE,
				(WINSIZEX - IMAGEMANAGER->findImage("tileMap")->getWidth()) + j * TILESIZE + TILESIZE,
				i*TILESIZE + TILESIZE);
		}
	}

	//왼쪽 타일의 렉트 설정한다.
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			SetRect(&_tiles[i * TILEX + j].rc,
				j*TILESIZE,
				i*TILESIZE,
				j*TILESIZE + TILESIZE,
				i*TILESIZE + TILESIZE);
		}
	}
	
	//기본적으로 바닥을 특정한 거로 전부 깐다
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		_tiles[i].terrainFrameX = 0;
		_tiles[i].terrainFrameY = 0;
		_tiles[i].terrain = terrainSelect(_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
		_tiles[i].objFrameX = 0;
		_tiles[i].objFrameY = 0;
		_tiles[i].obj = OBJ_NONE;
	}
		

}

TERRAIN mapTool::terrainSelect(int frameX, int frameY)
{
	if (frameX == 1 && frameY == 0) return TR_CEMENT;
	if (frameX == 2 && frameY == 0) return TR_EARTH;
	if (frameX == 3 && frameY == 0) return TR_GRASS;
	if (frameX == 4 && frameY == 0) return TR_WATER;
	return TR_GRASS;
}

OBJECT mapTool::objSelect(int frameX, int frameY)
{
	if (frameX == 0 && frameY == 1) return OBJ_BLOCK1;
	if (frameX == 0 && frameY == 2) return OBJ_BLOCK2;
	if (frameX == 0 && frameY == 0) return OBJ_TANK1;
	if (frameX == 0 && frameY == 8) return OBJ_TANK2;
	return OBJ_BLOCK1;
}

void mapTool::load()
{
}

void mapTool::save()
{
}
