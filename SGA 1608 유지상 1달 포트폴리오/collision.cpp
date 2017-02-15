#include "stdafx.h"
#include "collision.h"


HRESULT collision::init()
{
	currentTime = TIMEMANAGER->getWorldTime();
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

	if (currentTime + 0.05f < TIMEMANAGER->getWorldTime())
	{
		currentTime = TIMEMANAGER->getWorldTime();

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
					if (IntersectRect(&RectMake(0, 0, 0, 0), &(*_viAttack)->getAttackRect(), &(*_viEnemy)->getEnemyRect()))
					{
						SOUNDMANAGER->playSound("hit", PointMake((*_viAttack)->getAttackX(), (*_viAttack)->getAttackY()));
						if (!(*_viAttack)->getCheckCollision())
						{
							(*_viAttack)->collisionTrue();
							(*_viAttack)->setFrameCountZero();
						}
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

		for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
		{
			//모든 적과 플레이어가 충돌하면
			if (IntersectRect(&RectMake(0, 0, 0, 0), &_player->getPlayerRect(), &(*_viEnemy)->getEnemyRect()))
			{
				_player->setPlayerHit(2.0f);
			}
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
