#pragma once

#include "gameNode.h"

typedef void(*CALLBACKFUNCTION) (void);

class action : public gameNode
{
private:
	image* _image;
	float _startX, _startY;
	float _endX, _endY;
	float _angle;
	float _count;
	float _travelRange;
	float _worldTimeCount;
	float _time;

	bool _isMoving;

	CALLBACKFUNCTION _callbackFunction;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void moveTo(image* img, float endX, float endY, float time);
	virtual void moveTo(image* img, float endX, float endY, float time,
		CALLBACKFUNCTION cbFunction);
	virtual void moving();

	bool getIsMoving() { return _isMoving; }

	action();
	~action();
};

