#pragma once

#include "singletonBase.h"

class effect;

class effectManager : public singletonBase<effectManager>
{
private:
	typedef vector<effect*> arrEffects;
	typedef vector<effect*>::iterator iterEffects;
	typedef map<string, arrEffects> arrEffect;
	typedef map<string, arrEffects>::iterator iterEffect;

	arrEffect _mTotalEffect;


public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void addEffect(string effectName, const char* imageName,
		int imageWidth, int imageHeight, int effectWidth, int effectHeight,
		int fps, int buffer);

	void play(string effectName, int x, int y);

	effectManager();
	virtual ~effectManager();
};

