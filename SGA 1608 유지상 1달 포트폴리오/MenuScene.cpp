#include "stdafx.h"
#include "MenuScene.h"


HRESULT MenuScene::init()
{
	IMAGEMANAGER->addImage("black", "IMAGE/UI/black.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 0));
	IMAGEMANAGER->addImage("saveArea", "IMAGE/UI/SaveArea.bmp", 800, 150, true, RGB(255, 0, 0));
	IMAGEMANAGER->addImage("selectArea", "IMAGE/UI/SelectArea.bmp", 200, 51, true, RGB(255, 0, 0));
	IMAGEMANAGER->addImage("name", "IMAGE/UI/name.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 0));
	IMAGEMANAGER->addImage("title", "IMAGE/UI/title.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 0));
	IMAGEMANAGER->addImage("keyBoard", "IMAGE/UI/keyboard.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 0));
	currentTime = TIMEMANAGER->getWorldTime();
	showName = true;
	showLogo = false;
	showMenu = false;
	showKey = false;
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
	
	if (showKey) IMAGEMANAGER->findImage("keyBoard")->render(getMemDC());
}

void MenuScene::keyboardInput()
{
	if (showMenu && KEYMANAGER->isOnceKeyDown(VK_DOWN) && SelectMenu < 3)	SelectMenu++;
	if (showMenu && KEYMANAGER->isOnceKeyDown(VK_UP) && SelectMenu > 0) SelectMenu--;
	if (showMenu && KEYMANAGER->isOnceKeyDown(VK_RIGHT) && SelectMenu < 5)	SelectMenu++;
	if (showMenu && KEYMANAGER->isOnceKeyDown(VK_LEFT) && SelectMenu > 3) SelectMenu--;

	//플레이어의 점프 또는 공격버튼을 누르면 현재 선택 메뉴의 번호에 따라 특정한 행동을 하게 지시합니다.
	if (showMenu && (KEYMANAGER->isOnceKeyDown('Z') || KEYMANAGER->isOnceKeyDown('X')))
	{
		switch (SelectMenu)
		{
		case 0:	break;		//1번째 세이브 파일
		case 1:	break;		//2번째 세이브 파일
		case 2:	break;		//3번째 세이브 파일
		case 3:	break;		//딜리트 세이브 파일
			//사용하는 키 안내
		case 4:
			showMenu = false;
			showKey = true;
			break;
		case 5:	break;		//게임 시작
		}
	}

	if (showKey && (KEYMANAGER->isOnceKeyDown('Z') || KEYMANAGER->isOnceKeyDown('X')))
	{
		showKey = false;
		showMenu = true;
	}
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
