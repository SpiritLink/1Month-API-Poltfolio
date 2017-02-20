#include "stdafx.h"
#include "collision.h"


HRESULT collision::init()
{
	attackCheckTime = TIMEMANAGER->getWorldTime();
	bodyCheckTime = TIMEMANAGER->getWorldTime();
	itemCheckTime = TIMEMANAGER->getWorldTime();
	return S_OK;
}

void collision::release()
{
}

void collision::update(player* PL, vector<enemy*> VE, vector<attack*> VA, vector<item*> VI)
{
	_player = PL;
	vector<enemy*> _vEnemy = VE;
	vector<attack*> _vAttack = VA;
	vector<item*> _vItem = VI;

	//->아이템과 플레이어가 충돌하면 특정 행동을 하도록 처리

	//공격과 플레이어 , 몬스터 충돌을 처리하고 있다.
	if (attackCheckTime + ATTACKCHECKTIME < TIMEMANAGER->getWorldTime())
	{
		attackCheckTime = TIMEMANAGER->getWorldTime();

		for (_viAttack = _vAttack.begin(); _viAttack != _vAttack.end(); ++_viAttack)
		{
			switch ((*_viAttack)->getAttackType())
			{
			case ATTACK_PLAYER_SLASH_LEFT:
			case ATTACK_PLAYER_SLASH_RIGHT:
			case ATTACK_PLAYER_THROW_LEFT:
			case ATTACK_PLAYER_THROW_RIGHT:
				//플레이어 공격과 적이 충돌하면
				for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
				{
					if (IntersectRect(&RectMake(0, 0, 0, 0), &(*_viAttack)->getAttackRect(), &(*_viEnemy)->getEnemyRect())
						&& !(*_viAttack)->getCheckCollision())
					{
						SOUNDMANAGER->playSound("hit", PointMake((*_viAttack)->getAttackX(), (*_viAttack)->getAttackY()));
						(*_viAttack)->collisionTrue();
						(*_viAttack)->setFrameCountZero();
						(*_viEnemy)->addEnemyHP(-1);
					}
				}
				break;
			case ATTACK_ERI_WAVE_RIGHT:
			case ATTACK_ERI_WAVE_LEFT:
			case ATTACK_ERI_KNIVES:
				//적 공격과 플레이어가 충돌하면
				if (IntersectRect(&RectMake(0, 0, 0, 0), &(*_viAttack)->getAttackRect(), &_player->getPlayerRect()))
				{
					_player->setPlayerHit(2.0f);
					(*_viAttack)->collisionTrue();
				}
				break;
			}
		}
	}

	//플레이어와 몬스터간 충돌을 처리하고 있다.
	if (bodyCheckTime + BODYCHECKTIME < TIMEMANAGER->getWorldTime())
	{
		bodyCheckTime = TIMEMANAGER->getWorldTime();

		for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
		{
			//모든 적과 플레이어가 충돌하면(단 적이 살아있을때)
			if (IntersectRect(&RectMake(0, 0, 0, 0), &_player->getPlayerRect(), &(*_viEnemy)->getEnemyRect()) &&
				(*_viEnemy)->getEnemyAlive())
			{
				_player->setPlayerHit(2.0f);
			}
		}
	}

	if (itemCheckTime + ITEMCHECKTIME < TIMEMANAGER->getWorldTime())
	{
		itemCheckTime = TIMEMANAGER->getWorldTime();

		for (_viItem = _vItem.begin(); _viItem != _vItem.end(); ++_viItem)
		{
			//아이템과 플레이어의 충돌을 처리한다.
			//아이템에 속성 한개를 둔뒤 특별한 행동을 처리한다면 속성값을 변경한다.
			//속성값을 확인한뒤 충돌을 처리시켜 중복충돌을 방지한다.
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
