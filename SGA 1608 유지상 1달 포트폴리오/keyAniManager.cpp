#include "stdafx.h"
#include "keyAniManager.h"
#include "image.h"
#include "animation.h"


keyAniManager::keyAniManager()
{
}


keyAniManager::~keyAniManager()
{
}

HRESULT keyAniManager::init()
{
	return S_OK;
}

void keyAniManager::release()
{
	deleteAll();
}

void keyAniManager::update()
{
	iterAnimations iter = _mTotalAnimation.begin();

	for (iter; iter != _mTotalAnimation.end(); ++iter)
	{
		if (!iter->second->isPlay()) continue;
		iter->second->frameUpdate(TIMEMANAGER->getElapsedTime());
	}
}

void keyAniManager::render()
{
}

void keyAniManager::addDefaultFrameAnimation(string animationKeyName, char * imageKeyName, int fps, bool reverse, bool loop)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setDefPlayFrame(reverse, loop);
	ani->setFPS(fps);

	_mTotalAnimation.insert(make_pair(animationKeyName, ani));
}

void keyAniManager::addArrayFrameAnimation(string animationKeyName, char * imageKeyName, int * arr, int arrlen, int fps, bool loop)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(arr, arrlen, loop);
	ani->setFPS(fps);

	_mTotalAnimation.insert(make_pair(animationKeyName, ani));
}

void keyAniManager::addCoordinateFrameAnimation(string animationKeyName, char * imageKeyName, int start, int end, int fps, bool reverse, bool loop)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(start, end, reverse, loop);
	ani->setFPS(fps);

	_mTotalAnimation.insert(make_pair(animationKeyName, ani));
}

void keyAniManager::start(string animationKeyName, CALLBACKCLASS cbFunction, void * targetClass)
{
	findAnimation(animationKeyName)->start(cbFunction, targetClass);
}

void keyAniManager::stop(string animationKeyName)
{
	findAnimation(animationKeyName)->stop();
}

void keyAniManager::pause(string animationKeyName)
{
	findAnimation(animationKeyName)->pause();
}

void keyAniManager::resume(string animationKeyName)
{
	findAnimation(animationKeyName)->resume();
}

animation * keyAniManager::findAnimation(string animationKeyName)
{
	iterAnimations iter = _mTotalAnimation.find(animationKeyName);
	if (iter != _mTotalAnimation.end())
	{
		return iter->second;
	}
	return nullptr;
}

void keyAniManager::deleteAll()
{
	iterAnimations iter = _mTotalAnimation.begin();

	for (iter; iter != _mTotalAnimation.end();)
	{
		if (iter->second != nullptr)
		{
			iter->second->release();
			SAFE_DELETE(iter->second);
			iter = _mTotalAnimation.erase(iter);
		}
		else
			++iter;
	}

	_mTotalAnimation.clear();
}
