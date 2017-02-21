#include "stdafx.h"
#include "collision.h"


HRESULT collision::init()
{
	attackCheckTime = TIMEMANAGER->getWorldTime();
	bodyCheckTime = TIMEMANAGER->getWorldTime();
	itemCheckTime = TIMEMANAGER->getWorldTime();
	shakeTime = 0;

	SOUNDMANAGER->addSound("item1", "SOUND/item.wav", false, false);
	SOUNDMANAGER->addSound("item2", "SOUND/item2.wav", false, false);
	SOUNDMANAGER->addSound("bell", "SOUND/bell.wav", false, false);
	return S_OK;
}

void collision::release()
{
}

void collision::update(player* PL, vector<enemy*> VE, vector<attack*> VA, vector<item*> VI)
{
	screenShake();
	_player = PL;
	vector<enemy*> _vEnemy = VE;
	vector<attack*> _vAttack = VA;
	vector<item*> _vItem = VI;

	//���̺��� ���� �浹�� �����ϱ� ���� ��ġ
	if (DATABASE->getSaveTime() + 0.5f < TIMEMANAGER->getWorldTime())
	{
		DATABASE->setCanSave(true);
		DATABASE->setSaveTime(TIMEMANAGER->getWorldTime());
	}

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
						&& !(*_viAttack)->getCheckCollision() && (*_viEnemy)->getEnemyAlive())
					{
						shakeTime = TIMEMANAGER->getWorldTime();
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
			//�����۰� �÷��̾ �浹�Ѵٸ� , �������� �̹� �浹�� ���°� �ƴ϶��
			if (IntersectRect(&RectMake(0, 0, 0, 0), &_player->getPlayerRect(), &(*_viItem)->getItemRect()) &&
				!((*_viItem)->getItemCollision()))
			{
				switch ((*_viItem)->getItemType())
				{
					//ü�� ȸ�� �����۰� �浹 ���� ��
				case ITEM_HEART: 
					(*_viItem)->setItemCollision();
					_player->addPlayerHP(3);
					SOUNDMANAGER->playSound("item1", PointMake(0, 0));
					break;
					//������ ȸ�� �����۰� �浹 ���� ��
				case ITEM_SHURIKEN: 
					(*_viItem)->setItemCollision();
					_player->addPlayerMP(5);
					SOUNDMANAGER->playSound("item2", PointMake(0, 0));
					break;
				case ITEM_SAVEBELL:
					if (DATABASE->getCanSave())
					{
						DATABASE->setCanSave(false);
						DATABASE->saveDataToFile();
						SOUNDMANAGER->playSound("bell", PointMake(0, 0));
					}
					break;
				}
			}
			//�����۰� �÷��̾��� �浹�� ó���Ѵ�.
			//�����ۿ� �Ӽ� �Ѱ��� �е� Ư���� �ൿ�� ó���Ѵٸ� �Ӽ����� �����Ѵ�.
			//�Ӽ����� Ȯ���ѵ� �浹�� ó������ �ߺ��浹�� �����Ѵ�.
		}
	}
}

void collision::render()
{
}

void collision::screenShake()
{
	int shakeCount = (TIMEMANAGER->getWorldTime() - shakeTime) / 0.025f;

	//x��ǥ�� ���� ���� ����.
	switch (shakeCount)
	{
	case 1:	DATABASE->setDestCamX(WINSIZEX / 2 - TILESIZE); 
		DATABASE->setDestCamY(WINSIZEY - 150);
		break;
	case 2:	DATABASE->setDestCamX(WINSIZEX / 2); 
		DATABASE->setDestCamY(WINSIZEY - 200);
		break;
	case 3:	DATABASE->setDestCamX(WINSIZEX / 2 + TILESIZE); 
		DATABASE->setDestCamY(WINSIZEY - 150);
		break;
	case 4:	DATABASE->setDestCamX(WINSIZEX / 2); 
		DATABASE->setDestCamY(WINSIZEY - 100);
		break;
	case 5:	DATABASE->setDestCamX(WINSIZEX / 2 - TILESIZE);
		DATABASE->setDestCamY(WINSIZEY - 150);
		break;
	case 6:	DATABASE->setDestCamX(WINSIZEX / 2);
		DATABASE->setDestCamY(WINSIZEY - 200);
		break;
	case 7:	DATABASE->setDestCamX(WINSIZEX / 2 + TILESIZE);
		DATABASE->setDestCamY(WINSIZEY - 150);
		break;
	case 8:	DATABASE->setDestCamX(WINSIZEX / 2);
		DATABASE->setDestCamY(WINSIZEY - 100);
		break;
	default: DATABASE->setDestCamX(WINSIZEX / 2); 
		DATABASE->setDestCamY(WINSIZEY - 150);
		break;
	}
}

collision::collision()
{
}


collision::~collision()
{
}
