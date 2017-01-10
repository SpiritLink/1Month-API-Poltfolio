#pragma once

#include "gameNode.h"

#define DEFAULT_STR 1
#define DEFAULT_DEF 1
class player : public gameNode
{
private:
	float x;
	float y;
	RECT PlayerRect;

	int ATK;
	int STR;
	int DEF;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void keyboardInput();

	player();
	virtual ~player();
};

