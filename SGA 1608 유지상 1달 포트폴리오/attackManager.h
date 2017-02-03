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
	
	void moveAttackX(int value);
	void moveAttackY(int value);

	void playerSlashAttack(float inputX, float inputY, DIRECTION Dir);
	void playerThrowAttack(float inputX, float inputY, DIRECTION Dir);
	void eriWaveAttack(float inputX, float inputY, DIRECTION Dir);
	void eriKnivesAttack(float inputX, float inputY, DIRECTION Dir);
	attackManager();
	virtual ~attackManager();
};

