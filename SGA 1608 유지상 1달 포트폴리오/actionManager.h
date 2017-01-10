#pragma once

#include "singletonBase.h"

class action;

class actionManager : public singletonBase<actionManager>
{
private:
	typedef vector<action*> arrAction;
	typedef vector<action*>::iterator iterAction;

	arrAction _vAction;
	iterAction _viAction;

public:
	HRESULT init();
	void release();
	void update();

	void moveTo(image* img, float endX, float endY, float time);
	void moveTo(image* img, float endX, float endY, float time, void* cbFunction);

	actionManager();
	~actionManager();
};

