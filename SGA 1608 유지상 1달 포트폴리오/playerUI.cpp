#include "stdafx.h"
#include "playerUI.h"


HRESULT playerUI::init()
{
	_hpFrame = IMAGEMANAGER->addImage("hpFrame", "IMAGE/UI/hpFrame.bmp", 39, 36, true, RGB(0, 0, 255));
	_sealFrame = IMAGEMANAGER->addImage("sealFrame", "IMAGE/UI/sealFrame.bmp", 33, 33, true, RGB(0, 0, 255));
	_hpIMG = IMAGEMANAGER->addFrameImage("hp", "IMAGE/UI/hp.bmp", 200, 50, 4, 1, true, RGB(0, 0, 0));
	_heart = IMAGEMANAGER->addFrameImage("hear", "IMAGE/UI/heart.bmp", 84, 24, 3, 1, true, RGB(255, 255, 255));
	currentTime = TIMEMANAGER->getWorldTime();
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
}

void playerUI::render()
{
	_hpFrame->render(getMemDC(), 20, 20);
	_sealFrame->render(getMemDC(), 20, 70);
	if (HP <= 3)
	{
		_heart->frameRender(getMemDC(), 70, 20, HP - 1, 0);
	}
	else
	{
		for (int i = 0; i < (HP / 3) + 1; ++i)
		{
			if (i != (HP / 3))
				_heart->frameRender(getMemDC(), 70 + _hpIMG->getFrameWidth() / 2 * i, 20, 2, 0);
			else
				_heart->frameRender(getMemDC(), 70 + _hpIMG->getFrameWidth() / 2 * i, 20, HP % 3, 0);
		}
	}
}

playerUI::playerUI()
{
}


playerUI::~playerUI()
{
}
