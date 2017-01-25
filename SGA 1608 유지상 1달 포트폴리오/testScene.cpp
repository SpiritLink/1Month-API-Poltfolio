#include "stdafx.h"
#include "testScene.h"


HRESULT testScene::init()
{
	DATABASE->setBaseTime(TIMEMANAGER->getWorldTime());
	DATABASE->setDestCamX(WINSIZEX / 2);
	DATABASE->setDestCamY(WINSIZEY / 2);
	IMAGEMANAGER->addFrameImage("tileMap", "IMAGE/tile/tile.bmp", 0, 0, 1350, 1200, SAMPLETILEX, SAMPLETILEY, true, RGB(0, 0, 0));
	_image = IMAGEMANAGER->addImage("흰배경", "IMAGE/whiteBackground.bmp", WINSIZEX, WINSIZEY, false, RGB(0, 0, 0));

	_tileMap = new tileMap;
	_tileMap->init("DATA/MAP/Town.map");

	_player = new player;
	_player->init();
	_player->setTileMapMemoryAddress(_tileMap);
	_player->firstCollisionTileCheck();

	cameraX = 0;
	cameraY = 0;

	_test = IMAGEMANAGER->addImage("테스트배경", "IMAGE/test.bmp", TILESIZEX, TILESIZEY, false, RGB(0, 0, 0));
	Background = RectMake(0, 0, _test->getWidth(), _test->getHeight());
	return S_OK;
}

void testScene::release()
{
	_player->release();
	SAFE_DELETE(_player);

	_tileMap->release();
	SAFE_DELETE(_tileMap);
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

	if (KEYMANAGER->isStayKeyDown('R'))
	{
		DATABASE->setDestCamX(WINSIZEX / 2);
		DATABASE->setDestCamY((WINSIZEY / 4) * 3);
	}
	cameraMove();

}

void testScene::render()
{
	_image->render(getMemDC());
	Rectangle(getMemDC(), Background.left, Background.top, Background.right, Background.bottom);
	_test->render(getMemDC(), Background.left, Background.top);
	//tileRender();
	_tileMap->render();
	_player->render();

	SetTextColor(getMemDC(), RGB(255, 255, 255));
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
			_tileMap->moveTileX(diffrence);
			_player->addPlayerX(-diffrence);//플레이어의 움직이는 정도를 조절
		}
		if (Background.left > 0)
		{
			int diffrence = Background.left;
			Background.right -= diffrence;
			Background.left -= diffrence;
			_player->addPlayerX(+diffrence);
			_tileMap->moveTileX(-diffrence);
		}
		if (Background.top > 0)
		{
			int diffrence = Background.top;
			Background.top -= diffrence;
			Background.bottom -= diffrence;
			_player->addPlayerY(diffrence);
			_tileMap->moveTileY(-diffrence);
		}

		if (Background.bottom < WINSIZEY)
		{
			int diffrence = WINSIZEY - Background.bottom;
			Background.top += diffrence;
			Background.bottom += diffrence;
			_player->addPlayerY(-diffrence);
			_tileMap->moveTileY(+diffrence);
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
			_player->addPlayerX(-distanceX / 10);
			_tileMap->moveTileX(-distanceX / 10);
		}

		if (DATABASE->getSourCamX() < DATABASE->getDestCamX())		//화면 왼쪽으로 움직일때
		{
			Background.left += distanceX / 10;
			Background.right += distanceX / 10;
			_player->addPlayerX(distanceX / 10);
			_tileMap->moveTileX(distanceX / 10);
		}

		//Y좌표 이동
		if (DATABASE->getSourCamY() > DATABASE->getDestCamY())		//화면 아래쪽으로 움직일때
		{
			Background.top -= distanceY / 10;
			Background.bottom -= distanceY / 10;
			_player->addPlayerY(-distanceY / 10);
			_tileMap->moveTileY(-distanceY / 10);
		}
		
		if (DATABASE->getSourCamY() < DATABASE->getDestCamY())		//화면 위쪽으로 움직일때
		{
			Background.top += distanceY / 10;
			Background.bottom += distanceY / 10;
			_player->addPlayerY(distanceY / 10);
			_tileMap->moveTileY(distanceY / 10);
		}
}


testScene::testScene()
{
}

testScene::~testScene()
{
}
