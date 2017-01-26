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
	_player->update();											//플레이어에서 보고자 하는 대상의 위치를 먼저 전송합니다.

	//만약 다른 대상을 보고싶다면
	if (KEYMANAGER->isStayKeyDown('Q'))
	{
		DATABASE->setSourCamX(Background.left + WINSIZEX / 2);	//보고싶은 대상의 X좌표 위치
		DATABASE->setSourCamY(Background.top + WINSIZEY / 2);	//보고싶은 대상위 Y좌표 위치
	}

	if (KEYMANAGER->isStayKeyDown('W'))
	{
		DATABASE->setSourCamX(Background.right - WINSIZEX / 2);	//보고싶은 대상의 X좌표 위치
		DATABASE->setSourCamY(Background.bottom - WINSIZEY / 2);//보고싶은 대상의 Y좌표 위치
	}

	if (KEYMANAGER->isStayKeyDown('E'))
	{
		DATABASE->setDestCamX(WINSIZEX / 2);			//대상이 고정되기 원하는 X좌표 위치
		DATABASE->setDestCamY(WINSIZEY / 2);			//대상이 고정되기 원하는 Y좌표 위치
	}

	if (KEYMANAGER->isStayKeyDown('R'))
	{
		DATABASE->setDestCamX(WINSIZEX / 2);			//대상이 고정되기 원하는 X좌표 위치
		DATABASE->setDestCamY((WINSIZEY / 4) * 3);		//대상이 고정되기 원하는 Y좌표 위치
	}
	
	//좌표 설정이 끝난뒤에 Camera함수에 진입합니다.
	cameraMove();

}

void testScene::render()
{
	_image->render(getMemDC());
	Rectangle(getMemDC(), Background.left, Background.top, Background.right, Background.bottom);
	_test->render(getMemDC(), Background.left, Background.top);
	_tileMap->render();
	_player->render();
	if (KEYMANAGER->isToggleKey(VK_SHIFT)) _tileMap->miniMapRender();

	SetTextColor(getMemDC(), RGB(255, 255, 255));
}

void testScene::cameraMove()
{
	//현재는 사실상 쓰이지 않고 있습니다.
	//->소수점 연산 도중 반올림에 의해 좌표가 어긋나 다른 방식으로 대체됨
	float angle = getAngle(DATABASE->getDestCamX(), DATABASE->getDestCamY(), DATABASE->getSourCamX(), DATABASE->getSourCamY());
	int distanceX = getDistance(DATABASE->getDestCamX(), 0, DATABASE->getSourCamX(), 0);
	int distanceY = getDistance(0, DATABASE->getDestCamY(), 0, DATABASE->getSourCamY());

	//만약 화면을 벗어난다면
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
