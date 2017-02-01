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

	for (_viAttack = _vAttack.begin(); _viAttack != _vAttack.end();)
	{
		if ((*_viAttack)->getInputTime() + 0.25f < TIMEMANAGER->getWorldTime())
		{
			(*_viAttack)->release();
			_viAttack = _vAttack.erase(_viAttack);
		}
		else
		{
			++_viAttack;
		}
	}
}

void attackManager::render()
{
	for (_viAttack = _vAttack.begin(); _viAttack != _vAttack.end(); ++_viAttack)
	{
		(*_viAttack)->render();
	}
}

void attackManager::moveAttackX(int value)
{
	for (_viAttack = _vAttack.begin(); _viAttack != _vAttack.end(); ++_viAttack)
	{
		(*_viAttack)->addX(value);
	}
}

void attackManager::moveAttackY(int value)
{
	for (_viAttack = _vAttack.begin(); _viAttack != _vAttack.end(); ++_viAttack)
	{
		(*_viAttack)->addY(value);
	}
}

void attackManager::playerAttack(float inputX, float inputY, DIRECTION Dir)
{
	attack* Attack;
	Attack = new playerSlash;
	Attack->init(inputX, inputY);
	switch (Dir)
	{
	case LEFT:
		Attack->setAttackType(ATTACK_PLAYER_SLASH_LEFT); break;
	case RIGHT:
		Attack->setAttackType(ATTACK_PLAYER_SLASH_RIGHT); break;
	}
	_vAttack.push_back(Attack);
}

attackManager::attackManager()
{
}


attackManager::~attackManager()
{
}
