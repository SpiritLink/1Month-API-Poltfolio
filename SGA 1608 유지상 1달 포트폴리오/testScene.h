#pragma once

#include "gameNode.h"

class testScene : public gameNode
{
private:
	image* _image;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	
	testScene();
	virtual ~testScene();
};

