#pragma once

#include "gameNode.h"
#include "attack.h"

class attackManager : public gameNode
{
private:
	vector<attack*>				_vAttack;
	vector<attack*>::iterator	_viAttack;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	
	void playerAttack(float inputX, float inputY);
	attackManager();
	virtual ~attackManager();
};

