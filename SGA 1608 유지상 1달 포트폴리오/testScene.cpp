#include "stdafx.h"
#include "testScene.h"


HRESULT testScene::init()
{
	_image = IMAGEMANAGER->addImage("Èò¹è°æ", "IMAGE/whiteBackground.bmp", WINSIZEX, WINSIZEY, false, RGB(0, 0, 0));
	return S_OK;
}

void testScene::release()
{
}

void testScene::update()
{
}

void testScene::render()
{
	_image->render(getMemDC());
}

testScene::testScene()
{
}


testScene::~testScene()
{
}
