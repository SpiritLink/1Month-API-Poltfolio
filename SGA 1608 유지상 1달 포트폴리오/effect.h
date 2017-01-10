#pragma once

#include "gameNode.h"

class image;
class animation;

class effect : public gameNode
{
protected:
	int			_x;				//이펙트 위치
	int			_y;				//이펙트 위치

	image*		_image;			//이펙트 이미지
	animation*	_animation;		//이펙트 애니메이션
	bool		_isRunning;		//실행중이냐?

public:
	virtual HRESULT init(image* img, int frameW, int frameH, int fps);
	virtual void release();
	virtual void update(float elapsedTime);
	virtual void render();

	virtual void start(int x, int y);
	virtual void stop();

	bool getIsRunning() { return _isRunning; }

	effect();
	virtual ~effect();
};

