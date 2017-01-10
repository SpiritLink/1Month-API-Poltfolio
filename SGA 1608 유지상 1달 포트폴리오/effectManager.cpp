#include "stdafx.h"
#include "effectManager.h"
#include "effect.h"

effectManager::effectManager()
{
}

effectManager::~effectManager()
{
}

HRESULT effectManager::init()
{
	return S_OK;
}

void effectManager::release()
{
	iterEffect mIter;

	mIter = _mTotalEffect.begin();
	for (mIter; mIter != _mTotalEffect.end(); ++mIter)
	{
		if (mIter->second.size() != 0)
		{
			iterEffects vArrIter = mIter->second.begin();
			for (vArrIter; vArrIter != mIter->second.end();)
			{
				(*vArrIter)->release();
				SAFE_DELETE(*vArrIter);
				vArrIter = mIter->second.erase(vArrIter);
			}

		}

	}

	_mTotalEffect.clear();
}

void effectManager::update()
{
	iterEffect mIter;

	mIter = _mTotalEffect.begin();
	for (mIter; mIter != _mTotalEffect.end(); ++mIter)
	{
		iterEffects vArrIter = mIter->second.begin();
		for (vArrIter; vArrIter != mIter->second.end(); ++vArrIter)
		{
			(*vArrIter)->update(TIMEMANAGER->getElapsedTime());
		}
	}
}

void effectManager::render()
{
	iterEffect mIter;

	mIter = _mTotalEffect.begin();
	for (mIter; mIter != _mTotalEffect.end(); ++mIter)
	{
		iterEffects vArrIter = mIter->second.begin();
		for (vArrIter; vArrIter != mIter->second.end(); ++vArrIter)
		{
			(*vArrIter)->render();
		}
	}
}

void effectManager::addEffect(string effectName, const char* imageName,
	int imageWidth, int imageHeight, int effectWidth, int effectHeight,
	int fps, int buffer)
{
	image* img;
	arrEffects vEffectBuffer;

	if (IMAGEMANAGER->findImage(effectName))
	{
		img = IMAGEMANAGER->findImage(effectName);
	}
	else
	{
		img = IMAGEMANAGER->addImage(effectName, imageName, imageWidth, imageHeight, true, RGB(255, 0, 255));
	}

	for (int i = 0; i < buffer; ++i)
	{
		vEffectBuffer.push_back(new effect);
		vEffectBuffer[i]->init(img, effectWidth, effectHeight, fps);
	}

	_mTotalEffect.insert(make_pair(effectName, vEffectBuffer));
}

void effectManager::play(string effectName, int x, int y)
{
	iterEffect mIter;

	mIter = _mTotalEffect.begin();
	for (mIter; mIter != _mTotalEffect.end(); ++mIter)
	{
		if (!(effectName == mIter->first)) continue;

		iterEffects vArrIter = mIter->second.begin();
		for (vArrIter; vArrIter != mIter->second.end(); ++vArrIter)
		{
			if ((*vArrIter)->getIsRunning()) continue;
			(*vArrIter)->start(x, y);
			return;
		}
	}
}
