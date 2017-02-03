#pragma once

#include "gameNode.h"

class playerUI : public gameNode
{
private:
	image* _hpIMG;
	image* _heart;
	int HP;
	int MP;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	playerUI();
	virtual ~playerUI();
};

