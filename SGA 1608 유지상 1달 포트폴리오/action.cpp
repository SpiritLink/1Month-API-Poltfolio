#include "stdafx.h"
#include "action.h"

action::action()
	:_callbackFunction(NULL)
{
}


action::~action()
{
}

HRESULT action::init()
{
	_worldTimeCount = 0.0f;
	_count = 0.0f;
	_isMoving = false;

	return S_OK;
}

void action::release()
{
	_callbackFunction = NULL;
}

void action::update()
{

	moving();

}

void action::render()
{

}

void action::moveTo(image * img, float endX, float endY, float time)
{
	if (_isMoving) return;

	_image = img;

	_startX = _image->getX();
	_startY = _image->getY();

	_endX = endX;
	_endY = endY;

	_travelRange = getDistance(_startX, _startY, _endX, _endY);

	_angle = getAngle(_startX, _startY, _endX, _endY);

	_worldTimeCount = TIMEMANAGER->getWorldTime();

	_time = time;

	_isMoving = true;

}

void action::moveTo(image * img, float endX, float endY, float time, CALLBACKFUNCTION cbFunction)
{
	if (_isMoving) return;

	_callbackFunction = static_cast<CALLBACKFUNCTION>(cbFunction);

	moveTo(img, endX, endY, time);
}

void action::moving()
{
	if (!_isMoving) return;

	float elpasedTime = TIMEMANAGER->getElapsedTime();
	float moveSpeed = (elpasedTime / _time) * _travelRange;

	_image->setX(_image->getX() + cosf(_angle) * moveSpeed);
	_image->setY(_image->getY() + (-sinf(_angle) * moveSpeed));

	if (_time + _worldTimeCount <= TIMEMANAGER->getWorldTime())
	{
		_worldTimeCount = TIMEMANAGER->getWorldTime();
		_image->setX(_endX);
		_image->setY(_endY);
		_isMoving = false;

		if (_callbackFunction != NULL) _callbackFunction();
	}

}


