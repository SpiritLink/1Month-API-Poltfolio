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



	for (int i = 0; i < 3; ++i)
	{
		rect[i].x = i * 100;
		rect[i].y = i * 30;
	}

	cameraX = 0;
	cameraY = 0;

	cameraRect = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 100, 100);

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

	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		DATABASE->setDestCamX(0);
		DATABASE->setDestCamY(0);
	}

	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		DATABASE->setDestCamX(WINSIZEX);
		DATABASE->setDestCamY(WINSIZEY);
	}

	if (KEYMANAGER->isOnceKeyDown('E'))
	{
		DATABASE->setDestCamX(WINSIZEX / 2);
		DATABASE->setDestCamY(WINSIZEY / 2);
	}
}

void testScene::render()
{
	_image->render(getMemDC());
	Rectangle(getMemDC(), Background.left, Background.top, Background.right, Background.bottom);
	_test->render(getMemDC(), Background.left, Background.top);
	Rectangle(getMemDC(), cameraRect.left, cameraRect.top, cameraRect.right, cameraRect.bottom);
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
	//if (Background.bottom >= WINSIZEY &&
	//	Background.top <= 0 &&
	//	Background.right >= WINSIZEX &&
	//	Background.left <= 0)
	//{
	if (DATABASE->getBaseTime() + 0.03f <= TIMEMANAGER->getWorldTime())
	{
		float angle = getAngle(DATABASE->getDestCamX(), DATABASE->getDestCamY(), DATABASE->getSourCamX(), DATABASE->getSourCamY());
		if (angle >= 0 && angle < 0.5f * PI)		//0에서 90도일때
		{
			if (Background.right  < WINSIZEX) return;
		}

		if (angle > 1.5f * PI && angle < 2.0f * PI)	//270도에서 360도일때
		{
			if (Background.right  < WINSIZEX) return;
		}

		if (angle > 0.5f * PI && angle < 1.5f * PI)
		{

			if (Background.left > 0) return;
		}
		
		//if (DATABASE->getCamAngle() > 0 && DATABASE->getCamAngle() < PI)
		//{
		//	if (Background.bottom + DATABASE->getCamDistanceY() / 10.0f < WINSIZEY) return;
		//}

		//if (DATABASE->getCamAngle() > PI && DATABASE->getCamAngle() < 2.0f * PI)
		//{
		//	if (Background.top + DATABASE->getCamDistanceY() / 10.0f > -1) return;
		//}

		DATABASE->setBaseTime(TIMEMANAGER->getWorldTime());

		Background.right -= DATABASE->getCamDistanceX() / 10.0f;
		Background.left -= DATABASE->getCamDistanceX() / 10.0f;

		Background.top -= DATABASE->getCamDistanceY() / 10.0f;
		Background.bottom -= DATABASE->getCamDistanceY() / 10.0f;

		_player->addPlayerX(-DATABASE->getCamDistanceX() / 10.0f);
		_player->addPlayerY(-DATABASE->getCamDistanceY() / 10.0f);

	}
	//}
}

testScene::testScene()
{
}


testScene::~testScene()
{
}
