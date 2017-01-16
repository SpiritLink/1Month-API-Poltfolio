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

	_test = IMAGEMANAGER->addImage("테스트배경", "IMAGE/test.bmp", 1500, 751, false, RGB(0, 0, 0));
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
		DATABASE->setBaseTime(TIMEMANAGER->getWorldTime());
		DATABASE->setSourCamX(_player->getPlayerX());
		DATABASE->setSourCamY(_player->getPlayerY());

		Background.right += DATABASE->getCamDistanceX() / 30.0f;
		Background.left += DATABASE->getCamDistanceX() / 30.0f;

		Background.top += DATABASE->getCamDistanceY() / 30.0f;
		Background.bottom += DATABASE->getCamDistanceY() / 30.0f;

		_player->addPlayerX(DATABASE->getCamDistanceX() / 10.0f);
		_player->addPlayerY(DATABASE->getCamDistanceY() / 10.0f);

	}
	//}
}

testScene::testScene()
{
}


testScene::~testScene()
{
}
