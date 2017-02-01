#include "stdafx.h"
#include "attackManager.h"


HRESULT attackManager::init()
{
	return S_OK;
}

void attackManager::release()
{
}

void attackManager::update()
{
	for (_viAttack = _vAttack.begin(); _viAttack != _vAttack.end(); ++_viAttack)
	{
		(*_viAttack)->update();
	}
}

void attackManager::render()
{
	for (_viAttack = _vAttack.begin(); _viAttack != _vAttack.end(); ++_viAttack)
	{
		(*_viAttack)->render();
	}
}

void attackManager::playerAttack(float inputX, float inputY)
{
	attack* Attack;
	Attack = new playerSlash;
	Attack->init(inputX, inputY);
	_vAttack.push_back(Attack);
}

attackManager::attackManager()
{
}


attackManager::~attackManager()
{
}
