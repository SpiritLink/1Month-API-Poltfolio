#include "stdafx.h"
#include "testScene.h"


HRESULT testScene::init()
{
	DATABASE->setBaseTime(TIMEMANAGER->getWorldTime());
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
	Background = RectMake(0, 0, 1500, 751);
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
}

void testScene::render()
{
	_image->render(getMemDC());
	_test->loopRender(getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), cameraX, cameraY);
	Rectangle(getMemDC(), cameraRect.left, cameraRect.top, cameraRect.right, cameraRect.bottom);
	_player->render();
}

void testScene::cameraMove()
{
	DATABASE->setCameraX(_player->getPlayerX());
	DATABASE->setCameraY(_player->getPlayerY());

	if (!(PtInRect(&cameraRect, PointMake(DATABASE->getCameraX(), DATABASE->getCameraY()))))	//플레이어가 카메라 렉트를 벗어나면
	{
		//가려고 하는 좌표 -> 현재 좌표 의 거리와 각도를 구한다.
		float distance = getDistance(WINSIZEX / 2, WINSIZEY / 2,DATABASE->getCameraX(), DATABASE->getCameraY());
		float angle = getAngle(WINSIZEX / 2, WINSIZEY / 2,DATABASE->getCameraX(), DATABASE->getCameraY());

		cameraX += cosf(angle) * distance / 50.0f;
		cameraY += -sinf(angle) * distance / 50.0f;

		_player->addPlayerX(-cosf(angle) * distance / 50.0f);
		_player->addPlayerY(sinf(angle) * distance / 50.0f);
	}
}

testScene::testScene()
{
}


testScene::~testScene()
{
}
