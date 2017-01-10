#pragma once

#include "singletonBase.h"

typedef void(*CALLBACKCLASS)(void* targetClass);

class image;
class animation;

class keyAniManager : public singletonBase<keyAniManager>
{
private:
	typedef map<string, animation*> arrAnimation;
	typedef map<string, animation*>::iterator iterAnimations;

	arrAnimation _mTotalAnimation;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void addDefaultFrameAnimation(string animationKeyName, char* imageKeyName, int fps,
		bool reverse, bool loop);

	void addArrayFrameAnimation(string animationKeyName, char* imageKeyName, int* arr, int arrlen,
		int fps, bool loop);

	void addCoordinateFrameAnimation(string animationKeyName, char* imageKeyName, int start, int end,
		int fps, bool reverse, bool loop);

	void start(string animationKeyName, CALLBACKCLASS cbFunction, void* targetClass);
	void stop(string animationKeyName);
	void pause(string animationKeyName);
	void resume(string animationKeyName);

	animation* findAnimation(string animationKeyName);

	void deleteAll();

	keyAniManager();
	~keyAniManager();
};

