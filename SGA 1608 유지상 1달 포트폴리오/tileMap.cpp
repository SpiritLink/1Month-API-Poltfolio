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
		if (!(_tiles[i].rc.left >= -TILESIZE && _tiles[i].rc.right <= WINSIZEX + TILESIZE && _tiles[i].rc.top >= -TILESIZE && _tiles[i].rc.bottom <= WINSIZEY + TILESIZE)) continue;
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

tileMap::tileMap()
{
}

tileMap::~tileMap()
{
}
