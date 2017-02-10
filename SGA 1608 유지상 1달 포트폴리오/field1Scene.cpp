#include "stdafx.h"
#include "field1Scene.h"


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

	Background = RectMake(0, 0, TILESIZEX, TILESIZEY);	//임계영역 설정을 위해서
	_player->update();
	cameraInit();

	//적 배치 (나중에 함수로 분리하자)
	_enemyManager->setFlower(21174);
	_enemyManager->setFlower(17864);
	_enemyManager->setOko(17870);
	_enemyManager->setMiniGhost(18461);
	_enemyManager->setMiniGhost(18460);

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
	//업데이트 순서
	_tileMap->update();			//1.맵
	_player->update();			//2.플레이어
	_enemyManager->update();	//3.적
	_attackManager->update();	//4.공격
	_collision->update(_player, _enemyManager->getEnemyVector(), _attackManager->getAttackVector());	//충돌
	_playerUI->update();		//6.UI
	cameraMove();				//7.카메라 (이동)
	portal();					//8.포탈 (특정 A좌표 -> 특정 B좌표 이동)
}

void field1Scene::render()
{	
	//렌더(그리는) 순서
	_tileMap->render();			//1.맵		최하위
	_enemyManager->render();	//2.적
	_player->render();			//3.플레이어
	_attackManager->render();	//4.공격	
	_playerUI->render();		//5.UI		최상위
}

void field1Scene::cameraMove()
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
		DATABASE->addBackgroundCount(-distanceX / 10);
	}

	if (DATABASE->getSourCamX() < DATABASE->getDestCamX())		//화면 왼쪽으로 움직일때
	{
		Background.left += distanceX / 10;
		Background.right += distanceX / 10;
		_player->addPlayerX(distanceX / 10);
		_tileMap->moveTileX(distanceX / 10);
		_attackManager->moveAttackX(distanceX / 10);
		_enemyManager->addEnemyX(distanceX / 10);
		DATABASE->addBackgroundCount(distanceX / 10);
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

void field1Scene::cameraInit()
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

void field1Scene::portal()
{
	//플레이어가 특정 타일에 닿으면 다른 타일로 이동시키는 함수.
	//이동할수 있는 타일을 좀더 넉넉하게 설정해주자.
	//충돌구간이 순간적으로 이동하기 때문에 첫 충돌을 한번더 실행시켜줘야 한다.

	switch (_player->getCollisionTile())
	{
	case 17272:									//1스테이지에서 2스테이지로 넘기는 부분
	case 17273:
	case 17274:
		_player->setPlayerTilePosition(16398);
		_player->firstCollisionTileCheck();
		_player->update();
		cameraInit();
		break;
	case 14748:									//2스테이지 에서 3스테이지로 넘기는 부분
	case 14749:
		_player->setPlayerTilePosition(13698);
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
