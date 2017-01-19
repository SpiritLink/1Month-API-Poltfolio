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
	if (SendMessage(_btnTerrainDraw, BM_GETCHECK, BST_CHECKED, 0)) _ctrlSelect = CTRL_TERRAINDRAW;
	if (SendMessage(_btnObjDraw, BM_GETCHECK, BST_CHECKED, 0)) _ctrlSelect = CTRL_OBJDRAW;
	if (SendMessage(_btnObjEraser, BM_GETCHECK, BST_CHECKED, 0)) _ctrlSelect = CTRL_OBJERASER;
	if (SendMessage(_btnTerrainEraser, BM_GETCHECK, BST_CHECKED, 0)) _ctrlSelect = CTRL_TERRAINERASER;
	mouseClick();
}

void mapTool::render()
{
	_whiteBackground->render(getMemDC());
	_sampleTile->render(getMemDC(), WINSIZEX - _sampleTile->getWidth(), 0);
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		if (!(_tiles[i].rc.left >= 50 && _tiles[i].rc.right <= 800 && _tiles[i].rc.top >= 50 && _tiles[i].rc.bottom <= 800)) continue;
		IMAGEMANAGER->frameRender("tileMap", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top,
			_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
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
	Rectangle(getMemDC(), _moveRight.left, _moveRight.top, _moveRight.right, _moveRight.bottom);
	Rectangle(getMemDC(), _moveLeft.left, _moveLeft.top, _moveLeft.right, _moveLeft.bottom);
	Rectangle(getMemDC(), _moveUp.left, _moveUp.top, _moveUp.right, _moveUp.bottom);
	Rectangle(getMemDC(), _moveDown.left, _moveDown.top, _moveDown.right, _moveDown.bottom);

	Rectangle(getMemDC(), _saveTown.left, _saveTown.top, _saveTown.right, _saveTown.bottom);
	Rectangle(getMemDC(), _saveField1.left, _saveField1.top, _saveField1.right, _saveField1.bottom);
	Rectangle(getMemDC(), _saveField2.left, _saveField2.top, _saveField2.right, _saveField2.bottom);
	Rectangle(getMemDC(), _saveBoss.left, _saveBoss.top, _saveBoss.right, _saveBoss.bottom);

	Rectangle(getMemDC(), _loadTown.left, _loadTown.top, _loadTown.right, _loadTown.bottom);
	Rectangle(getMemDC(), _loadField1.left, _loadField1.top, _loadField1.right, _loadField1.bottom);
	Rectangle(getMemDC(), _loadField2.left, _loadField2.top, _loadField2.right, _loadField2.bottom);
	Rectangle(getMemDC(), _loadBoss.left, _loadBoss.top, _loadBoss.right, _loadBoss.bottom);

	lineRender();
}

void mapTool::mouseClick()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&_saveTown, _ptMouse)) save("DATA/MAP/Town.map");
		if (PtInRect(&_saveField1, _ptMouse)) save("DATA/MAP/Field1.map");
		if (PtInRect(&_saveField2, _ptMouse)) save("DATA/MAP/Field2.map");
		if (PtInRect(&_saveBoss, _ptMouse)) save("DATA/MAP/Boss.map");

		if (PtInRect(&_loadTown, _ptMouse)) load("DATA/MAP/Town.map");
		if (PtInRect(&_loadField1, _ptMouse)) load("DATA/MAP/Field1.map");
		if (PtInRect(&_loadField2, _ptMouse)) load("DATA/MAP/Field2.map");
		if (PtInRect(&_loadBoss, _ptMouse)) load("DATA/MAP/Boss.map");

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
		if (_ptMouse.x >= 50 && _ptMouse.x <= 800 && _ptMouse.y >= 50 && _ptMouse.y <= 800)
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
					case CTRL_OBJERASER:
						_tiles[i].objFrameX = 0;
						_tiles[i].objFrameY = 4;
						_tiles[i].obj = OBJ_NONE;
						break;
					case CTRL_TERRAINERASER:
						_tiles[i].terrainFrameX = 0;
						_tiles[i].terrainFrameY = 4;
						_tiles[i].terrain = TR_NONE;
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
	_btnTerrainDraw = CreateWindow("button", "배경설치", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
		1100, 380, 100, 30, _hWnd, HMENU(0), _hInstance, NULL);

	_btnObjDraw = CreateWindow("button", "물체설치", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
		1100, 410, 100, 30, _hWnd, HMENU(1), _hInstance, NULL);

	_btnObjEraser = CreateWindow("button", "물체삭제", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
		1100, 470, 100, 30, _hWnd, HMENU(2), _hInstance, NULL);

	_btnTerrainEraser = CreateWindow("button", "배경삭제", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
		1100, 440, 100, 30, _hWnd, HMENU(3), _hInstance, NULL);

	_moveLeft = RectMake(0, WINSIZEY / 2 - 50, 50, 50);
	_moveRight = RectMake(800, WINSIZEY / 2 - 50, 50, 50);
	_moveUp = RectMake(400, 0, 50, 50);
	_moveDown = RectMake(400, 800, 50, 50);

	_saveTown = RectMake(WINSIZEX - 200, 600, 50, 50);
	_saveField1 = RectMake(WINSIZEX - 150, 600, 50, 50);
	_saveField2 = RectMake(WINSIZEX - 100, 600, 50, 50);
	_saveBoss = RectMake(WINSIZEX - 50, 600, 50, 50);

	_loadTown = RectMake(WINSIZEX - 200, 650, 50, 50);
	_loadField1 = RectMake(WINSIZEX - 150, 650, 50, 50);
	_loadField2 = RectMake(WINSIZEX - 100, 650, 50, 50);
	_loadBoss = RectMake(WINSIZEX - 50, 650, 50, 50);
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
	return OBJ_BLOCK1;
}

TERRAIN mapTool::terrainSelect(int frameX, int frameY)
{
	return TERRAIN();
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
