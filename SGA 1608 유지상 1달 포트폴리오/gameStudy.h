#pragma once

#include "gameNode.h"


//��ó��------------------------------------



//-----------------------------------------

class gameStudy : public gameNode
{
private:
	//����-----------------------------------

	image* _whiteBackground;
	//--------------------------------------

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	//�Լ�------------------------------------



	//---------------------------------------

	gameStudy();
	virtual ~gameStudy();
};

