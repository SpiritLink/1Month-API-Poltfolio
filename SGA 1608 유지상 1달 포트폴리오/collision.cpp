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
		//��� ���ݰ� �÷��̾ �浹�ϸ�
		if (IntersectRect(&RectMake(0, 0, 0, 0), &(*_viAttack)->getAttackRect(), &_player->getPlayerRect()))
		{

		}

		//��� ���ݰ� ��� ���� �浹�ϸ�
		for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
		{
			if (IntersectRect(&RectMake(0, 0, 0, 0), &(*_viAttack)->getAttackRect(), &_player->getPlayerRect()))
			{

			}
		}
	}

	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		//��� ���� �÷��̾ �浹�ϸ�
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
