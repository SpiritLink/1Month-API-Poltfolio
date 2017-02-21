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

	//세이브의 무한 충돌을 방지하기 위한 장치
	if (DATABASE->getSaveTime() + 0.5f < TIMEMANAGER->getWorldTime())
	{
		DATABASE->setCanSave(true);
		DATABASE->setSaveTime(TIMEMANAGER->getWorldTime());
	}

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
			//아이템과 플레이어가 충돌한다면 , 아이템이 이미 충돌한 상태가 아니라면
			if (IntersectRect(&RectMake(0, 0, 0, 0), &_player->getPlayerRect(), &(*_viItem)->getItemRect()) &&
				!((*_viItem)->getItemCollision()))
			{
				switch ((*_viItem)->getItemType())
				{
					//체력 회복 아이템과 충돌 했을 때
				case ITEM_HEART: 
					(*_viItem)->setItemCollision();
					_player->addPlayerHP(3);
					SOUNDMANAGER->playSound("item1", PointMake(0, 0));
					break;
					//수리검 회복 아이템과 충돌 했을 때
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
			//아이템과 플레이어의 충돌을 처리한다.
			//아이템에 속성 한개를 둔뒤 특별한 행동을 처리한다면 속성값을 변경한다.
			//속성값을 확인한뒤 충돌을 처리시켜 중복충돌을 방지한다.
		}
	}
}

void collision::render()
{
}

void collision::screenShake()
{
	int shakeCount = (TIMEMANAGER->getWorldTime() - shakeTime) / 0.025f;

	//x좌표만 먼저 흔들어 보자.
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
