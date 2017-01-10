#include "stdafx.h"
#include "effect.h"
#include "image.h"
#include "animation.h"


effect::effect()
	:_image(NULL)
	, _animation(NULL)
	, _isRunning(false)
	, _x(0)
	, _y(0)
{
}


effect::~effect()
{
}

HRESULT effect::init(image* img, int frameW, int frameH, int fps)
{
	if (!img) return E_FAIL;

	_isRunning = false;

	_image = img;

	if (!_animation) _animation = new animation;

	_animation->init(_image->getWidth(), _image->getHeight(), frameW, frameH);
	_animation->setDefPlayFrame(false, false);
	_animation->setFPS(fps);
	_animation->stop();

	return S_OK;
}

void effect::release()
{
	_image = NULL;
	_animation->release();
	SAFE_DELETE(_animation);
}

void effect::update(float elapsedTime)
{
	//활성화 되어있지 않으면 실행 불가
	if (!_isRunning) return;

	_animation->frameUpdate(elapsedTime);

	//애니메이션이 종료 되었으면 정지한다.
	if (!_animation->isPlay()) stop();
}

void effect::render()
{
	if (!_isRunning) return;

	_image->aniRender(getMemDC(), _x, _y, _animation);
}

void effect::start(int x, int y)
{
	if (!_image || !_animation) return;

	_x = x - (_animation->getFrameWidth() / 2);
	_y = y - (_animation->getFrameHeight() / 2);

	_isRunning = true;
	_animation->start();
}

void effect::stop()
{
	_isRunning = false;
}
