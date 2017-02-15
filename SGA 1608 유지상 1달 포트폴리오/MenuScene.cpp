#include "stdafx.h"
#include "MenuScene.h"


HRESULT MenuScene::init()
{
	IMAGEMANAGER->addImage("black", "IMAGE/UI/black.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 0));
	IMAGEMANAGER->addImage("saveArea", "IMAGE/UI/SaveArea.bmp", 800, 150, true, RGB(255, 0, 0));
	IMAGEMANAGER->addImage("selectArea", "IMAGE/UI/SelectArea.bmp", 200, 51, true, RGB(255, 0, 0));
	IMAGEMANAGER->addImage("name", "IMAGE/UI/name.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 0));
	IMAGEMANAGER->addImage("title", "IMAGE/UI/title.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 0));
	currentTime = TIMEMANAGER->getWorldTime();
	showName = true;
	showLogo = false;
	showMenu = false;
	SelectMenu = 0;
	alphaValue = 0;
	fadeOut = false;
	return S_OK;
}

void MenuScene::release()
{
}

void MenuScene::update()
{
	keyboardInput();
	changeScene();
}

void MenuScene::render()
{
	IMAGEMANAGER->findImage("black")->render(getMemDC());
	if (showName) IMAGEMANAGER->findImage("name")->render(getMemDC(), 0, 0);

	if (showLogo) IMAGEMANAGER->findImage("title")->alphaRender(getMemDC(), 0, 0, alphaValue);

	if (showMenu)
	{
		if (SelectMenu != 0)IMAGEMANAGER->findImage("saveArea")->render(getMemDC(), 0, 0);
		if (SelectMenu != 1)IMAGEMANAGER->findImage("saveArea")->render(getMemDC(), 0, 150);
		if (SelectMenu != 2)IMAGEMANAGER->findImage("saveArea")->render(getMemDC(), 0, 300);
		if (SelectMenu != 3)IMAGEMANAGER->findImage("selectArea")->render(getMemDC(), 50, 500);
		if (SelectMenu != 4)IMAGEMANAGER->findImage("selectArea")->render(getMemDC(), 300, 500);
		if (SelectMenu != 5)IMAGEMANAGER->findImage("selectArea")->render(getMemDC(), 550, 500);

		switch (SelectMenu)
		{
		case 0:	IMAGEMANAGER->findImage("saveArea")->alphaRender(getMemDC(), 0, 0, 120);		break;
		case 1: IMAGEMANAGER->findImage("saveArea")->alphaRender(getMemDC(), 0, 150, 120);		break;
		case 2: IMAGEMANAGER->findImage("saveArea")->alphaRender(getMemDC(), 0, 300, 120);		break;
		case 3: IMAGEMANAGER->findImage("selectArea")->alphaRender(getMemDC(), 50, 500, 120);	break;
		case 4:	IMAGEMANAGER->findImage("selectArea")->alphaRender(getMemDC(), 300, 500, 120);	break;
		case 5: IMAGEMANAGER->findImage("selectArea")->alphaRender(getMemDC(), 550, 500, 120);	break;
		}
	}
}

void MenuScene::keyboardInput()
{
	if (showMenu && KEYMANAGER->isOnceKeyDown(VK_DOWN) && SelectMenu < 3)	SelectMenu++;
	if (showMenu && KEYMANAGER->isOnceKeyDown(VK_UP) && SelectMenu > 0) SelectMenu--;
	if (showMenu && KEYMANAGER->isOnceKeyDown(VK_RIGHT) && SelectMenu < 5)	SelectMenu++;
	if (showMenu && KEYMANAGER->isOnceKeyDown(VK_LEFT) && SelectMenu > 3) SelectMenu--;
}

void MenuScene::changeScene()
{
	if (showName && currentTime + 1.5f < TIMEMANAGER->getWorldTime())
	{
		currentTime = TIMEMANAGER->getWorldTime();
		showName = false;
		showLogo = true;
	}

	if (showLogo)
	{
		if (alphaValue < 254 && !(fadeOut)) alphaValue += 4;
		if (!(fadeOut) && alphaValue >= 250) fadeOut = true;
		if (alphaValue > 1 && fadeOut) alphaValue -= 4;
		if (fadeOut && alphaValue <= 10)
		{
			fadeOut = false;
			alphaValue = 255;
			showLogo = false;
			showMenu = true;
		}
	}
}

MenuScene::MenuScene()
{
}


MenuScene::~MenuScene()
{
}
