#include "stdafx.h"
#include "MenuScene.h"


HRESULT MenuScene::init()
{
	IMAGEMANAGER->addImage("saveArea", "IMAGE/UI/SaveArea.bmp", 800, 150, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("black", "IMAGE/UI/black.bmp", WINSIZEX, WINSIZEY, false, RGB(0, 0, 0));
	return S_OK;
}

void MenuScene::release()
{
}

void MenuScene::update()
{
}

void MenuScene::render()
{
	IMAGEMANAGER->findImage("black")->render(getMemDC());
	IMAGEMANAGER->findImage("saveArea")->render(getMemDC(),0,0);
	IMAGEMANAGER->findImage("saveArea")->render(getMemDC(), 0, 150);
	IMAGEMANAGER->findImage("saveArea")->render(getMemDC(), 0, 300);

}

MenuScene::MenuScene()
{
}


MenuScene::~MenuScene()
{
}
