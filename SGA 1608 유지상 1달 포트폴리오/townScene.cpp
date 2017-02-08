#include "stdafx.h"
#include "townScene.h"


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

	_backIMG = IMAGEMANAGER->addImage("테스트배경", "IMAGE/test.bmp", TILESIZEX, TILESIZEY, false, RGB(0, 0, 0));
	Background = RectMake(0, 0, _backIMG->getWidth(), _backIMG->getHeight());

	_player->update();
	cameraInit();//카메라의 위치를 세팅합니다.

	_enemyManager->setBomb(21548);
	_enemyManager->setBomb(21549);
	_enemyManager->setBomb(21550);
	_enemyManager->setBomb(21551);
	_enemyManager->setBomb(21552);

	_enemyManager->setFlower(21101);

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
	_attackManager->update();
	_enemyManager->update();
	_collision->update(_player, _enemyManager->getEnemyVector(), _attackManager->getAttackVector());
	cameraMove();
}

void townScene::render()
{
	_backIMG->render(getMemDC(),Background.left, Background.top);
	_tileMap->render();
	_enemyManager->render();
	_player->render();

	_attackManager->render();
	_playerUI->render();
}

void townScene::cameraMove()
{
	//현재는 사실상 쓰이지 않고 있습니다.
	//->소수점 연산 도중 반올림에 의해 좌표가 어긋나 다른 방식으로 대체됨
	float angle = getAngle(DATABASE->getDestCamX(), DATABASE->getDestCamY(), DATABASE->getSourCamX(), DATABASE->getSourCamY());
	int distanceX = getDistance(DATABASE->getDestCamX(), 0, DATABASE->getSourCamX(), 0);
	int distanceY = getDistance(0, DATABASE->getDestCamY(), 0, DATABASE->getSourCamY());

	//만약 화면을 벗어난다면
	if (Background.right < WINSIZEX)
	{
		int diffrence = WINSIZEX - Background.right;
		Background.right += diffrence;	//배경의 움직이는 정도를 조절
		Background.left += diffrence;	//배경의 움직이는 정도를 조정
		_tileMap->moveTileX(diffrence);
		_player->addPlayerX(-diffrence);//플레이어의 움직이는 정도를 조절
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

	//X좌표 이동
	if (DATABASE->getSourCamX() > DATABASE->getDestCamX())		//화면 오른쪽으로 움직일때
	{
		Background.left -= distanceX / 10;
		Background.right -= distanceX / 10;
		_player->addPlayerX(-distanceX / 10);
		_tileMap->moveTileX(-distanceX / 10);
		_attackManager->moveAttackX(-distanceX / 10);
		_enemyManager->addEnemyX(-distanceX / 10);
	}

	if (DATABASE->getSourCamX() < DATABASE->getDestCamX())		//화면 왼쪽으로 움직일때
	{
		Background.left += distanceX / 10;
		Background.right += distanceX / 10;
		_player->addPlayerX(distanceX / 10);
		_tileMap->moveTileX(distanceX / 10);
		_attackManager->moveAttackX(distanceX / 10);
		_enemyManager->addEnemyX(distanceX / 10);
	}

	//Y좌표 이동
	if (DATABASE->getSourCamY() > DATABASE->getDestCamY())		//화면 아래쪽으로 움직일때
	{
		Background.top -= distanceY / 10;
		Background.bottom -= distanceY / 10;
		_player->addPlayerY(-distanceY / 10);
		_tileMap->moveTileY(-distanceY / 10);
		_attackManager->moveAttackY(-distanceY / 10);
		_enemyManager->addEnemyY(-distanceY / 10);
	}

	if (DATABASE->getSourCamY() < DATABASE->getDestCamY())		//화면 위쪽으로 움직일때
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
	//현재는 사실상 쓰이지 않고 있습니다.
	//->소수점 연산 도중 반올림에 의해 좌표가 어긋나 다른 방식으로 대체됨
	float angle = getAngle(DATABASE->getDestCamX(), DATABASE->getDestCamY(), DATABASE->getSourCamX(), DATABASE->getSourCamY());
	int distanceX = getDistance(DATABASE->getDestCamX(), 0, DATABASE->getSourCamX(), 0);
	int distanceY = getDistance(0, DATABASE->getDestCamY(), 0, DATABASE->getSourCamY());

	//만약 화면을 벗어난다면
	if (Background.right < WINSIZEX)
	{
		int diffrence = WINSIZEX - Background.right;
		Background.right += diffrence;	//배경의 움직이는 정도를 조절
		Background.left += diffrence;	//배경의 움직이는 정도를 조정
		_tileMap->moveTileX(diffrence);
		_player->addPlayerX(-diffrence);//플레이어의 움직이는 정도를 조절
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

	//X좌표 이동
	if (DATABASE->getSourCamX() > DATABASE->getDestCamX())		//화면 오른쪽으로 움직일때
	{
		Background.left -= distanceX;
		Background.right -= distanceX;
		_player->addPlayerX(-distanceX);
		_tileMap->moveTileX(-distanceX);
		_attackManager->moveAttackX(-distanceX);
		_enemyManager->addEnemyX(-distanceX);
	}

	if (DATABASE->getSourCamX() < DATABASE->getDestCamX())		//화면 왼쪽으로 움직일때
	{
		Background.left += distanceX;
		Background.right += distanceX;
		_player->addPlayerX(distanceX);
		_tileMap->moveTileX(distanceX);
		_attackManager->moveAttackX(distanceX);
		_enemyManager->addEnemyX(distanceX);
	}

	//Y좌표 이동
	if (DATABASE->getSourCamY() > DATABASE->getDestCamY())		//화면 아래쪽으로 움직일때
	{
		Background.top -= distanceY;
		Background.bottom -= distanceY;
		_player->addPlayerY(-distanceY);
		_tileMap->moveTileY(-distanceY);
		_attackManager->moveAttackY(-distanceY);
		_enemyManager->addEnemyY(-distanceY);
	}

	if (DATABASE->getSourCamY() < DATABASE->getDestCamY())		//화면 위쪽으로 움직일때
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
