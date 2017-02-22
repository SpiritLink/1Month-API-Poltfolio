#include "stdafx.h"
#include "playerUI.h"


HRESULT playerUI::init()
{
	HP = 1;
	MP = 1;
	_hpFrame = IMAGEMANAGER->addImage("hpFrame", "IMAGE/UI/hpFrame.bmp", 39, 36, true, RGB(0, 0, 255));
	_sealFrame = IMAGEMANAGER->addImage("sealFrame", "IMAGE/UI/sealFrame.bmp", 33, 33, true, RGB(0, 0, 255));
	_hpIMG = IMAGEMANAGER->addFrameImage("hp", "IMAGE/UI/hp.bmp", 200, 50, 4, 1, true, RGB(0, 0, 0));
	_heart = IMAGEMANAGER->addFrameImage("heart", "IMAGE/UI/heart2.bmp", 84, 24, 3, 1, true, RGB(255, 255, 255));
	_number = IMAGEMANAGER->addFrameImage("number", "IMAGE/UI/number2.bmp", 200, 30, 10, 1, true, RGB(255, 255, 255));
	currentTime = TIMEMANAGER->getWorldTime();

	_menuButton = IMAGEMANAGER->addImage("menuButton", "IMAGE/UI/menuButton.bmp", 200, 51, true, RGB(255, 0, 0));
	_menuButton2 = IMAGEMANAGER->addImage("menuButton2", "IMAGE/UI/menuButton2.bmp", 200, 51, true, RGB(255, 0, 0));
	_restartButton = IMAGEMANAGER->addImage("restartButton", "IMAGE/UI/restartButton.bmp", 200, 51, true, RGB(255, 0, 0));
	_restartButton2 = IMAGEMANAGER->addImage("restartButton2", "IMAGE/UI/restartButton2.bmp", 200, 51, true, RGB(255, 0, 0));
	_gameOver = IMAGEMANAGER->addImage("gameOver", "IMAGE/UI/gameOver.bmp", 500, 200, true, RGB(255, 0, 0));

	alphaValue = 0;
	menuSelect = 0;
	return S_OK;
}

void playerUI::release()
{
}

void playerUI::update()
{
	if (currentTime + 0.25f < TIMEMANAGER->getWorldTime())
	{
		currentTime = TIMEMANAGER->getWorldTime();
		HP = DATABASE->getHP();
		MP = DATABASE->getMP();
	}

	if (DATABASE->getPlayerDie())
	{

		alphaValue += 2;
		if (alphaValue >= 255) alphaValue = 255;
		
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			if(menuSelect < 1) menuSelect++;
		}

		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			if(menuSelect > 0) menuSelect--;
		}

		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			switch (menuSelect)
			{
			case 0:	DATABASE->setMenu(true); break;
			case 1:	DATABASE->setRestart(true); break;
			}
		}
	}
}

void playerUI::render()
{
	_hpFrame->render(getMemDC(), 20, 20);
	_sealFrame->render(getMemDC(), 20, 70);

	if (!(DATABASE->getPlayerDie()))
	{
		for (int i = 0; i < (HP - 1) / 3 + 1; ++i)
		{
			if (i != (HP - 1) / 3 && HP > 0) _heart->frameRender(getMemDC(), 70 + _hpIMG->getFrameWidth() / 2 * i, 20, 0, 0);
			else if (HP > 0) _heart->frameRender(getMemDC(), 70 + _hpIMG->getFrameWidth() / 2 * i, 20, HP % 3, 0);
		}

		if (MP > 10)
		{
			_number->frameRender(getMemDC(), 70, 70, MP / 10, 0);
			_number->frameRender(getMemDC(), 90, 70, MP % 10, 0);
		}
		else if (MP < 10)
		{
			_number->frameRender(getMemDC(), 70, 70, MP % 10, 0);
		}
	}
	if (DATABASE->getPlayerDie())
	{
		_gameOver->alphaRender(getMemDC(), (WINSIZEX - _gameOver->getWidth()) / 2, ((WINSIZEY / 2) - _gameOver->getHeight()) / 2,alphaValue);

		switch (menuSelect)
		{
		case 0:
			_menuButton2->alphaRender(getMemDC(), (WINSIZEX / 2) - 300, WINSIZEY - 100, alphaValue);
			break;
		case 1:
			_restartButton2->alphaRender(getMemDC(), (WINSIZEX / 2) + 100, WINSIZEY - 100, alphaValue);
			break;
		}
		if(menuSelect != 0)_menuButton->alphaRender(getMemDC(), (WINSIZEX / 2) - 300, WINSIZEY - 100,alphaValue);
		if(menuSelect != 1)_restartButton->alphaRender(getMemDC(), (WINSIZEX / 2) + 100, WINSIZEY - 100,alphaValue);
	}
}

playerUI::playerUI()
{
}


playerUI::~playerUI()
{
}
