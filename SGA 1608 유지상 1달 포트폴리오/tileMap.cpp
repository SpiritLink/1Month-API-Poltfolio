#include "stdafx.h"
#include "tileMap.h"

HRESULT tileMap::init(const char* fileName)
{
	//파일에서 맵 데이터를 불러옴
	HANDLE file;
	DWORD read;
	file = CreateFile(fileName, GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
	CloseHandle(file);
	
	//미니맵 이미지 세팅
	_miniMapIMG = IMAGEMANAGER->addFrameImage("miniMap", "IMAGE/tile/tile.bmp", SAMPLETILEX * 2, SAMPLETILEY * 2, SAMPLETILEX, SAMPLETILEY, true, RGB(0, 0, 0));
	_miniRedTile = IMAGEMANAGER->addImage("miniRedTile", "IMAGE/tile/redTile.bmp", 2, 2, false, RGB(0, 0, 0));
	//Rect 셋팅
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

	return S_OK;
}

void tileMap::release()
{
}

void tileMap::update()
{
}

void tileMap::render()
{
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		if (!(_tiles[i].rc.left >= -TILESIZE && _tiles[i].rc.right <= WINSIZEX + TILESIZE && 
			_tiles[i].rc.top >= -TILESIZE && _tiles[i].rc.bottom <= WINSIZEY + TILESIZE)) continue;
		IMAGEMANAGER->frameRender("tileMap", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top,
			_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
		IMAGEMANAGER->frameRender("tileMap", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top,
			_tiles[i].objFrameX, _tiles[i].objFrameY);
	}
}

void tileMap::moveTileX(int value)
{
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		_tiles[i].rc.left += value;
		_tiles[i].rc.right += value;
	}
}

void tileMap::moveTileY(int value)
{
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		_tiles[i].rc.top += value;
		_tiles[i].rc.bottom += value;
	}
}

void tileMap::miniMapRender()
{
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		_miniMapIMG->frameRender(getMemDC(), (WINSIZEX / 2 )- 150 + ((i % TILEX)* 2), (WINSIZEY / 2) - 150 + ((i / TILEX) * 2), _tiles[i].objFrameX, _tiles[i].objFrameY);
		if (DATABASE->getCollisionTile() == i) _miniRedTile->render(getMemDC(), (WINSIZEX / 2) - 150 + ((i % TILEX) * 2), (WINSIZEY / 2) - 150 + ((i / TILEX) * 2));
	}
}

tileMap::tileMap()
{
}

tileMap::~tileMap()
{
}
