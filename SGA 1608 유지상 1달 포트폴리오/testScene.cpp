#include "stdafx.h"
#include "testScene.h"


HRESULT testScene::init()
{
	_image = IMAGEMANAGER->addImage("Èò¹è°æ", "IMAGE/whiteBackground.bmp", WINSIZEX, WINSIZEY, false, RGB(0, 0, 0));
	_player = new player;
	_player->init();
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
