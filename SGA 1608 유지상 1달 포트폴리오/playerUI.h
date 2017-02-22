#pragma once

#include "gameNode.h"

class playerUI : public gameNode
{
private:
	image* _hpFrame;
	image* _sealFrame;
	image* _hpIMG;
	image* _heart;
	image* _number;
	int HP;
	int MP;

	image* _menuButton;
	image* _menuButton2;
	image* _restartButton;
	image* _restartButton2;
	image* _gameOver;
	float currentTime;

	int alphaValue;
	int menuSelect;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	playerUI();
	virtual ~playerUI();
};

