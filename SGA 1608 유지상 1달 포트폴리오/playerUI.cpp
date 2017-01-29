#include "stdafx.h"
#include "playerUI.h"


HRESULT playerUI::init()
{
	_hpIMG = IMAGEMANAGER->addFrameImage("hp", "IMAGE/UI/hp.bmp", 200, 50, 4, 1, true, RGB(0, 0, 0));
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
	if (HP <= 4)
	{
		_hpIMG->frameRender(getMemDC(), 20, 20, HP % 4, 0);
	}
	else
	{
		for (int i = 0; i < (HP / 4) + 1; ++i)
		{
			if (i != (HP / 4))
				_hpIMG->frameRender(getMemDC(), 20 + _hpIMG->getFrameWidth() * i, 20, 0, 0);
			else
				_hpIMG->frameRender(getMemDC(), 20 + _hpIMG->getFrameWidth() * i, 20, HP % 4, 0);
		}
	}
}

playerUI::playerUI()
{
}


playerUI::~playerUI()
{
}
