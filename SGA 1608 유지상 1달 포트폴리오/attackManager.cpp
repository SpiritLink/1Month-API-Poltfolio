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
	for (_viAttack = _vAttack.begin(); _viAttack != _vAttack.end();)			//모든 공격을 확인한다.
	{
		if ((*_viAttack)->getCheckCollision() == true)						//이미 한번 충돌된 공격이라면
		{
			(*_viAttack)->release();
			_viAttack = _vAttack.erase(_viAttack);								//공격을 삭제한다.
		}
		else
		{
			(*_viAttack)->update();
			++_viAttack;														//아니라면 다음 공격 확인
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
		if ((*_viAttack)->getAttackType() == ATTACK_PLAYER_SLASH_LEFT) continue;	//기본좌공격은 좌표를 옮기지 않는다.
		if ((*_viAttack)->getAttackType() == ATTACK_PLAYER_SLASH_RIGHT) continue;	//기본우공격은 좌표를 옮기지 않는다.

		(*_viAttack)->addX(value);
	}
}

void attackManager::moveAttackY(int value)
{
	for (_viAttack = _vAttack.begin(); _viAttack != _vAttack.end(); ++_viAttack)
	{
		if ((*_viAttack)->getAttackType() == ATTACK_PLAYER_SLASH_LEFT) continue;	//기본좌공격은 좌표를 옮기지 않는다.
		if ((*_viAttack)->getAttackType() == ATTACK_PLAYER_SLASH_RIGHT) continue;	//기본우공격은 좌표를 옮기지 않는다.

		(*_viAttack)->addY(value);
	}
}

void attackManager::playerSlashAttack(float inputX, float inputY, DIRECTION Dir)
{
	attack* Attack;
	Attack = new playerSlash;
	Attack->init(inputX, inputY);
	switch (Dir)
	{
	case LEFT:		Attack->setAttackType(ATTACK_PLAYER_SLASH_LEFT); break;
	case RIGHT:		Attack->setAttackType(ATTACK_PLAYER_SLASH_RIGHT); break;
	}
	_vAttack.push_back(Attack);
}

void attackManager::playerThrowAttack(float inputX, float inputY, DIRECTION Dir)
{
	attack* Attack;
	Attack = new playerThrow;
	Attack->init(inputX, inputY);
	switch (Dir)
	{
	case LEFT: Attack->setAttackType(ATTACK_PLAYER_THROW_LEFT); break;
	case RIGHT: Attack->setAttackType(ATTACK_PLAYER_THROW_RIGHT); break;
	}
	_vAttack.push_back(Attack);
}

void attackManager::eriWaveAttack(float inputX, float inputY, DIRECTION Dir)
{
	attack* Attack;
	Attack = new eriWave;
	Attack->init(inputX, inputY);
	switch (Dir)
	{
	case LEFT: Attack->setAttackType(ATTACK_ERI_WAVE_LEFT); break;
	case RIGHT: Attack->setAttackType(ATTACK_ERI_WAVE_RIGHT); break;
	}
	_vAttack.push_back(Attack);
}

void attackManager::eriKnivesAttack(float inputX, float inputY, DIRECTION Dir)
{
	attack* Attack1;
	attack* Attack2;

	Attack1 = new eriKnives;
	Attack2 = new eriKnives;

	switch (Dir)
	{
	case LEFT:
		Attack1->init(inputX, inputY);
		Attack1->setAngle(PI);
		Attack1->setAttackType(ATTACK_ERI_KNIVES);

		Attack2->init(inputX, inputY);
		Attack2->setAngle(PI - PI / 6.0f);
		Attack2->setAttackType(ATTACK_ERI_KNIVES);
		break;
	case RIGHT:
		Attack1->init(inputX, inputY);
		Attack1->setAngle(0);
		Attack1->setAttackType(ATTACK_ERI_KNIVES);

		Attack2->init(inputX, inputY);
		Attack2->setAngle((2.0f * PI) - (PI / 6.0f));
		Attack2->setAttackType(ATTACK_ERI_KNIVES);
		break;
	}

	_vAttack.push_back(Attack1);
	_vAttack.push_back(Attack2);

	
}

attackManager::attackManager()
{
}


attackManager::~attackManager()
{
}
