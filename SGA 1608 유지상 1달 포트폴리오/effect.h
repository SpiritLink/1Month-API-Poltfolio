#pragma once

#include "gameNode.h"

class image;
class animation;

class effect : public gameNode
{
protected:
	int			_x;				//����Ʈ ��ġ
	int			_y;				//����Ʈ ��ġ

	image*		_image;			//����Ʈ �̹���
	animation*	_animation;		//����Ʈ �ִϸ��̼�
	bool		_isRunning;		//�������̳�?

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

