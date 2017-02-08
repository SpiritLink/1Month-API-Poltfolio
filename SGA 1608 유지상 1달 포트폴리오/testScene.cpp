#include "stdafx.h"
#include "testScene.h"


HRESULT testScene::init()
{
	DATABASE->setBaseTime(TIMEMANAGER->getWorldTime());
	DATABASE->setDestCamX(WINSIZEX / 2);
	DATABASE->setDestCamY(WINSIZEY / 2);
	IMAGEMANAGER->addFrameImage("tileMap", "IMAGE/tile/tile.bmp", 0, 0, 1350, 1200, SAMPLETILEX, SAMPLETILEY, true, RGB(0, 0, 0));
	_image = IMAGEMANAGER->addImage("흰배경", "IMAGE/whiteBackground.bmp", WINSIZEX, WINSIZEY, false, RGB(0, 0, 0));

	_tileMap = new tileMap;
	_tileMap->init("DATA/MAP/Field1.map");

	_attackManager = new attackManager;
	_attackManager->init();

	_enemyManager = new enemyManager;
	_enemyManager->init(_tileMap,_attackManager);

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

	cameraX = 0;
	cameraY = 0;

	_enemyManager->setAlien(21022);
	_enemyManager->setEri(21022);
	_enemyManager->setGhost(21024);
	_enemyManager->setOko(20876);


	_test = IMAGEMANAGER->addImage("테스트배경", "IMAGE/test.bmp", TILESIZEX, TILESIZEY, false, RGB(0, 0, 0));
	Background = RectMake(0, 0, _test->getWidth(), _test->getHeight());

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
	_player->update();											//플레이어에서 보고자 하는 대상의 위치를 먼저 전송합니다.
	_playerUI->update();
	_attackManager->update();
	_enemyManager->update();
	_collision->update(_player, _enemyManager->getEnemyVector(), _attackManager->getAttackVector());
	//만약 다른 대상을 보고싶다면
	if (KEYMANAGER->isStayKeyDown('Q'))
	{
		DATABASE->setSourCamX(Background.left + WINSIZEX / 2);	//보고싶은 대상의 X좌표 위치
		DATABASE->setSourCamY(Background.top + WINSIZEY / 2);	//보고싶은 대상위 Y좌표 위치
	}

	if (KEYMANAGER->isStayKeyDown('W'))
	{
		DATABASE->setSourCamX(Background.right - WINSIZEX / 2);	//보고싶은 대상의 X좌표 위치
		DATABASE->setSourCamY(Background.bottom - WINSIZEY / 2);//보고싶은 대상의 Y좌표 위치
	}

	if (KEYMANAGER->isStayKeyDown('E'))
	{		
		DATABASE->setDestCamX(WINSIZEX / 2);			//대상이 고정되기 원하는 X좌표 위치
		DATABASE->setDestCamY(WINSIZEY / 2);			//대상이 고정되기 원하는 Y좌표 위치
	}

	if (KEYMANAGER->isStayKeyDown('R'))
	{
		DATABASE->setDestCamX(WINSIZEX / 2);			//대상이 고정되기 원하는 X좌표 위치
		DATABASE->setDestCamY((WINSIZEY / 4) * 3);		//대상이 고정되기 원하는 Y좌표 위치
	}
	
	//좌표 설정이 끝난뒤에 Camera함수에 진입합니다.
	cameraMove();
	portal();

}

void testScene::render()
{
	_image->render(getMemDC());
	Rectangle(getMemDC(), Background.left, Background.top, Background.right, Background.bottom);
	_test->render(getMemDC(), Background.left, Background.top);
	_tileMap->render();
	_enemyManager->render();
	_player->render();
	//if (KEYMANAGER->isToggleKey(VK_SHIFT)) _tileMap->miniMapRender();

	_attackManager->render();
	_playerUI->render();
	SetTextColor(getMemDC(), RGB(255, 255, 255));
}

void testScene::cameraMove()
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

void testScene::cameraInit()
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

void testScene::portal()
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


testScene::testScene()
{
}

testScene::~testScene()
{
}
