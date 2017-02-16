#include "stdafx.h"
#include "ingameScene.h"


HRESULT ingameScene::init()
{
	return S_OK;
}

void ingameScene::release()
{
}

void ingameScene::update()
{
}

void ingameScene::render()
{
}

ingameScene::ingameScene()
{
}

ingameScene::~ingameScene()
{
}

HRESULT townScene::init()
{
	DATABASE->setBaseTime(TIMEMANAGER->getWorldTime());
	DATABASE->setDestCamX(WINSIZEX / 2);
	DATABASE->setDestCamY(WINSIZEY / 2);
	IMAGEMANAGER->addFrameImage("tileMap", "IMAGE/tile/tile.bmp", 0, 0, 1350, 1200, SAMPLETILEX, SAMPLETILEY, true, RGB(0, 0, 0));

	_tileMap = new tileMap;
	_tileMap->init("DATA/MAP/Town.map");

	_attackManager = new attackManager;
	_attackManager->init();

	_enemyManager = new enemyManager;
	_enemyManager->init(_tileMap, _attackManager);
	_player = new player;
	_player->init();
	_player->setTileMapMemoryAddress(_tileMap);
	_player->setPlayerTilePosition(20557);
	_player->setAttackManagerMemoryAddress(_attackManager);
	_player->firstCollisionTileCheck();

	_playerUI = new playerUI;
	_playerUI->init();

	_collision = new collision;
	_collision->init();

	_backIMG = IMAGEMANAGER->addImage("�׽�Ʈ���", "IMAGE/test.bmp", TILESIZEX, TILESIZEY, false, RGB(0, 0, 0));
	Background = RectMake(0, 0, TILESIZEX, TILESIZEY);


	_enemyManager->setBomb(21548);
	_enemyManager->setBomb(21549);
	_enemyManager->setBomb(21550);
	_enemyManager->setBomb(21551);
	_enemyManager->setBomb(21552);

	_enemyManager->setFlower(21101);

	_player->update();
	cameraInit();//ī�޶��� ��ġ�� �����մϴ�.
	return S_OK;
}

void townScene::release()
{
	_player->release();
	SAFE_DELETE(_player);

	_tileMap->release();
	SAFE_DELETE(_tileMap);

	_playerUI->release();
	SAFE_DELETE(_playerUI);

	_attackManager->release();
	SAFE_DELETE(_attackManager);

	_enemyManager->release();
	SAFE_DELETE(_enemyManager);

	_collision->release();
	SAFE_DELETE(_collision);
}

void townScene::update()
{
	_player->update();
	_playerUI->update();
	_tileMap->update();
	_attackManager->update();
	_enemyManager->update();
	_collision->update(_player, _enemyManager->getEnemyVector(), _attackManager->getAttackVector());
	cameraMove();
}

void townScene::render()
{
	_tileMap->render();
	_enemyManager->render();
	_player->render();
	_attackManager->render();
	_playerUI->render();
}

void townScene::cameraMove()
{
	//����� ��ǻ� ������ �ʰ� �ֽ��ϴ�.
	//->�Ҽ��� ���� ���� �ݿø��� ���� ��ǥ�� ��߳� �ٸ� ������� ��ü��
	float angle = getAngle(DATABASE->getDestCamX(), DATABASE->getDestCamY(), DATABASE->getSourCamX(), DATABASE->getSourCamY());
	int distanceX = getDistance(DATABASE->getDestCamX(), 0, DATABASE->getSourCamX(), 0);
	int distanceY = getDistance(0, DATABASE->getDestCamY(), 0, DATABASE->getSourCamY());


	//���� ȭ���� ����ٸ�
	if (Background.right < WINSIZEX)
	{
		int diffrence = WINSIZEX - Background.right;
		Background.right += diffrence;	//����� �����̴� ������ ����
		Background.left += diffrence;	//����� �����̴� ������ ����
		_tileMap->moveTileX(diffrence);
		_player->addPlayerX(-diffrence);//�÷��̾��� �����̴� ������ ����
		_enemyManager->addEnemyX(diffrence);
	}
	if (Background.left > 0)
	{
		int diffrence = Background.left;
		Background.right -= diffrence;
		Background.left -= diffrence;
		_player->addPlayerX(+diffrence);
		_tileMap->moveTileX(-diffrence);
		_enemyManager->addEnemyX(-diffrence);
	}
	if (Background.top > 0)
	{
		int diffrence = Background.top;
		Background.top -= diffrence;
		Background.bottom -= diffrence;
		_player->addPlayerY(diffrence);
		_tileMap->moveTileY(-diffrence);
		_enemyManager->addEnemyY(-diffrence);
	}

	if (Background.bottom < WINSIZEY)
	{
		int diffrence = WINSIZEY - Background.bottom;
		Background.top += diffrence;
		Background.bottom += diffrence;
		_player->addPlayerY(-diffrence);
		_tileMap->moveTileY(+diffrence);
		_enemyManager->addEnemyY(diffrence);
	}

	//X��ǥ �̵�
	if (DATABASE->getSourCamX() > DATABASE->getDestCamX())		//ȭ�� ���������� �����϶�
	{
		Background.left -= distanceX / 10;
		Background.right -= distanceX / 10;
		_player->addPlayerX(-distanceX / 10);
		_tileMap->moveTileX(-distanceX / 10);
		_attackManager->moveAttackX(-distanceX / 10);
		_enemyManager->addEnemyX(-distanceX / 10);
		DATABASE->addBackgroundCount(-distanceX / 10);
	}

	if (DATABASE->getSourCamX() < DATABASE->getDestCamX())		//ȭ�� �������� �����϶�
	{
		Background.left += distanceX / 10;
		Background.right += distanceX / 10;
		_player->addPlayerX(distanceX / 10);
		_tileMap->moveTileX(distanceX / 10);
		_attackManager->moveAttackX(distanceX / 10);
		_enemyManager->addEnemyX(distanceX / 10);
		DATABASE->addBackgroundCount(distanceX / 10);
	}

	//Y��ǥ �̵�
	if (DATABASE->getSourCamY() > DATABASE->getDestCamY())		//ȭ�� �Ʒ������� �����϶�
	{
		Background.top -= distanceY / 10;
		Background.bottom -= distanceY / 10;
		_player->addPlayerY(-distanceY / 10);
		_tileMap->moveTileY(-distanceY / 10);
		_attackManager->moveAttackY(-distanceY / 10);
		_enemyManager->addEnemyY(-distanceY / 10);
	}

	if (DATABASE->getSourCamY() < DATABASE->getDestCamY())		//ȭ�� �������� �����϶�
	{
		Background.top += distanceY / 10;
		Background.bottom += distanceY / 10;
		_player->addPlayerY(distanceY / 10);
		_tileMap->moveTileY(distanceY / 10);
		_attackManager->moveAttackY(distanceY / 10);
		_enemyManager->addEnemyY(distanceY / 10);
	}
}

void townScene::cameraInit()
{
	//����� ��ǻ� ������ �ʰ� �ֽ��ϴ�.
	//->�Ҽ��� ���� ���� �ݿø��� ���� ��ǥ�� ��߳� �ٸ� ������� ��ü��
	float angle = getAngle(DATABASE->getDestCamX(), DATABASE->getDestCamY(), DATABASE->getSourCamX(), DATABASE->getSourCamY());
	int distanceX = getDistance(DATABASE->getDestCamX(), 0, DATABASE->getSourCamX(), 0);
	int distanceY = getDistance(0, DATABASE->getDestCamY(), 0, DATABASE->getSourCamY());

	//���� ȭ���� ����ٸ�
	if (Background.right < WINSIZEX)
	{
		int diffrence = WINSIZEX - Background.right;
		Background.right += diffrence;	//����� �����̴� ������ ����
		Background.left += diffrence;	//����� �����̴� ������ ����
		_tileMap->moveTileX(diffrence);
		_player->addPlayerX(-diffrence);//�÷��̾��� �����̴� ������ ����
	}
	if (Background.left > 0)
	{
		int diffrence = Background.left;
		Background.right -= diffrence;
		Background.left -= diffrence;
		_player->addPlayerX(+diffrence);
		_tileMap->moveTileX(-diffrence);
	}
	if (Background.top > 0)
	{
		int diffrence = Background.top;
		Background.top -= diffrence;
		Background.bottom -= diffrence;
		_player->addPlayerY(diffrence);
		_tileMap->moveTileY(-diffrence);
	}

	if (Background.bottom < WINSIZEY)
	{
		int diffrence = WINSIZEY - Background.bottom;
		Background.top += diffrence;
		Background.bottom += diffrence;
		_player->addPlayerY(-diffrence);
		_tileMap->moveTileY(+diffrence);
	}

	//X��ǥ �̵�
	if (DATABASE->getSourCamX() > DATABASE->getDestCamX())		//ȭ�� ���������� �����϶�
	{
		Background.left -= distanceX;
		Background.right -= distanceX;
		_player->addPlayerX(-distanceX);
		_tileMap->moveTileX(-distanceX);
		_attackManager->moveAttackX(-distanceX);
		_enemyManager->addEnemyX(-distanceX);
	}

	if (DATABASE->getSourCamX() < DATABASE->getDestCamX())		//ȭ�� �������� �����϶�
	{
		Background.left += distanceX;
		Background.right += distanceX;
		_player->addPlayerX(distanceX);
		_tileMap->moveTileX(distanceX);
		_attackManager->moveAttackX(distanceX);
		_enemyManager->addEnemyX(distanceX);
	}

	//Y��ǥ �̵�
	if (DATABASE->getSourCamY() > DATABASE->getDestCamY())		//ȭ�� �Ʒ������� �����϶�
	{
		Background.top -= distanceY;
		Background.bottom -= distanceY;
		_player->addPlayerY(-distanceY);
		_tileMap->moveTileY(-distanceY);
		_attackManager->moveAttackY(-distanceY);
		_enemyManager->addEnemyY(-distanceY);
	}

	if (DATABASE->getSourCamY() < DATABASE->getDestCamY())		//ȭ�� �������� �����϶�
	{
		Background.top += distanceY;
		Background.bottom += distanceY;
		_player->addPlayerY(distanceY);
		_tileMap->moveTileY(distanceY);
		_attackManager->moveAttackY(distanceY);
		_enemyManager->addEnemyY(distanceY);
	}
}

townScene::townScene()
{

}

townScene::~townScene()
{

}

HRESULT field1Scene::init()
{
	DATABASE->setBaseTime(TIMEMANAGER->getWorldTime());
	DATABASE->setDestCamX(WINSIZEX / 2);
	DATABASE->setDestCamY(WINSIZEY / 2);
	IMAGEMANAGER->addFrameImage("tileMap", "IMAGE/tile/tile.bmp", 0, 0, 1350, 1200, SAMPLETILEX, SAMPLETILEY, true, RGB(0, 0, 0));

	_tileMap = new tileMap;
	_tileMap->init("DATA/MAP/Field1.map");

	_attackManager = new attackManager;
	_attackManager->init();

	_enemyManager = new enemyManager;
	_enemyManager->init(_tileMap, _attackManager);

	_player = new player;
	_player->init();
	_player->setTileMapMemoryAddress(_tileMap);
	_player->setAttackManagerMemoryAddress(_attackManager);
	_player->setPlayerTilePosition(20557);
	_player->firstCollisionTileCheck();

	_playerUI = new playerUI;
	_playerUI->init();

	_collision = new collision;
	_collision->init();

	Background = RectMake(0, 0, TILESIZEX, TILESIZEY);	//�Ӱ迵�� ������ ���ؼ�
	_player->update();
	cameraInit();

	//�� ��ġ (���߿� �Լ��� �и�����)
	initEnemy();

	return S_OK;
}

void field1Scene::release()
{
	_player->release();
	SAFE_DELETE(_player);

	_tileMap->release();
	SAFE_DELETE(_tileMap);

	_playerUI->release();
	SAFE_DELETE(_playerUI);

	_attackManager->release();
	SAFE_DELETE(_attackManager);

	_enemyManager->release();
	SAFE_DELETE(_enemyManager);

	_collision->release();
	SAFE_DELETE(_collision);
}

void field1Scene::update()
{
	//�ӽ� �׽�Ʈ
	if (KEYMANAGER->isOnceKeyDown('G')) DATABASE->saveDataToFile();
	//������Ʈ ����
	_tileMap->update();			//1.��
	_player->update();			//2.�÷��̾�
	_enemyManager->update();	//3.��
	_attackManager->update();	//4.����
	_collision->update(_player, _enemyManager->getEnemyVector(), _attackManager->getAttackVector());	//�浹
	_playerUI->update();		//6.UI
	cameraMove();				//7.ī�޶� (�̵�)
	portal();					//8.��Ż (Ư�� A��ǥ -> Ư�� B��ǥ �̵�)
}

void field1Scene::render()
{
	//����(�׸���) ����
	_tileMap->render();			//1.��		������
	_enemyManager->render();	//2.��
	_player->render();			//3.�÷��̾�
	_attackManager->render();	//4.����	
	_playerUI->render();		//5.UI		�ֻ���
}

void field1Scene::initEnemy()
{
	//���͸� �����ϴ� �Լ��Դϴ�.
	_enemyManager->setAlien(21022);
	_enemyManager->setGhost(21024);
	_enemyManager->setOko(20570);
	_enemyManager->setFlower(20270);
	_enemyManager->setBomb(21329);
	_enemyManager->setMiniGhost(20270);
	_enemyManager->setRotateCube(13250);
	_enemyManager->setRotateCube(12947);
	_enemyManager->setMiniGhost(12335);
	_enemyManager->setMiniGhost(12484);
	_enemyManager->setBomb(12922);
	_enemyManager->setBomb(12923);
	_enemyManager->setBomb(12924);
	_enemyManager->setAlien(10378);
	_enemyManager->setAlien(10526);
	_enemyManager->setOko(9642);
	_enemyManager->setOko(9644);
	_enemyManager->setOko(9646);
	_enemyManager->setEri(15718);
}

void field1Scene::cameraMove()
{
	//����� ��ǻ� ������ �ʰ� �ֽ��ϴ�.
	//->�Ҽ��� ���� ���� �ݿø��� ���� ��ǥ�� ��߳� �ٸ� ������� ��ü��
	float angle = getAngle(DATABASE->getDestCamX(), DATABASE->getDestCamY(), DATABASE->getSourCamX(), DATABASE->getSourCamY());
	int distanceX = getDistance(DATABASE->getDestCamX(), 0, DATABASE->getSourCamX(), 0);
	int distanceY = getDistance(0, DATABASE->getDestCamY(), 0, DATABASE->getSourCamY());


	//���� ȭ���� ����ٸ�
	if (Background.right < WINSIZEX)
	{
		int diffrence = WINSIZEX - Background.right;
		Background.right += diffrence;	//����� �����̴� ������ ����
		Background.left += diffrence;	//����� �����̴� ������ ����
		_tileMap->moveTileX(diffrence);
		_player->addPlayerX(-diffrence);//�÷��̾��� �����̴� ������ ����
		_enemyManager->addEnemyX(diffrence);
	}
	if (Background.left > 0)
	{
		int diffrence = Background.left;
		Background.right -= diffrence;
		Background.left -= diffrence;
		_player->addPlayerX(+diffrence);
		_tileMap->moveTileX(-diffrence);
		_enemyManager->addEnemyX(-diffrence);
	}
	if (Background.top > 0)
	{
		int diffrence = Background.top;
		Background.top -= diffrence;
		Background.bottom -= diffrence;
		_player->addPlayerY(diffrence);
		_tileMap->moveTileY(-diffrence);
		_enemyManager->addEnemyY(-diffrence);
	}

	if (Background.bottom < WINSIZEY)
	{
		int diffrence = WINSIZEY - Background.bottom;
		Background.top += diffrence;
		Background.bottom += diffrence;
		_player->addPlayerY(-diffrence);
		_tileMap->moveTileY(+diffrence);
		_enemyManager->addEnemyY(diffrence);
	}

	//X��ǥ �̵�
	if (DATABASE->getSourCamX() > DATABASE->getDestCamX())		//ȭ�� ���������� �����϶�
	{
		Background.left -= distanceX / 10;
		Background.right -= distanceX / 10;
		_player->addPlayerX(-distanceX / 10);
		_tileMap->moveTileX(-distanceX / 10);
		_attackManager->moveAttackX(-distanceX / 10);
		_enemyManager->addEnemyX(-distanceX / 10);
		DATABASE->addBackgroundCount(-distanceX / 10);
	}

	if (DATABASE->getSourCamX() < DATABASE->getDestCamX())		//ȭ�� �������� �����϶�
	{
		Background.left += distanceX / 10;
		Background.right += distanceX / 10;
		_player->addPlayerX(distanceX / 10);
		_tileMap->moveTileX(distanceX / 10);
		_attackManager->moveAttackX(distanceX / 10);
		_enemyManager->addEnemyX(distanceX / 10);
		DATABASE->addBackgroundCount(distanceX / 10);
	}

	//Y��ǥ �̵�
	if (DATABASE->getSourCamY() > DATABASE->getDestCamY())		//ȭ�� �Ʒ������� �����϶�
	{
		Background.top -= distanceY / 10;
		Background.bottom -= distanceY / 10;
		_player->addPlayerY(-distanceY / 10);
		_tileMap->moveTileY(-distanceY / 10);
		_attackManager->moveAttackY(-distanceY / 10);
		_enemyManager->addEnemyY(-distanceY / 10);
	}

	if (DATABASE->getSourCamY() < DATABASE->getDestCamY())		//ȭ�� �������� �����϶�
	{
		Background.top += distanceY / 10;
		Background.bottom += distanceY / 10;
		_player->addPlayerY(distanceY / 10);
		_tileMap->moveTileY(distanceY / 10);
		_attackManager->moveAttackY(distanceY / 10);
		_enemyManager->addEnemyY(distanceY / 10);
	}
}

void field1Scene::cameraInit()
{
	//����� ��ǻ� ������ �ʰ� �ֽ��ϴ�.
	//->�Ҽ��� ���� ���� �ݿø��� ���� ��ǥ�� ��߳� �ٸ� ������� ��ü��
	float angle = getAngle(DATABASE->getDestCamX(), DATABASE->getDestCamY(), DATABASE->getSourCamX(), DATABASE->getSourCamY());
	int distanceX = getDistance(DATABASE->getDestCamX(), 0, DATABASE->getSourCamX(), 0);
	int distanceY = getDistance(0, DATABASE->getDestCamY(), 0, DATABASE->getSourCamY());

	//���� ȭ���� ����ٸ�
	if (Background.right < WINSIZEX)
	{
		int diffrence = WINSIZEX - Background.right;
		Background.right += diffrence;	//����� �����̴� ������ ����
		Background.left += diffrence;	//����� �����̴� ������ ����
		_tileMap->moveTileX(diffrence);
		_player->addPlayerX(-diffrence);//�÷��̾��� �����̴� ������ ����
	}
	if (Background.left > 0)
	{
		int diffrence = Background.left;
		Background.right -= diffrence;
		Background.left -= diffrence;
		_player->addPlayerX(+diffrence);
		_tileMap->moveTileX(-diffrence);
	}
	if (Background.top > 0)
	{
		int diffrence = Background.top;
		Background.top -= diffrence;
		Background.bottom -= diffrence;
		_player->addPlayerY(diffrence);
		_tileMap->moveTileY(-diffrence);
	}

	if (Background.bottom < WINSIZEY)
	{
		int diffrence = WINSIZEY - Background.bottom;
		Background.top += diffrence;
		Background.bottom += diffrence;
		_player->addPlayerY(-diffrence);
		_tileMap->moveTileY(+diffrence);
	}

	//X��ǥ �̵�
	if (DATABASE->getSourCamX() > DATABASE->getDestCamX())		//ȭ�� ���������� �����϶�
	{
		Background.left -= distanceX;
		Background.right -= distanceX;
		_player->addPlayerX(-distanceX);
		_tileMap->moveTileX(-distanceX);
		_attackManager->moveAttackX(-distanceX);
		_enemyManager->addEnemyX(-distanceX);
	}

	if (DATABASE->getSourCamX() < DATABASE->getDestCamX())		//ȭ�� �������� �����϶�
	{
		Background.left += distanceX;
		Background.right += distanceX;
		_player->addPlayerX(distanceX);
		_tileMap->moveTileX(distanceX);
		_attackManager->moveAttackX(distanceX);
		_enemyManager->addEnemyX(distanceX);
	}

	//Y��ǥ �̵�
	if (DATABASE->getSourCamY() > DATABASE->getDestCamY())		//ȭ�� �Ʒ������� �����϶�
	{
		Background.top -= distanceY;
		Background.bottom -= distanceY;
		_player->addPlayerY(-distanceY);
		_tileMap->moveTileY(-distanceY);
		_attackManager->moveAttackY(-distanceY);
		_enemyManager->addEnemyY(-distanceY);
	}

	if (DATABASE->getSourCamY() < DATABASE->getDestCamY())		//ȭ�� �������� �����϶�
	{
		Background.top += distanceY;
		Background.bottom += distanceY;
		_player->addPlayerY(distanceY);
		_tileMap->moveTileY(distanceY);
		_attackManager->moveAttackY(distanceY);
		_enemyManager->addEnemyY(distanceY);
	}
}

void field1Scene::portal()
{
	//�÷��̾ Ư�� Ÿ�Ͽ� ������ �ٸ� Ÿ�Ϸ� �̵���Ű�� �Լ�.
	//�̵��Ҽ� �ִ� Ÿ���� ���� �˳��ϰ� ����������.
	//�浹������ ���������� �̵��ϱ� ������ ù �浹�� �ѹ��� ���������� �Ѵ�.

	switch (_player->getCollisionTile())
	{
	case 17272:									//1������������ 2���������� �ѱ�� �κ�
	case 17273:
	case 17274:
		_player->setPlayerTilePosition(16398);
		_player->firstCollisionTileCheck();
		_player->update();
		cameraInit();
		break;
	case 14748:									//2�������� ���� 3���������� �ѱ�� �κ�
	case 14749:
		_player->setPlayerTilePosition(13698);
		_player->firstCollisionTileCheck();
		_player->update();
		cameraInit();
		break;
	case 15289:
		_player->setPlayerTilePosition(5873);
		_player->firstCollisionTileCheck();
		_player->update();
		cameraInit();
		break;
	case 5872:
	case 5722:
	case 5572:
		_player->setPlayerTilePosition(15137);
		_player->firstCollisionTileCheck();
		_player->update();
		cameraInit();
		break;
	}
}

field1Scene::field1Scene()
{

}

field1Scene::~field1Scene()
{

}

HRESULT field2Scene::init()
{
	return S_OK;
}

void field2Scene::release()
{
}

void field2Scene::update()
{
}

void field2Scene::render()
{
}

void field2Scene::cameraMove()
{
}

void field2Scene::cameraInit()
{

}

field2Scene::field2Scene()
{
}

field2Scene::~field2Scene()
{
}

HRESULT bossScene::init()
{
	DATABASE->setBaseTime(TIMEMANAGER->getWorldTime());
	DATABASE->setDestCamX(WINSIZEX / 2);
	DATABASE->setDestCamY(WINSIZEY / 2);
	IMAGEMANAGER->addFrameImage("tileMap", "IMAGE/tile/tile.bmp", 0, 0, 1350, 1200, SAMPLETILEX, SAMPLETILEY, true, RGB(0, 0, 0));
	Background = RectMake(0, 0, TILESIZEX, TILESIZEY);

	_tileMap = new tileMap;
	_tileMap->init("DATA/MAP/Boss.map");

	_attackManager = new attackManager;
	_attackManager->init();

	_enemyManager = new enemyManager;
	_enemyManager->init(_tileMap, _attackManager);

	_player = new player;
	_player->init();
	_player->setTileMapMemoryAddress(_tileMap);
	_player->setAttackManagerMemoryAddress(_attackManager);
	_player->setPlayerTilePosition(21513);
	_player->firstCollisionTileCheck();

	_playerUI = new playerUI;
	_playerUI->init();

	_enemyManager->setEri(21375);

	return S_OK;
}

void bossScene::release()
{
	_tileMap->release();
	SAFE_DELETE(_tileMap);

	_attackManager->release();
	SAFE_DELETE(_attackManager);

	_enemyManager->release();
	SAFE_DELETE(_enemyManager);

	_player->release();
	SAFE_DELETE(_player);

	_playerUI->release();
	SAFE_DELETE(_playerUI);
}

void bossScene::update()
{
	_player->update();
	_playerUI->update();
	_attackManager->update();
	_enemyManager->update();

	cameraMove(); //��� ó���� ������ ī�޶��� �������� �����մϴ�.
}

void bossScene::render()
{
	_tileMap->render();
	_enemyManager->render();
	_player->render();
	_attackManager->render();
	_playerUI->render();
}

void bossScene::cameraMove()
{
	//����� ��ǻ� ������ �ʰ� �ֽ��ϴ�.
	//->�Ҽ��� ���� ���� �ݿø��� ���� ��ǥ�� ��߳� �ٸ� ������� ��ü��
	float angle = getAngle(DATABASE->getDestCamX(), DATABASE->getDestCamY(), DATABASE->getSourCamX(), DATABASE->getSourCamY());
	int distanceX = getDistance(DATABASE->getDestCamX(), 0, DATABASE->getSourCamX(), 0);
	int distanceY = getDistance(0, DATABASE->getDestCamY(), 0, DATABASE->getSourCamY());

	//���� ȭ���� ����ٸ�
	if (Background.right < WINSIZEX)
	{
		int diffrence = WINSIZEX - Background.right;
		Background.right += diffrence;	//����� �����̴� ������ ����
		Background.left += diffrence;	//����� �����̴� ������ ����
		_tileMap->moveTileX(diffrence);
		_player->addPlayerX(-diffrence);//�÷��̾��� �����̴� ������ ����
	}
	if (Background.left > 0)
	{
		int diffrence = Background.left;
		Background.right -= diffrence;
		Background.left -= diffrence;
		_player->addPlayerX(+diffrence);
		_tileMap->moveTileX(-diffrence);
	}
	if (Background.top > 0)
	{
		int diffrence = Background.top;
		Background.top -= diffrence;
		Background.bottom -= diffrence;
		_player->addPlayerY(diffrence);
		_tileMap->moveTileY(-diffrence);
	}

	if (Background.bottom < WINSIZEY)
	{
		int diffrence = WINSIZEY - Background.bottom;
		Background.top += diffrence;
		Background.bottom += diffrence;
		_player->addPlayerY(-diffrence);
		_tileMap->moveTileY(+diffrence);
	}

	//X��ǥ �̵�
	if (DATABASE->getSourCamX() > DATABASE->getDestCamX())		//ȭ�� ���������� �����϶�
	{
		Background.left -= distanceX / 10;
		Background.right -= distanceX / 10;
		_player->addPlayerX(-distanceX / 10);
		_tileMap->moveTileX(-distanceX / 10);
		_attackManager->moveAttackX(-distanceX / 10);
		_enemyManager->addEnemyX(-distanceX / 10);
	}

	if (DATABASE->getSourCamX() < DATABASE->getDestCamX())		//ȭ�� �������� �����϶�
	{
		Background.left += distanceX / 10;
		Background.right += distanceX / 10;
		_player->addPlayerX(distanceX / 10);
		_tileMap->moveTileX(distanceX / 10);
		_attackManager->moveAttackX(distanceX / 10);
		_enemyManager->addEnemyX(distanceX / 10);
	}

	//Y��ǥ �̵�
	if (DATABASE->getSourCamY() > DATABASE->getDestCamY())		//ȭ�� �Ʒ������� �����϶�
	{
		Background.top -= distanceY / 10;
		Background.bottom -= distanceY / 10;
		_player->addPlayerY(-distanceY / 10);
		_tileMap->moveTileY(-distanceY / 10);
		_attackManager->moveAttackY(-distanceY / 10);
		_enemyManager->addEnemyY(-distanceY / 10);
	}

	if (DATABASE->getSourCamY() < DATABASE->getDestCamY())		//ȭ�� �������� �����϶�
	{
		Background.top += distanceY / 10;
		Background.bottom += distanceY / 10;
		_player->addPlayerY(distanceY / 10);
		_tileMap->moveTileY(distanceY / 10);
		_attackManager->moveAttackY(distanceY / 10);
		_enemyManager->addEnemyY(distanceY / 10);
	}
}

void bossScene::cameraInit()
{

}

bossScene::bossScene()
{
}

bossScene::~bossScene()
{
}

HRESULT testScene::init()
{
	DATABASE->loadDataFromFile();	//���Ϸκ��� �÷��̾��� �����͸� �ҷ��� �����մϴ�. ������ �÷��̾��� �ʱ�ȭ�� �ʿ��մϴ�.
	DATABASE->setBaseTime(TIMEMANAGER->getWorldTime());
	DATABASE->setDestCamX(WINSIZEX / 2);
	DATABASE->setDestCamY(WINSIZEY / 2);
	IMAGEMANAGER->addFrameImage("tileMap", "IMAGE/tile/tile.bmp", 0, 0, 1350, 1200, SAMPLETILEX, SAMPLETILEY, true, RGB(0, 0, 0));
	_image = IMAGEMANAGER->addImage("����", "IMAGE/whiteBackground.bmp", WINSIZEX, WINSIZEY, false, RGB(0, 0, 0));

	_tileMap = new tileMap;
	_tileMap->init("DATA/MAP/Town.map");

	_attackManager = new attackManager;
	_attackManager->init();

	_enemyManager = new enemyManager;
	_enemyManager->init(_tileMap, _attackManager);

	//�÷��̾ �ʱ�ȭ �ϱ� ���� �̱��濡 �����͸� �ε� ����� �մϴ�.
	_player = new player;
	_player->init();
	_player->setTileMapMemoryAddress(_tileMap);
	_player->setAttackManagerMemoryAddress(_attackManager);
	_player->setPlayerTilePosition(DATABASE->getCollisionTile());
	_player->firstCollisionTileCheck();

	_playerUI = new playerUI;
	_playerUI->init();

	_collision = new collision;
	_collision->init();

	cameraX = 0;
	cameraY = 0;

	_enemyManager->setAlien(21022);
	_enemyManager->setGhost(21024);
	_enemyManager->setOko(20570);
	_enemyManager->setFlower(20270);
	_enemyManager->setBomb(21329);
	_enemyManager->setMiniGhost(20270);
	_enemyManager->setRotateCube(13250);
	_enemyManager->setRotateCube(12947);
	_enemyManager->setMiniGhost(12335);
	_enemyManager->setMiniGhost(12484);
	_enemyManager->setBomb(12922);
	_enemyManager->setBomb(12923);
	_enemyManager->setBomb(12924);
	_enemyManager->setAlien(10378);
	_enemyManager->setAlien(10526);
	_enemyManager->setOko(9642);
	_enemyManager->setOko(9644);
	_enemyManager->setOko(9646);
	_enemyManager->setEri(15718);
	//_test = IMAGEMANAGER->addImage("�׽�Ʈ���", "IMAGE/test.bmp", TILESIZEX, TILESIZEY, false, RGB(0, 0, 0));
	Background = RectMake(0, 0, TILESIZEX, TILESIZEY);

	_player->update();
	cameraInit();
	return S_OK;
}

void testScene::release()
{
	_player->release();
	SAFE_DELETE(_player);

	_tileMap->release();
	SAFE_DELETE(_tileMap);

	_playerUI->release();
	SAFE_DELETE(_playerUI);

	_attackManager->release();
	SAFE_DELETE(_attackManager);

	_enemyManager->release();
	SAFE_DELETE(_enemyManager);

	_collision->release();
	SAFE_DELETE(_collision);
}

void testScene::update()
{
	_player->update();											//�÷��̾�� ������ �ϴ� ����� ��ġ�� ���� �����մϴ�.
	_playerUI->update();
	_attackManager->update();
	_enemyManager->update();
	_tileMap->update();
	_collision->update(_player, _enemyManager->getEnemyVector(), _attackManager->getAttackVector());
	//���� �ٸ� ����� ����ʹٸ�
	if (KEYMANAGER->isStayKeyDown('Q'))
	{
		DATABASE->setSourCamX(Background.left + WINSIZEX / 2);	//������� ����� X��ǥ ��ġ
		DATABASE->setSourCamY(Background.top + WINSIZEY / 2);	//������� ����� Y��ǥ ��ġ
	}

	if (KEYMANAGER->isStayKeyDown('W'))
	{
		DATABASE->setSourCamX(Background.right - WINSIZEX / 2);	//������� ����� X��ǥ ��ġ
		DATABASE->setSourCamY(Background.bottom - WINSIZEY / 2);//������� ����� Y��ǥ ��ġ
	}

	if (KEYMANAGER->isStayKeyDown('E'))
	{
		DATABASE->setDestCamX(WINSIZEX / 2);			//����� �����Ǳ� ���ϴ� X��ǥ ��ġ
		DATABASE->setDestCamY(WINSIZEY / 2);			//����� �����Ǳ� ���ϴ� Y��ǥ ��ġ
	}

	if (KEYMANAGER->isStayKeyDown('R'))
	{
		DATABASE->setDestCamX(WINSIZEX / 2);			//����� �����Ǳ� ���ϴ� X��ǥ ��ġ
		DATABASE->setDestCamY((WINSIZEY / 4) * 3);		//����� �����Ǳ� ���ϴ� Y��ǥ ��ġ
	}

	if (KEYMANAGER->isOnceKeyDown('H'))
	{
		_saveCount = 2;
		DATABASE->saveDataToFile();
	}
	//��ǥ ������ �����ڿ� Camera�Լ��� �����մϴ�.
	cameraMove();
	portal();
}

void testScene::render()
{
	_tileMap->render();
	_enemyManager->render();
	_player->render();
	_attackManager->render();
	_playerUI->render();
	SetTextColor(getMemDC(), RGB(255, 255, 255));
}

void testScene::cameraMove()
{
	//����� ��ǻ� ������ �ʰ� �ֽ��ϴ�.
	//->�Ҽ��� ���� ���� �ݿø��� ���� ��ǥ�� ��߳� �ٸ� ������� ��ü��
	float angle = getAngle(DATABASE->getDestCamX(), DATABASE->getDestCamY(), DATABASE->getSourCamX(), DATABASE->getSourCamY());
	int distanceX = getDistance(DATABASE->getDestCamX(), 0, DATABASE->getSourCamX(), 0);
	int distanceY = getDistance(0, DATABASE->getDestCamY(), 0, DATABASE->getSourCamY());


	//���� ȭ���� ����ٸ�
	if (Background.right < WINSIZEX)
	{
		int diffrence = WINSIZEX - Background.right;
		Background.right += diffrence;	//����� �����̴� ������ ����
		Background.left += diffrence;	//����� �����̴� ������ ����
		_tileMap->moveTileX(diffrence);
		_player->addPlayerX(-diffrence);//�÷��̾��� �����̴� ������ ����
		_enemyManager->addEnemyX(diffrence);
	}
	if (Background.left > 0)
	{
		int diffrence = Background.left;
		Background.right -= diffrence;
		Background.left -= diffrence;
		_player->addPlayerX(+diffrence);
		_tileMap->moveTileX(-diffrence);
		_enemyManager->addEnemyX(-diffrence);
	}
	if (Background.top > 0)
	{
		int diffrence = Background.top;
		Background.top -= diffrence;
		Background.bottom -= diffrence;
		_player->addPlayerY(diffrence);
		_tileMap->moveTileY(-diffrence);
		_enemyManager->addEnemyY(-diffrence);
	}

	if (Background.bottom < WINSIZEY)
	{
		int diffrence = WINSIZEY - Background.bottom;
		Background.top += diffrence;
		Background.bottom += diffrence;
		_player->addPlayerY(-diffrence);
		_tileMap->moveTileY(+diffrence);
		_enemyManager->addEnemyY(diffrence);
	}

	//X��ǥ �̵�
	if (DATABASE->getSourCamX() > DATABASE->getDestCamX())		//ȭ�� ���������� �����϶�
	{
		Background.left -= distanceX / 10;
		Background.right -= distanceX / 10;
		_player->addPlayerX(-distanceX / 10);
		_tileMap->moveTileX(-distanceX / 10);
		_attackManager->moveAttackX(-distanceX / 10);
		_enemyManager->addEnemyX(-distanceX / 10);
		DATABASE->addBackgroundCount(-distanceX / 10);
	}

	if (DATABASE->getSourCamX() < DATABASE->getDestCamX())		//ȭ�� �������� �����϶�
	{
		Background.left += distanceX / 10;
		Background.right += distanceX / 10;
		_player->addPlayerX(distanceX / 10);
		_tileMap->moveTileX(distanceX / 10);
		_attackManager->moveAttackX(distanceX / 10);
		_enemyManager->addEnemyX(distanceX / 10);
		DATABASE->addBackgroundCount(distanceX / 10);
	}

	//Y��ǥ �̵�
	if (DATABASE->getSourCamY() > DATABASE->getDestCamY())		//ȭ�� �Ʒ������� �����϶�
	{
		Background.top -= distanceY / 10;
		Background.bottom -= distanceY / 10;
		_player->addPlayerY(-distanceY / 10);
		_tileMap->moveTileY(-distanceY / 10);
		_attackManager->moveAttackY(-distanceY / 10);
		_enemyManager->addEnemyY(-distanceY / 10);
	}

	if (DATABASE->getSourCamY() < DATABASE->getDestCamY())		//ȭ�� �������� �����϶�
	{
		Background.top += distanceY / 10;
		Background.bottom += distanceY / 10;
		_player->addPlayerY(distanceY / 10);
		_tileMap->moveTileY(distanceY / 10);
		_attackManager->moveAttackY(distanceY / 10);
		_enemyManager->addEnemyY(distanceY / 10);
	}
}

void testScene::cameraInit()
{
	//����� ��ǻ� ������ �ʰ� �ֽ��ϴ�.
	//->�Ҽ��� ���� ���� �ݿø��� ���� ��ǥ�� ��߳� �ٸ� ������� ��ü��
	float angle = getAngle(DATABASE->getDestCamX(), DATABASE->getDestCamY(), DATABASE->getSourCamX(), DATABASE->getSourCamY());
	int distanceX = getDistance(DATABASE->getDestCamX(), 0, DATABASE->getSourCamX(), 0);
	int distanceY = getDistance(0, DATABASE->getDestCamY(), 0, DATABASE->getSourCamY());

	//���� ȭ���� ����ٸ�
	if (Background.right < WINSIZEX)
	{
		int diffrence = WINSIZEX - Background.right;
		Background.right += diffrence;	//����� �����̴� ������ ����
		Background.left += diffrence;	//����� �����̴� ������ ����
		_tileMap->moveTileX(diffrence);
		_player->addPlayerX(-diffrence);//�÷��̾��� �����̴� ������ ����
	}
	if (Background.left > 0)
	{
		int diffrence = Background.left;
		Background.right -= diffrence;
		Background.left -= diffrence;
		_player->addPlayerX(+diffrence);
		_tileMap->moveTileX(-diffrence);
	}
	if (Background.top > 0)
	{
		int diffrence = Background.top;
		Background.top -= diffrence;
		Background.bottom -= diffrence;
		_player->addPlayerY(diffrence);
		_tileMap->moveTileY(-diffrence);
	}

	if (Background.bottom < WINSIZEY)
	{
		int diffrence = WINSIZEY - Background.bottom;
		Background.top += diffrence;
		Background.bottom += diffrence;
		_player->addPlayerY(-diffrence);
		_tileMap->moveTileY(+diffrence);
	}

	//X��ǥ �̵�
	if (DATABASE->getSourCamX() > DATABASE->getDestCamX())		//ȭ�� ���������� �����϶�
	{
		Background.left -= distanceX;
		Background.right -= distanceX;
		_player->addPlayerX(-distanceX);
		_tileMap->moveTileX(-distanceX);
		_attackManager->moveAttackX(-distanceX);
		_enemyManager->addEnemyX(-distanceX);
	}

	if (DATABASE->getSourCamX() < DATABASE->getDestCamX())		//ȭ�� �������� �����϶�
	{
		Background.left += distanceX;
		Background.right += distanceX;
		_player->addPlayerX(distanceX);
		_tileMap->moveTileX(distanceX);
		_attackManager->moveAttackX(distanceX);
		_enemyManager->addEnemyX(distanceX);
	}

	//Y��ǥ �̵�
	if (DATABASE->getSourCamY() > DATABASE->getDestCamY())		//ȭ�� �Ʒ������� �����϶�
	{
		Background.top -= distanceY;
		Background.bottom -= distanceY;
		_player->addPlayerY(-distanceY);
		_tileMap->moveTileY(-distanceY);
		_attackManager->moveAttackY(-distanceY);
		_enemyManager->addEnemyY(-distanceY);
	}

	if (DATABASE->getSourCamY() < DATABASE->getDestCamY())		//ȭ�� �������� �����϶�
	{
		Background.top += distanceY;
		Background.bottom += distanceY;
		_player->addPlayerY(distanceY);
		_tileMap->moveTileY(distanceY);
		_attackManager->moveAttackY(distanceY);
		_enemyManager->addEnemyY(distanceY);
	}
}

void testScene::portal()
{
	//�÷��̾ Ư�� Ÿ�Ͽ� ������ �ٸ� Ÿ�Ϸ� �̵���Ű�� �Լ�.
	//�̵��Ҽ� �ִ� Ÿ���� ���� �˳��ϰ� ����������.
	//�浹������ ���������� �̵��ϱ� ������ ù �浹�� �ѹ��� ���������� �Ѵ�.

	switch (_player->getCollisionTile())
	{
	case 17272:									//1������������ 2���������� �ѱ�� �κ�
	case 17273:
	case 17274:
		_player->setPlayerTilePosition(16398);
		_player->firstCollisionTileCheck();
		_player->update();
		cameraInit();
		break;
	case 14748:									//2�������� ���� 3���������� �ѱ�� �κ�
	case 14749:
		_player->setPlayerTilePosition(13698);
		_player->firstCollisionTileCheck();
		_player->update();
		cameraInit();
		break;
	case 15289:
		_player->setPlayerTilePosition(5873);
		_player->firstCollisionTileCheck();
		_player->update();
		cameraInit();
		break;
	case 5872:
	case 5722:
	case 5572:
		_player->setPlayerTilePosition(15137);
		_player->firstCollisionTileCheck();
		_player->update();
		cameraInit();
		break;
	}
}

testScene::testScene()
{
}

testScene::~testScene()
{

}