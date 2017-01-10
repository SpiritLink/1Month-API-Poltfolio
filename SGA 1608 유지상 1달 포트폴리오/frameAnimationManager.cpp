#include "stdafx.h"
#include "frameAnimationManager.h"
#include "frameAnimation.h"

frameAnimationManager::frameAnimationManager()
{
}


frameAnimationManager::~frameAnimationManager()
{
}

HRESULT frameAnimationManager::init()
{
	_vAnimation.reserve(3);

	return S_OK;
}

void frameAnimationManager::release()
{
	for (_viAnimation = _vAnimation.begin(); _viAnimation != _vAnimation.end();)
	{
		if (_vAnimation.size() != 0)
		{
			SAFE_DELETE(*_viAnimation);
			_viAnimation = _vAnimation.erase(_viAnimation);
		}
		else ++_viAnimation;
	}

	_vAnimation.clear();
}

void frameAnimationManager::update()
{
	/*for (int i = 0; i < _vAnimation.size();)
	{
	_vAnimation[i]->update();
	if (!(_vAnimation[i]->getIsPlay()))
	{
	SAFE_DELETE(_vAnimation[i]);
	_vAnimation.erase(_vAnimation.begin() + i);
	}
	else ++i;
	}*/



	for (_viAnimation = _vAnimation.begin(); _viAnimation != _vAnimation.end();)
	{
		(*_viAnimation)->update();
		if (!((*_viAnimation)->getIsPlay()))
		{
			SAFE_DELETE(*_viAnimation);
			_viAnimation = _vAnimation.erase(_viAnimation);


		}
		else
			++_viAnimation;

	}

}

void frameAnimationManager::render()
{
}

void frameAnimationManager::animationXFrame(image * img, int xFrame, float count, CALLBACKFUNCTION cbFunction)
{
	frameAnimation* fa = new frameAnimation;
	fa->init();
	fa->animationXFrame(img, xFrame, count, cbFunction);
	_vAnimation.push_back(fa);
}

void frameAnimationManager::animationYFrame(image * img, int yFrame, float count, CALLBACKFUNCTION cbFunction)
{
	frameAnimation* fa = new frameAnimation;
	fa->init();
	fa->animationYFrame(img, yFrame, count, cbFunction);
	_vAnimation.push_back(fa);
}


