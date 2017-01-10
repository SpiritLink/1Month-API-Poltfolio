#pragma once

#include "gameNode.h"
#include "image.h"

typedef void(*CALLBACKFUNCTION)(void);

enum ANIMATIONDIRECTION
{
	ANIMATIONDIRECTION_NULL,
	ANIMATIONDIRECTION_X,
	ANIMATIONDIRECTION_Y
};

class frameAnimation :public gameNode
{
private:

	ANIMATIONDIRECTION _ad;

	image* _image;
	float _worldTimeCount;
	float _count;
	int _xMaxFrame, _yMaxFrame;
	int _xFrameCount, _yFrameCount;

	bool _isPlay;

	CALLBACKFUNCTION _callbackFunction;


public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void animationXFrame(image* img, int xFrame, float count, CALLBACKFUNCTION cbFunction);
	void animationYFrame(image* img, int yFrame, float count, CALLBACKFUNCTION cbFunction);

	inline bool getIsPlay() { return _isPlay; }

	frameAnimation();
	virtual ~frameAnimation();

};

