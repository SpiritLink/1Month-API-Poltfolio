#include "Stdafx.h"
#include "frameAnimation.h"


frameAnimation::frameAnimation()
	:_callbackFunction(NULL)
{
}

frameAnimation::~frameAnimation()
{

}

HRESULT frameAnimation::init()
{
	_ad = ANIMATIONDIRECTION_NULL;
	_worldTimeCount = TIMEMANAGER->getWorldTime();
	_isPlay = false;

	return S_OK;
}

void frameAnimation::release()
{
}

void frameAnimation::update()
{
	if (!_isPlay) return;

	switch (_ad)
	{
	case ANIMATIONDIRECTION_X:
		if (_count + _worldTimeCount <= TIMEMANAGER->getWorldTime())
		{
			_worldTimeCount = TIMEMANAGER->getWorldTime();

			_xFrameCount++;
			_image->setFrameX(_xFrameCount);

			if (_xFrameCount > _xMaxFrame)
			{
				_image->setFrameX(0);
				_isPlay = false;
				_callbackFunction();
			}

		}
		break;
	case ANIMATIONDIRECTION_Y:
		if (_count + _worldTimeCount <= TIMEMANAGER->getWorldTime())
		{
			_worldTimeCount = TIMEMANAGER->getWorldTime();

			_yFrameCount++;
			_image->setFrameY(_yFrameCount);

			if (_yFrameCount > _yMaxFrame)
			{
				_image->setFrameY(0);
				_isPlay = false;
				_callbackFunction();
			}

		}
		break;

	}
}
void frameAnimation::render()
{
}


void frameAnimation::animationXFrame(image* img, int xFrame, float count, CALLBACKFUNCTION cbFunction)
{
	if (_isPlay) return;
	_isPlay = true;

	_count = count;
	_ad = ANIMATIONDIRECTION_X;
	_worldTimeCount = TIMEMANAGER->getWorldTime();
	_image = img;
	_xMaxFrame = xFrame - 1;
	_yMaxFrame = 0;
	_xFrameCount = 0;
	_yFrameCount = 0;

	_callbackFunction = static_cast<CALLBACKFUNCTION>(cbFunction);

}

void frameAnimation::animationYFrame(image* img, int yFrame, float count, CALLBACKFUNCTION cbFunction)
{
	if (_isPlay) return;
	_isPlay = true;

	_count = count;
	_ad = ANIMATIONDIRECTION_Y;
	_worldTimeCount = TIMEMANAGER->getWorldTime();
	_image = img;
	_xMaxFrame = 0;
	_yMaxFrame = yFrame - 1;
	_xFrameCount = 0;
	_yFrameCount = 0;

	_callbackFunction = static_cast<CALLBACKFUNCTION>(cbFunction);
}