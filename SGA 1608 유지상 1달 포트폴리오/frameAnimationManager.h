#pragma once

#include "singletonBase.h"


typedef void(*CALLBACKFUNCTION)(void);

class frameAnimation;

class frameAnimationManager : public singletonBase<frameAnimationManager>
{
private:
	typedef vector<frameAnimation*> arrAnimation;
	typedef vector<frameAnimation*>::iterator iterAnimation;

	arrAnimation _vAnimation;
	iterAnimation _viAnimation;

	CALLBACKFUNCTION _callbackFunction;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void animationXFrame(image* img, int xFrame, float count, CALLBACKFUNCTION cbFunction);
	void animationYFrame(image* img, int yFrame, float count, CALLBACKFUNCTION cbFunction);

	frameAnimationManager();
	~frameAnimationManager();
};

