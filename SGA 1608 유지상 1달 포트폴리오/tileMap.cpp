#include "stdafx.h"
#include "tileMap.h"

HRESULT tileMap::init(const char* fileName)
{
	//���Ͽ��� �� �����͸� �ҷ���
	HANDLE file;
	DWORD read;
	file = CreateFile(fileName, GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
	CloseHandle(file);

	//�浹ó���� �̹��� �ε�
	IMAGEMANAGER->addFrameImage("tilePIXEL", "IMAGE/tile/TilePIXEL.bmp", 0, 0, 1350, 1200, SAMPLETILEX, SAMPLETILEY, false, RGB(0, 0, 0));

	//�̴ϸ� �̹��� ����
	_miniMapIMG = IMAGEMANAGER->addFrameImage("miniMap", "IMAGE/tile/tile.bmp", SAMPLETILEX * 2, SAMPLETILEY * 2, SAMPLETILEX, SAMPLETILEY, true, RGB(0, 0, 0));
	_miniRedTile = IMAGEMANAGER->addImage("miniRedTile", "IMAGE/tile/redTile.bmp", 2, 2, false, RGB(0, 0, 0));

	//��� �̹��� ����
	_BgSky = IMAGEMANAGER->addImage("BG_Sky", "IMAGE/background/bg_sky.bmp", 800, 600, false, RGB(0, 0, 0));
	_BgMt1 = IMAGEMANAGER->addImage("BG_Mt1", "IMAGE/background/bg_mountain1.bmp", 800, 600, true, RGB(120, 175, 237));
	_BgMt2 = IMAGEMANAGER->addImage("BG_Mt2", "IMAGE/background/bg_mountain2.bmp", 800, 600, true, RGB(120, 175, 237));
	_BgMt3 = IMAGEMANAGER->addImage("BG_Mt3", "IMAGE/background/bg_mountain3.bmp", 800, 600, true, RGB(120, 175, 237));
	//Rect ����
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
	//�÷��̾��� Y��ǥ�� ���� ����� Y��ǥ�� �����մϴ�.
	playerYTileNumber = TILEY - (DATABASE->getCollisionTile() / TILEX);

	//����� ���������� �����ϱ� ���� ó���Դϴ�. (2�̻� ���̰� ���� ���� �����)
	if (abs(playerYTileNumber - beforePlayerYTileNumber) >= 2) 		beforePlayerYTileNumber = playerYTileNumber;

	//�÷��̾��� YŸ�� ��ȣ�� ����� ũ�⿡ �°� ��ȯ�մϴ� (240�ۼ�Ʈ)
	valueY = beforePlayerYTileNumber * 2.4f;

	//X��ǥ�� ī�޶��� �����ӿ� ���� ��ȭ�� ������ �̿��մϴ�.
	valueX = DATABASE->getbackgroundCount();

	//ī�޶� ������������ ���� Y��ǥ �����Դϴ�.
	correctionY = (DATABASE->getPlayerY() / TILESIZE) * 2.4f;

	//�ϴ��� ������ ���ο� ������� ������ ��� �������� �����Դϴ�.
	++skyX;

	_Ground = RectMake(0, valueY + correctionY, WINSIZEX, WINSIZEY);	//�� ����
	_Sky = RectMake(0, valueY - 600 + correctionY, WINSIZEX, WINSIZEY);	//�ϴ� ����
}

void tileMap::render()
{
	//��� ���� ��ܿ���
	_BgSky->loopRender(getMemDC(), &_Sky, skyX, 0);
	//��� ���� �ϴܿ���
	_BgSky->loopRender(getMemDC(), &_Ground, skyX, 0);
	_BgMt3->loopRender(getMemDC(), &_Ground, -(valueX / 6), 0);
	_BgMt2->loopRender(getMemDC(), &_Ground, -(valueX / 3), 0);
	_BgMt1->loopRender(getMemDC(), &_Ground, valueX / 3, 0);

	//Ÿ�ϸ� ����
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
