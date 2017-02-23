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

	//충돌처리용 이미지 로드
	IMAGEMANAGER->addFrameImage("tilePIXEL", "IMAGE/tile/TilePIXEL.bmp", 0, 0, 1350, 1200, SAMPLETILEX, SAMPLETILEY, false, RGB(0, 0, 0));

	//미니맵 이미지 세팅
	_miniMapIMG = IMAGEMANAGER->addFrameImage("miniMap", "IMAGE/tile/tile.bmp", SAMPLETILEX * 2, SAMPLETILEY * 2, SAMPLETILEX, SAMPLETILEY, true, RGB(0, 0, 0));
	_miniRedTile = IMAGEMANAGER->addImage("miniRedTile", "IMAGE/tile/redTile.bmp", 2, 2, false, RGB(0, 0, 0));

	//배경 이미지 세팅
	_BgSky = IMAGEMANAGER->addImage("BG_Sky", "IMAGE/background/bg_sky.bmp", 800, 600, false, RGB(0, 0, 0));
	_BgMt1 = IMAGEMANAGER->addImage("BG_Mt1", "IMAGE/background/bg_mountain1.bmp", 800, 600, true, RGB(120, 175, 237));
	_BgMt2 = IMAGEMANAGER->addImage("BG_Mt2", "IMAGE/background/bg_mountain2.bmp", 800, 600, true, RGB(120, 175, 237));
	_BgMt3 = IMAGEMANAGER->addImage("BG_Mt3", "IMAGE/background/bg_mountain3.bmp", 800, 600, true, RGB(120, 175, 237));
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

	playerYTileNumber = 0;
	valueX = 0;
	valueY = 0;
	skyX = 0;
	correctionY = 0;

	beforePlayerYTileNumber = 0;
	return S_OK;
}

void tileMap::release()
{
}

void tileMap::update()
{
	//플레이어의 Y좌표에 따라서 배경의 Y좌표를 변경합니다.
	playerYTileNumber = TILEY - (DATABASE->getCollisionTile() / TILEX);

	//배경의 떨림현상을 제거하기 위한 처리입니다. (2이상 차이가 나야 값이 변경됨)
	if (abs(playerYTileNumber - beforePlayerYTileNumber) >= 2) 		beforePlayerYTileNumber = playerYTileNumber;

	//플레이어의 Y타일 번호를 배경의 크기에 맞게 변환합니다 (240퍼센트)
	valueY = beforePlayerYTileNumber * 2.4f;

	//X좌표는 카메라의 움직임에 따라 변화된 변수를 이용합니다.
	valueX = DATABASE->getbackgroundCount();

	//카메라만 움직였을때를 위한 Y좌표 보정입니다.
	correctionY = (DATABASE->getPlayerY() / TILESIZE) * 2.4f;

	//하늘은 움직임 여부에 상관없이 일정량 계속 좌측으로 움직입니다.
	++skyX;

	_Ground = RectMake(0, valueY + correctionY, WINSIZEX, WINSIZEY);	//땅 영역
	_Sky = RectMake(0, valueY - 600 + correctionY, WINSIZEX, WINSIZEY);	//하늘 영역
}

void tileMap::render()
{
	//배경 렌더 상단영역
	_BgSky->loopRender(getMemDC(), &_Sky, skyX, 0);
	//배경 렌더 하단영역
	_BgSky->loopRender(getMemDC(), &_Ground, skyX, 0);
	_BgMt3->loopRender(getMemDC(), &_Ground, -(valueX / 6), 0);
	_BgMt2->loopRender(getMemDC(), &_Ground, -(valueX / 3), 0);
	_BgMt1->loopRender(getMemDC(), &_Ground, valueX / 3, 0);

	//타일맵 렌더
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		if (!(	_tiles[i].rc.left >= -TILESIZE && _tiles[i].rc.right <= WINSIZEX + TILESIZE && 
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
