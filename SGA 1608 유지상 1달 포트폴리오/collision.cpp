#include "stdafx.h"
#include "collision.h"


HRESULT collision::init()
{
	return S_OK;
}

void collision::release()
{
}

void collision::update(player* PL, vector<enemy*> VE, vector<attack*> VA)
{
	_player = PL;
	vector<enemy*> _vEnemy = VE;
	vector<attack*> _vAttack = VA;
	for (_viAttack = _vAttack.begin(); _viAttack != _vAttack.end(); ++_viAttack)
	{
		//모든 공격과 플레이어가 충돌하면
		if (IntersectRect(&RectMake(0, 0, 0, 0), &(*_viAttack)->getAttackRect(), &_player->getPlayerRect()))
		{

		}

		//모든 공격과 모든 적이 충돌하면
		for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
		{
			if (IntersectRect(&RectMake(0, 0, 0, 0), &(*_viAttack)->getAttackRect(), &_player->getPlayerRect()))
			{

			}
		}
	}

	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		//모든 적과 플레이어가 충돌하면
		if (IntersectRect(&RectMake(0, 0, 0, 0), &_player->getPlayerRect(), &(*_viEnemy)->getEnemyRect()))
		{

		}
	}
}

void collision::render()
{
}

collision::collision()
{
}


collision::~collision()
{
}
