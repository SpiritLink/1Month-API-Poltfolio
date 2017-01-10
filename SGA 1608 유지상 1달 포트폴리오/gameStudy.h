#pragma once

#include "gameNode.h"


//전처리------------------------------------



//-----------------------------------------

class gameStudy : public gameNode
{
private:
	//변수-----------------------------------


	//--------------------------------------

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	//함수------------------------------------



	//---------------------------------------

	gameStudy();
	virtual ~gameStudy();
};

