#include "stdafx.h"
#include "testScene.h"


HRESULT testScene::init()
{
	DATABASE->setBaseTime(TIMEMANAGER->getWorldTime());
	DATABASE->setDestCamX(WINSIZEX / 2);
	DATABASE->setDestCamY(WINSIZEY / 2);
	IMAGEMANAGER->addFrameImage("tileMap", "IMAGE/tile/tile.bmp", 0, 0, 1350, 1200, SAMPLETILEX, SAMPLETILEY, true, RGB(0, 0, 0));
	initTile();
	_image = IMAGEMANAGER->addImage("흰배경", "IMAGE/whiteBackground.bmp", WINSIZEX, WINSIZEY, false, RGB(0, 0, 0));
	_player = new player;
	_player->init();

	cameraX = 0;
	cameraY = 0;

	_test = IMAGEMANAGER->addImage("테스트배경", "IMAGE/test.bmp", 3840, 2160, false, RGB(0, 0, 0));
	Background = RectMake(0, 0, _test->getWidth(), _test->getHeight());
	return S_OK;
}

void testScene::release()
{
	_player->release();
	SAFE_DELETE(_player);
}

void testScene::update()
{
	_player->update();

	if (KEYMANAGER->isStayKeyDown('Q'))
	{
		DATABASE->setSourCamX(Background.left + WINSIZEX / 2);
		DATABASE->setSourCamY(Background.top + WINSIZEY / 2);
	}

	if (KEYMANAGER->isStayKeyDown('W'))
	{
		DATABASE->setSourCamX(Background.right - WINSIZEX / 2);
		DATABASE->setSourCamY(Background.bottom - WINSIZEY / 2);
	}

	if (KEYMANAGER->isStayKeyDown('E'))
	{
		DATABASE->setDestCamX(WINSIZEX / 2);
		DATABASE->setDestCamY(WINSIZEY / 2);
	}
	cameraMove();

}

void testScene::render()
{
	_image->render(getMemDC());
	Rectangle(getMemDC(), Background.left, Background.top, Background.right, Background.bottom);
	_test->render(getMemDC(), Background.left, Background.top);
	tileRender();
	_player->render();

	SetTextColor(getMemDC(), RGB(255, 255, 255));

	char strPosition1[128];
	char strPosition2[128];
	char strPosition3[128];

	sprintf(strPosition1, "%0.3f", getAngle(DATABASE->getDestCamX(), DATABASE->getDestCamY(), DATABASE->getSourCamX(), DATABASE->getSourCamY()));

	TextOut(getMemDC(), 200, 100, strPosition1, strlen(strPosition1));
}

void testScene::cameraMove()
{

		float angle = getAngle(DATABASE->getDestCamX(), DATABASE->getDestCamY(), DATABASE->getSourCamX(), DATABASE->getSourCamY());
		int distanceX = getDistance(DATABASE->getDestCamX(), 0, DATABASE->getSourCamX(), 0);
		int distanceY = getDistance(0, DATABASE->getDestCamY(), 0, DATABASE->getSourCamY());

		//화면이 벗어났을때 단순히 멈추는게 아니라 화면 조정을 해줘야 할것같다.
		if (Background.right < WINSIZEX)
		{
			int diffrence = WINSIZEX - Background.right;
			Background.right += diffrence;	//배경의 움직이는 정도를 조절
			Background.left += diffrence;	//배경의 움직이는 정도를 조정
			moveTileX(diffrence);			//타일의 움직이는 정도를 조정
			_player->addPlayerX(-diffrence);//플레이어의 움직이는 정도를 조절
		}
		if (Background.left > 0)
		{
			int diffrence = Background.left;
			Background.right -= diffrence;
			Background.left -= diffrence;
			_player->addPlayerX(+diffrence);
			moveTileX(-diffrence);
		}
		if (Background.top > 0)
		{
			int diffrence = Background.top;
			Background.top -= diffrence;
			Background.bottom -= diffrence;
			_player->addPlayerY(diffrence);
			moveTileY(-diffrence);
		}

		if (Background.bottom < WINSIZEY)
		{
			int diffrence = WINSIZEY - Background.bottom;
			Background.top += diffrence;
			Background.bottom += diffrence;
			_player->addPlayerY(-diffrence);
			moveTileY(diffrence);
		}
		//if (angle >= 0 && angle < 0.5f * PI)	if (Background.right  < WINSIZEX) return;
		//if (angle > 1.5f * PI && angle < 2.0f * PI)	if (Background.right  < WINSIZEX) return;
		//if (angle > 0.5f * PI && angle < 1.5f * PI)	if (Background.left > 0) return;	
		//if (angle > 0 && angle < PI) if (Background.top > 0) return;
		//if (angle > PI && angle < 2.0f * PI)	if (Background.bottom < WINSIZEY) return;


		//X좌표 이동
		if (DATABASE->getSourCamX() > DATABASE->getDestCamX())		//화면 오른쪽으로 움직일때
		{
			Background.left -= distanceX / 10;
			Background.right -= distanceX / 10;
			moveTileX(-distanceX / 10);
			_player->addPlayerX(-distanceX / 10);
		}

		if (DATABASE->getSourCamX() < DATABASE->getDestCamX())		//화면 왼쪽으로 움직일때
		{
			Background.left += distanceX / 10;
			Background.right += distanceX / 10;
			moveTileX(distanceX / 10);
			_player->addPlayerX(distanceX / 10);
		}

		//Y좌표 이동
		if (DATABASE->getSourCamY() > DATABASE->getDestCamY())		//화면 아래쪽으로 움직일때
		{
			Background.top -= distanceY / 10;
			Background.bottom -= distanceY / 10;
			moveTileY(-distanceY / 10);
			_player->addPlayerY(-distanceY / 10);
		}
		
		if (DATABASE->getSourCamY() < DATABASE->getDestCamY())		//화면 위쪽으로 움직일때
		{
			Background.top += distanceY / 10;
			Background.bottom += distanceY / 10;
			moveTileY(distanceY / 10);
			_player->addPlayerY(distanceY / 10);
		}
}

void testScene::initTile()
{
	HANDLE file;
	DWORD read;
	file = CreateFile("DATA/MAP/Town.map", GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
	CloseHandle(file);
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
}

void testScene::tileRender()
{
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		IMAGEMANAGER->frameRender("tileMap", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top,
			_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
		IMAGEMANAGER->frameRender("tileMap", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top,
			_tiles[i].objFrameX, _tiles[i].objFrameY);
	}
}

void testScene::moveTileX(int value)
{
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		_tiles[i].rc.left += value;
		_tiles[i].rc.right += value;
	}
}

void testScene::moveTileY(int value)
{
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		_tiles[i].rc.top += value;
		_tiles[i].rc.bottom += value;
	}
}

testScene::testScene()
{
}

testScene::~testScene()
{
}
