#include "stdafx.h"
#include "testScene.h"


HRESULT testScene::init()
{
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

	for (int i = 0; i < 3; ++i)
	{
		rect[i].rc = RectMake(rect[i].x, rect[i].y, 20, 20);
	}

	if (_player->getPlayerX() > cameraRect.right) ++cameraX;
	if (_player->getPlayerX() < cameraRect.left) --cameraX;

	if (_player->getPlayerY() < cameraRect.top)
	{
		--Background.top;
		--Background.bottom;
		--cameraY;
	}
	if (_player->getPlayerY() > cameraRect.bottom)
	{
		++Background.top;
		++Background.bottom;
		++cameraY;
	}
}

void testScene::render()
{
	_image->render(getMemDC());
	//_test->loopRender(getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), cameraX, cameraY);
	_test->render(getMemDC(),Background.left, Background.top);
	//Rectangle(getMemDC(), Background.left, Background.top, Background.right, Background.bottom);
	Rectangle(getMemDC(), cameraRect.left, cameraRect.top, cameraRect.right, cameraRect.bottom);
	_player->render();

}

testScene::testScene()
{
}


testScene::~testScene()
{
}
