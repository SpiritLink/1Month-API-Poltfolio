#include "stdafx.h"
#include "testScene.h"


HRESULT testScene::init()
{
	DATABASE->setBaseTime(TIMEMANAGER->getWorldTime());
	DATABASE->setDestCamX(WINSIZEX / 2);
	DATABASE->setDestCamY(WINSIZEY / 2);
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
	cameraMove();

	if (KEYMANAGER->isStayKeyDown('Q'))
	{
		DATABASE->setSourCamX(Background.left);
		DATABASE->setSourCamY(Background.top);
	}

	if (KEYMANAGER->isStayKeyDown('W'))
	{
		DATABASE->setSourCamX(Background.right);
		DATABASE->setSourCamY(Background.bottom);
	}

	if (KEYMANAGER->isStayKeyDown('E'))
	{
		DATABASE->setSourCamX(_player->getPlayerX());
		DATABASE->setSourCamY(_player->getPlayerY());	
		DATABASE->setDestCamX(WINSIZEX / 2);
		DATABASE->setDestCamY(WINSIZEY / 2);
	}
}

void testScene::render()
{
	_image->render(getMemDC());
	Rectangle(getMemDC(), Background.left, Background.top, Background.right, Background.bottom);
	_test->render(getMemDC(), Background.left, Background.top);
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
	if (DATABASE->getBaseTime() + 0.02f <= TIMEMANAGER->getWorldTime())
	{
		float angle = getAngle(DATABASE->getDestCamX(), DATABASE->getDestCamY(), DATABASE->getSourCamX(), DATABASE->getSourCamY());
		int distanceX = getDistance(DATABASE->getDestCamX(), 0, DATABASE->getSourCamX(), 0);
		int distanceY = getDistance(0, DATABASE->getDestCamY(), 0, DATABASE->getSourCamY());

		if (angle >= 0 && angle < 0.5f * PI)	if (Background.right  < WINSIZEX) return;
		if (angle > 1.5f * PI && angle < 2.0f * PI)	if (Background.right  < WINSIZEX) return;
		if (angle > 0.5f * PI && angle < 1.5f * PI)	if (Background.left > 0) return;	
		if (angle > 0 && angle < PI) if (Background.top > 0) return;
		if (angle > PI && angle < 2.0f * PI)	if (Background.bottom < WINSIZEY) return;

		DATABASE->setBaseTime(TIMEMANAGER->getWorldTime());

		//X좌표 이동
		if (DATABASE->getSourCamX() > WINSIZEX / 2)		//화면 오른쪽으로 움직일때
		{
			Background.left -= distanceX / 10;
			Background.right -= distanceX / 10;
			_player->addPlayerX(-distanceX / 10);
		}

		if (DATABASE->getSourCamX() < WINSIZEX / 2)		//화면 왼쪽으로 움직일때
		{
			Background.left += distanceX / 10;
			Background.right += distanceX / 10;
			_player->addPlayerX(distanceX / 10);
		}

		//Y좌표 이동
		if (DATABASE->getSourCamY() > WINSIZEY / 2)		//화면 아래쪽으로 움직일때
		{
			Background.top -= distanceY / 10;
			Background.bottom -= distanceY / 10;
			_player->addPlayerY(-distanceY / 10);
		}
		
		if (DATABASE->getSourCamY() < WINSIZEY / 2)		//화면 위쪽으로 움직일때
		{
			Background.top += distanceY / 10;
			Background.bottom += distanceY / 10;
			_player->addPlayerY(distanceY / 10);
		}
	}
}

testScene::testScene()
{
}

testScene::~testScene()
{
}
