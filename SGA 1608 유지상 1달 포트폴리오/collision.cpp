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

	//->�����۰� �÷��̾ �浹�ϸ� Ư�� �ൿ�� �ϵ��� ó��

	//���ݰ� �÷��̾� , ���� �浹�� ó���ϰ� �ִ�.
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
				//�÷��̾� ���ݰ� ���� �浹�ϸ�
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
				//�� ���ݰ� �÷��̾ �浹�ϸ�
				if (IntersectRect(&RectMake(0, 0, 0, 0), &(*_viAttack)->getAttackRect(), &_player->getPlayerRect()))
				{
					_player->setPlayerHit(2.0f);
					(*_viAttack)->collisionTrue();
				}
				break;
			}
		}
	}

	//�÷��̾�� ���Ͱ� �浹�� ó���ϰ� �ִ�.
	if (bodyCheckTime + BODYCHECKTIME < TIMEMANAGER->getWorldTime())
	{
		bodyCheckTime = TIMEMANAGER->getWorldTime();

		for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
		{
			//��� ���� �÷��̾ �浹�ϸ�(�� ���� ���������)
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
			//�����۰� �÷��̾��� �浹�� ó���Ѵ�.
			//�����ۿ� �Ӽ� �Ѱ��� �е� Ư���� �ൿ�� ó���Ѵٸ� �Ӽ����� �����Ѵ�.
			//�Ӽ����� Ȯ���ѵ� �浹�� ó������ �ߺ��浹�� �����Ѵ�.
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
