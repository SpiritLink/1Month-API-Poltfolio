#include "stdafx.h"
#include "button.h"


button::button()
	:_callbackFunction(NULL)
{
}


button::~button()
{
}

HRESULT button::init(const char* imageName, float x, float y,
	POINT btnDownFramePoint, POINT btnUpFramePoint)
{
	_dir = BUTTONDIR_NULL;

	_x = x;
	_y = y;

	_btnDownFramePoint = btnDownFramePoint;
	_btnUpFramePoint = btnUpFramePoint;

	_imageName = imageName;
	_image = IMAGEMANAGER->findImage(imageName);

	_rc = RectMakeCenter(x, y, _image->getFrameWidth(), _image->getFrameHeight());

	return S_OK;
}

HRESULT button::init(const char* imageName, float x, float y,
	POINT btnDownFramePoint, POINT btnUpFramePoint, CALLBACKFUNCTION cbFunction)
{
	_callbackFunction = cbFunction;

	this->init(imageName, x, y,
		btnDownFramePoint, btnUpFramePoint);

	return S_OK;
}

void button::release()
{

}

void button::update()
{
	if (PtInRect(&_rc, _ptMouse))
	{
		if (_leftButtonDown)
		{
			_dir = BUTTONDIR_DOWN;
		}
		else if (!_leftButtonDown && _dir == BUTTONDIR_DOWN)
		{
			_dir = BUTTONDIR_UP;
			if (_callbackFunction != NULL) _callbackFunction();
		}
	}
	else _dir = BUTTONDIR_NULL;
}

void button::render()
{
	switch (_dir)
	{
	case BUTTONDIR_NULL: case BUTTONDIR_UP:
		_image->frameRender(getMemDC(), _rc.left, _rc.top, _btnUpFramePoint.x, _btnUpFramePoint.y);
		break;

	case BUTTONDIR_DOWN:
		_image->frameRender(getMemDC(), _rc.left, _rc.top, _btnDownFramePoint.x, _btnDownFramePoint.y);
		break;

	}
}
