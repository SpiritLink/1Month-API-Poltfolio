#pragma once

#include "gameNode.h"

typedef void(*CALLBACKFUNCTION)();

enum BUTTONDIR
{
	BUTTONDIR_NULL,
	BUTTONDIR_UP,
	BUTTONDIR_DOWN,
	BUTTONDIR_END
};

class button : public gameNode
{
private:
	BUTTONDIR _dir;
	const char* _imageName;
	image* _image;

	RECT _rc;
	float _x, _y;

	POINT _btnDownFramePoint;
	POINT _btnUpFramePoint;

	CALLBACKFUNCTION _callbackFunction;

public:
	virtual HRESULT init(const char* imageName, float x, float y,
		POINT btnDownFramePoint, POINT btnUpFramePoint);
	virtual HRESULT init(const char* imageName, float x, float y,
		POINT btnDownFramePoint, POINT btnUpFramePoint, CALLBACKFUNCTION cbFunction);
	virtual void release();
	virtual void update();
	virtual void render();

	button();
	virtual ~button();
};

