#include "stdafx.h"
#include "playerUI.h"


HRESULT playerUI::init()
{
	_hpIMG = IMAGEMANAGER->addFrameImage("hp", "IMAGE/UI/hp.bmp", 200, 50, 4, 1, true, RGB(0, 0, 0));
	_heart = IMAGEMANAGER->addFrameImage("hear", "IMAGE/UI/heart.bmp", 84, 24, 3, 1, true, RGB(255, 255, 255));
	return S_OK;
}

void playerUI::release()
{
}

void playerUI::update()
{
	HP = DATABASE->getHP();
	MP = DATABASE->getMP();
}

void playerUI::render()
{
	if (HP <= 3)
	{
		_heart->frameRender(getMemDC(), 20, 20, HP % 3, 0);
	}
	else
	{
		for (int i = 0; i < (HP / 3) + 1; ++i)
		{
			if (i != (HP / 3))
				_heart->frameRender(getMemDC(), 20 + _hpIMG->getFrameWidth() / 2 * i, 20, 0, 0);
			else
				_heart->frameRender(getMemDC(), 20 + _hpIMG->getFrameWidth() / 2 * i, 20, HP % 3, 0);
		}
	}
}

playerUI::playerUI()
{
}


playerUI::~playerUI()
{
}
