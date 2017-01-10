#include "stdafx.h"
#include "testScene.h"


HRESULT testScene::init()
{
	_image = IMAGEMANAGER->addImage("Èò¹è°æ", "IMAGE/whiteBackground.bmp", WINSIZEX, WINSIZEY, false, RGB(0, 0, 0));
	_player = new player;
	_player->init();

	for (int i = 0; i < 3; ++i)
	{
		rect[i].x = i * 100;
		rect[i].y = i * 30;
	}
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
}

void testScene::render()
{
	_image->render(getMemDC());
	_player->render();
}

testScene::testScene()
{
}


testScene::~testScene()
{
}
