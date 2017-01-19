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
	IMAGEMANAGER->addFrameImage("tileMap", "IMAGE/tile/tile.bmp", 0, 0, 1350, 1200, SAMPLETILEX, SAMPLETILEY, true, RGB(0, 0, 0));
	_sampleTile = IMAGEMANAGER->addImage("sampleTile", "IMAGE/tile/tile.bmp", 0, 0, 540, 480, true, RGB(0, 0, 0));
	_whiteBackground = IMAGEMANAGER->addImage("whiteSpace", "IMAGE/background/WhiteSpace.bmp", 1600, 900, false, RGB(0, 0, 0));
	setup();

	_ctrlSelect = CTRL_TERRAINDRAW;
	SendMessage(_btnObjDraw, BM_SETCHECK, BST_CHECKED, 0);

	return S_OK;
}

void mapTool::release()
{
}

void mapTool::update()
{
	if (SendMessage(_btnObjDraw, BM_GETCHECK, BST_CHECKED, 0)) _ctrlSelect = CTRL_OBJDRAW;;
	if (SendMessage(_btnEraser, BM_GETCHECK, BST_CHECKED, 0)) _ctrlSelect = CTRL_ERASER;

	setMap();
}

void mapTool::render()
{
	_whiteBackground->render(getMemDC());
	_sampleTile->render(getMemDC(), WINSIZEX - _sampleTile->getWidth(), 0);

	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		IMAGEMANAGER->frameRender("tileMap", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top,
			_tiles[i].objFrameX, _tiles[i].objFrameY);
	}

	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		//Rectangle(getMemDC(),_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].rc.right, _tiles[i].rc.bottom);
	}

	for (int i = 0; i < SAMPLETILEY * SAMPLETILEX; ++i)
	{
		//Rectangle(getMemDC(), _sampleTiles[i].rc.left, _sampleTiles[i].rc.top, _sampleTiles[i].rc.right, _sampleTiles[i].rc.bottom);
	}

	lineRender();
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
		if (_ptMouse.x >= 50 && _ptMouse.x <= 800)
		{
			for (int i = 0; i < TILEX * TILEY; ++i)
			{
				if (PtInRect(&_tiles[i].rc, _ptMouse))
				{
					switch (_ctrlSelect)
					{
					case CTRL_OBJDRAW:
						_tiles[i].objFrameX = _currentTile.x;
						_tiles[i].objFrameY = _currentTile.y;
						_tiles[i].obj = objSelect(_currentTile.x, _currentTile.y);
						break;
					case CTRL_ERASER:
						_tiles[i].objFrameX = 0;
						_tiles[i].objFrameY = 4;
						_tiles[i].obj = OBJ_NONE;
						break;
					}
					break;
				}
			}
		}
	}
}

void mapTool::setup()
{

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
				(WINSIZEX - IMAGEMANAGER->findImage("sampleTile")->getWidth()) + j * SAMPLETILESIZE, i*SAMPLETILESIZE,
				(WINSIZEX - IMAGEMANAGER->findImage("sampleTile")->getWidth()) + j * SAMPLETILESIZE + SAMPLETILESIZE,
				i*SAMPLETILESIZE + SAMPLETILESIZE);
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
		_tiles[i].objFrameX = 0;
		_tiles[i].objFrameY = 4;
		_tiles[i].obj = OBJ_NONE;
	}
		

}

void mapTool::lineRender()
{
	MoveToEx(getMemDC(), 50, 50, NULL);
	LineTo(getMemDC(), 50, 15 * TILESIZE + 50);
	MoveToEx(getMemDC(), 50, 50, NULL);
	LineTo(getMemDC(), 15 * TILESIZE + 50, 50);

	MoveToEx(getMemDC(), 15 * TILESIZE + 50, 50, NULL);
	LineTo(getMemDC(), 15 * TILESIZE + 50, 15 * TILESIZE + 50);
	MoveToEx(getMemDC(), 50, TILESIZE * 15 + 50, NULL);
	LineTo(getMemDC(), 15 * TILESIZE + 50, 15 * TILESIZE + 50);
}

OBJECT mapTool::objSelect(int frameX, int frameY)
{
	if (frameX == 0 && frameY == 1) return OBJ_BLOCK1;
	if (frameX == 0 && frameY == 2) return OBJ_BLOCK2;
	if (frameX == 0 && frameY == 0) return OBJ_TANK1;
	if (frameX == 0 && frameY == 8) return OBJ_TANK2;
	return OBJ_BLOCK1;
}

void mapTool::load(const char * fileName)
{
	HANDLE file;
	DWORD read;
	file = CreateFile(fileName, GENERIC_READ,0,NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
	CloseHandle(file);
}

void mapTool::save(const char * fileName)
{
	HANDLE file;
	DWORD write;
	file = CreateFile(fileName, GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &write, NULL);
	CloseHandle(file);
}
