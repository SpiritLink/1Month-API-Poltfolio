#include "stdafx.h"
#include "ingameScene.h"

HRESULT townScene::init()
{
	DATABASE->setBaseTime(TIMEMANAGER->getWorldTime());
	DATABASE->setDestCamX(WINSIZEX / 2);
	DATABASE->setDestCamY(WINSIZEY - 150);
	DATABASE->setMenu(false);
	DATABASE->setRestart(false);
	DATABASE->setPlayerDie(false);
	IMAGEMANAGER->addFrameImage("tileMap", "IMAGE/tile/tile.bmp", 0, 0, 1350, 1200, SAMPLETILEX, SAMPLETILEY, true, RGB(0, 0, 0));

	_sceneNumber = 1;
	_black = IMAGEMANAGER->addImage("black", "IMAGE/UI/black.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 255, 255));
	_white = IMAGEMANAGER->addImage("white", "IMAGE/UI/white.bmp", WINSIZEX, WINSIZEY, true, RGB(0, 0, 0));
	alphaValue = 255;
	screenStatus = FADE_IN;

	_tileMap = new tileMap;
	_tileMap->init("DATA/MAP/Town.map");

	_objectManager = new objectManager;
	_objectManager->init();
	_objectManager->setTileMapMemoryAddress(_tileMap);

	_attackManager = new attackManager;
	_attackManager->init();

	_enemyManager = new enemyManager;
	_enemyManager->init(_tileMap, _attackManager, _objectManager);

	_player = new player;
	_player->setTileMapMemoryAddress(_tileMap);
	_player->setAttackManagerMemoryAddress(_attackManager);
	_player->init();
	_player->firstCollisionTileCheck();

	_playerUI = new playerUI;
	_playerUI->init();

	_collision = new collision;
	_collision->init();

	Background = RectMake(0, 0, TILESIZEX, TILESIZEY);


	_enemyManager->setBomb(21548);
	_enemyManager->setBomb(21549);
	_enemyManager->setBomb(21550);
	_enemyManager->setBomb(21551);
	_enemyManager->setBomb(21552);

	_enemyManager->setFlower(21101);

	_player->update();
	cameraInit();//카메라의 위치를 세팅합니다.
	_objectManager->setSavebell(21344);
	SOUNDMANAGER->stopAllSound();
	SOUNDMANAGER->playSound("stage1", PointMake(0, 0));
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
	_tileMap->update();
	_player->update();
	_enemyManager->update();
	_attackManager->update();
	_collision->update(_player, _enemyManager->getEnemyVector(), _attackManager->getAttackVector(), _objectManager->getItemVector());
	_objectManager->update();
	_playerUI->update();
	changeAlphaValue();
	cameraMove();
	portal();			//화면의 끝에 이동하면 field1씬으로 넘깁니다.
}

void townScene::render()
{
	_tileMap->render();							//1.맵	최하위
	_enemyManager->render();					//2.적
	_objectManager->render();					//3.아이템
	_player->render();							//4.플레이어
	_attackManager->render();					//5.공격
	_playerUI->render();						//6.인터페이스
	_black->alphaRender(getMemDC(), alphaValue);//7.전환효과 최상위
	_white->alphaRender(getMemDC(), DATABASE->getWhiteAlphaValue());//8.전환효과 최상위
}

void townScene::changeAlphaValue()
{
	switch (screenStatus)
	{
	case DARK:
		break;
	case FADE_IN:
		if (alphaValue > 0)
		{
			alphaValue -= 5;
		}
		if (alphaValue <= 0)
		{
			alphaValue = 0;
			screenStatus = SHOW;
		}
		break;
	case SHOW:
		break;
	case FADE_OUT:
		if (alphaValue < 255)
		{
			alphaValue += 5;
		}
		if (alphaValue >= 255)
		{
			alphaValue = 255;
			screenStatus = DARK;
		}
		break;
	}

	if (DATABASE->getWhiteAlphaValue() > 0)
	{
		DATABASE->setWhiteAlphaValue(DATABASE->getWhiteAlphaValue() - 5);
		if (DATABASE->getWhiteAlphaValue() < 0) DATABASE->setWhiteAlphaValue(0);
	}
}

void townScene::portal()
{
	//플레이어가 특정 타일에 닿으면 다른 타일로 이동시키는 함수.
	//이동할수 있는 타일을 좀더 넉넉하게 설정해주자.
	//충돌구간이 순간적으로 이동하기 때문에 첫 충돌을 한번더 실행시켜줘야 한다.

	switch (_player->getCollisionTile())
	{
	case 20988:
	case 20989:
	case 20990:
	case 20991:
	case 20992:
	case 21138:
	case 21139:
	case 21140:
	case 21141:
	case 21142:
	case 21288:
	case 21289:
	case 21290:
	case 21291:
	case 21292:
	case 21438:
	case 21439:
	case 21440:
	case 21441:
	case 21442:
		if (screenStatus == SHOW)
		{
			screenStatus = FADE_OUT;
		}
		if (screenStatus == DARK)
		{
			DATABASE->setCollisionTile(20557);
			SCENEMANAGER->changeScene("field1Scene");
			return;
		}
	}
	if (DATABASE->getRestart())
	{
		DATABASE->loadDataFromFile();
		this->init();
	}

	if (DATABASE->getMenu())
	{
		SCENEMANAGER->changeScene("menuScene");
		return;
	}


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
		_enemyManager->addEnemyX(diffrence);
		_objectManager->addItemX(diffrence);
	}
	if (Background.left > 0)
	{
		int diffrence = Background.left;
		Background.right -= diffrence;
		Background.left -= diffrence;
		_player->addPlayerX(+diffrence);
		_tileMap->moveTileX(-diffrence);
		_enemyManager->addEnemyX(-diffrence);
		_objectManager->addItemX(-diffrence);
	}
	if (Background.top > 0)
	{
		int diffrence = Background.top;
		Background.top -= diffrence;
		Background.bottom -= diffrence;
		_player->addPlayerY(diffrence);
		_tileMap->moveTileY(-diffrence);
		_enemyManager->addEnemyY(-diffrence);
		_objectManager->addItemY(-diffrence);
	}

	if (Background.bottom < WINSIZEY)
	{
		int diffrence = WINSIZEY - Background.bottom;
		Background.top += diffrence;
		Background.bottom += diffrence;
		_player->addPlayerY(-diffrence);
		_tileMap->moveTileY(+diffrence);
		_enemyManager->addEnemyY(diffrence);
		_objectManager->addItemY(diffrence);
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
		_objectManager->addItemX(-distanceX / 10);
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
		_objectManager->addItemX(distanceX / 10);
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
		_objectManager->addItemY(-distanceY / 10);
	}

	if (DATABASE->getSourCamY() < DATABASE->getDestCamY())		//화면 위쪽으로 움직일때
	{
		Background.top += distanceY / 10;
		Background.bottom += distanceY / 10;
		_player->addPlayerY(distanceY / 10);
		_tileMap->moveTileY(distanceY / 10);
		_attackManager->moveAttackY(distanceY / 10);
		_enemyManager->addEnemyY(distanceY / 10);
		_objectManager->addItemY(distanceY / 10);
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

HRESULT field1Scene::init()
{
	DATABASE->setBaseTime(TIMEMANAGER->getWorldTime());
	DATABASE->setDestCamX(WINSIZEX / 2);
	DATABASE->setDestCamY(WINSIZEY - 150);
	DATABASE->setMenu(false);
	DATABASE->setRestart(false);
	DATABASE->setPlayerDie(false);
	DATABASE->setBossDie(false);
	IMAGEMANAGER->addFrameImage("tileMap", "IMAGE/tile/tile.bmp", 0, 0, 1350, 1200, SAMPLETILEX, SAMPLETILEY, true, RGB(0, 0, 0));
	
	_sceneNumber = 2;
	_black = IMAGEMANAGER->addImage("black", "IMAGE/UI/black.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 255, 255));
	_white = IMAGEMANAGER->addImage("white", "IMAGE/UI/white.bmp", WINSIZEX, WINSIZEY, true, RGB(0, 0, 0));
	alphaValue = 255;
	screenStatus = FADE_IN;

	_tileMap = new tileMap;
	_tileMap->init("DATA/MAP/Field1.map");

	_objectManager = new objectManager;
	_objectManager->init();
	_objectManager->setTileMapMemoryAddress(_tileMap);

	_attackManager = new attackManager;
	_attackManager->init();

	_enemyManager = new enemyManager;
	_enemyManager->init(_tileMap, _attackManager, _objectManager);

	_player = new player;
	_player->setTileMapMemoryAddress(_tileMap);
	_player->setAttackManagerMemoryAddress(_attackManager);
	_player->init();
	_player->firstCollisionTileCheck();

	_playerUI = new playerUI;
	_playerUI->init();

	_collision = new collision;
	_collision->init();

	Background = RectMake(0, 0, TILESIZEX, TILESIZEY);	//임계영역 설정을 위해서
	_player->update();
	cameraInit();

	//적 배치 (나중에 함수로 분리하자)
	initEnemy();
	_objectManager->setSavebell(18620);
	_objectManager->setSavebell(13089);
	_objectManager->setSavebell(10405);
	_objectManager->setSavebell(6217);

	SOUNDMANAGER->stopAllSound();
	SOUNDMANAGER->play("stage2",0.5f);
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

	_objectManager->release();
	SAFE_DELETE(_objectManager);
}

void field1Scene::update()
{
	//업데이트 순서
	_tileMap->update();			//1.맵
	_player->update();			//2.플레이어
	_enemyManager->update();	//3.적
	_attackManager->update();	//4.공격
	_collision->update(_player, _enemyManager->getEnemyVector(), _attackManager->getAttackVector(), _objectManager->getItemVector());	//충돌
	_objectManager->update();	//6.아이템
	_playerUI->update();		//7.UI
	cameraMove();				//8.카메라 (이동)
	changeAlphaValue();			//9.화면 전환효과 (페이드인 , 아웃)
	portal();					//10.포탈 (특정 A좌표 -> 특정 B좌표 이동)
}

void field1Scene::render()
{
	//렌더(그리는) 순서
	_tileMap->render();							//1.맵		최하위
	_enemyManager->render();					//2.적
	_objectManager->render();					//3.아이템
	_player->render();							//4.플레이어
	_attackManager->render();					//5.공격	
	_playerUI->render();						//6.UI	
	_black->alphaRender(getMemDC(), alphaValue);//7.전환효과 최상위
	_white->alphaRender(getMemDC(), DATABASE->getWhiteAlphaValue());//8.전환효과 최상위
}

void field1Scene::initEnemy()
{
	//몬스터를 생성하는 함수입니다.
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

	_enemyManager->setBomb(8524);
	_enemyManager->setBomb(8525);
	_enemyManager->setBomb(8526);
	_enemyManager->setBomb(8527);
	_enemyManager->setBomb(8528);
	_enemyManager->setBomb(8529);
	_enemyManager->setBomb(8530);
	_enemyManager->setBomb(8531);
	_enemyManager->setBomb(8532);
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
		_enemyManager->addEnemyX(diffrence);
		_objectManager->addItemX(diffrence);
	}
	if (Background.left > 0)
	{
		int diffrence = Background.left;
		Background.right -= diffrence;
		Background.left -= diffrence;
		_player->addPlayerX(+diffrence);
		_tileMap->moveTileX(-diffrence);
		_enemyManager->addEnemyX(-diffrence);
		_objectManager->addItemX(-diffrence);
	}
	if (Background.top > 0)
	{
		int diffrence = Background.top;
		Background.top -= diffrence;
		Background.bottom -= diffrence;
		_player->addPlayerY(diffrence);
		_tileMap->moveTileY(-diffrence);
		_enemyManager->addEnemyY(-diffrence);
		_objectManager->addItemY(-diffrence);
	}

	if (Background.bottom < WINSIZEY)
	{
		int diffrence = WINSIZEY - Background.bottom;
		Background.top += diffrence;
		Background.bottom += diffrence;
		_player->addPlayerY(-diffrence);
		_tileMap->moveTileY(+diffrence);
		_enemyManager->addEnemyY(diffrence);
		_objectManager->addItemY(diffrence);
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
		_objectManager->addItemX(-distanceX / 10);
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
		_objectManager->addItemX(distanceX / 10);
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
		_objectManager->addItemY(-distanceY / 10);
	}

	if (DATABASE->getSourCamY() < DATABASE->getDestCamY())		//화면 위쪽으로 움직일때
	{
		Background.top += distanceY / 10;
		Background.bottom += distanceY / 10;
		_player->addPlayerY(distanceY / 10);
		_tileMap->moveTileY(distanceY / 10);
		_attackManager->moveAttackY(distanceY / 10);
		_enemyManager->addEnemyY(distanceY / 10);
		_objectManager->addItemY(distanceY / 10);
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
		_objectManager->addItemX(diffrence);//아이템의 움직이는 정도를 조절
	}
	if (Background.left > 0)
	{
		int diffrence = Background.left;
		Background.right -= diffrence;
		Background.left -= diffrence;
		_player->addPlayerX(+diffrence);
		_tileMap->moveTileX(-diffrence);
		_objectManager->addItemX(-diffrence);
	}
	if (Background.top > 0)
	{
		int diffrence = Background.top;
		Background.top -= diffrence;
		Background.bottom -= diffrence;
		_player->addPlayerY(diffrence);
		_tileMap->moveTileY(-diffrence);
		_objectManager->addItemY(-diffrence);
	}

	if (Background.bottom < WINSIZEY)
	{
		int diffrence = WINSIZEY - Background.bottom;
		Background.top += diffrence;
		Background.bottom += diffrence;
		_player->addPlayerY(-diffrence);
		_tileMap->moveTileY(+diffrence);
		_objectManager->addItemY(diffrence);
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
		_objectManager->addItemX(-distanceX);
	}

	if (DATABASE->getSourCamX() < DATABASE->getDestCamX())		//화면 왼쪽으로 움직일때
	{
		Background.left += distanceX;
		Background.right += distanceX;
		_player->addPlayerX(distanceX);
		_tileMap->moveTileX(distanceX);
		_attackManager->moveAttackX(distanceX);
		_enemyManager->addEnemyX(distanceX);
		_objectManager->addItemX(distanceX);
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
		_objectManager->addItemY(-distanceY);
	}

	if (DATABASE->getSourCamY() < DATABASE->getDestCamY())		//화면 위쪽으로 움직일때
	{
		Background.top += distanceY;
		Background.bottom += distanceY;
		_player->addPlayerY(distanceY);
		_tileMap->moveTileY(distanceY);
		_attackManager->moveAttackY(distanceY);
		_enemyManager->addEnemyY(distanceY);
		_objectManager->addItemY(distanceY);
	}
}

void field1Scene::changeAlphaValue()
{
	switch (screenStatus)
	{
	case DARK:
		break;
	case FADE_IN:
		if (alphaValue > 0)
		{
			alphaValue -= 5;
		}
		if (alphaValue <= 0)
		{
			alphaValue = 0;
			screenStatus = SHOW;
		}
		break;
	case SHOW:
		break;
	case FADE_OUT:
		if (alphaValue < 255)
		{
			alphaValue += 5;
		}
		if (alphaValue >= 255)
		{
			alphaValue = 255;
			screenStatus = DARK;
		}
		break;
	}

	if (DATABASE->getWhiteAlphaValue() > 0)
	{
		DATABASE->setWhiteAlphaValue(DATABASE->getWhiteAlphaValue() - 5);
		if (DATABASE->getWhiteAlphaValue() < 0) DATABASE->setWhiteAlphaValue(0);
	}

	if (DATABASE->getBossDie())
	{
		alphaValue += 2;
		if (alphaValue > 255) alphaValue = 255;
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
		//cameraInit();
		break;
	case 14748:									//2스테이지 에서 3스테이지로 넘기는 부분
	case 14749:
		_player->setPlayerTilePosition(13698);
		_player->firstCollisionTileCheck();
		_player->update();
		//cameraInit();
		break;
	case 15289:
		SOUNDMANAGER->stopAllSound();
		SOUNDMANAGER->play("stage2", 0.5f);
		_player->setPlayerTilePosition(5873);
		_player->firstCollisionTileCheck();
		_player->update();
		cameraInit();
		break;
	case 5872:
	case 5722:
	case 5572:
		SOUNDMANAGER->stopAllSound();
		SOUNDMANAGER->play("battle1", 0.5f);
		_player->setPlayerTilePosition(15137);
		_player->firstCollisionTileCheck();
		_player->update();
		cameraInit();
		break;
	}

	if (DATABASE->getGoEnding())
	{
		SOUNDMANAGER->stopAllSound();
		SCENEMANAGER->changeScene("endingScene");
		return;
	}
	if (DATABASE->getRestart())
	{
		DATABASE->loadDataFromFile();
		this->init();
	}

	if (DATABASE->getMenu())
	{
		SCENEMANAGER->changeScene("menuScene");
		return;
	}
}

field1Scene::field1Scene()
{

}

field1Scene::~field1Scene()
{

}

HRESULT endingScene::init()
{
	_IMG1 = IMAGEMANAGER->addImage("ending1", "IMAGE/background/ending1.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 255, 255));
	_IMG2 = IMAGEMANAGER->addImage("ending2", "IMAGE/background/ending2.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 255, 255));
	_IMG3 = IMAGEMANAGER->addImage("ending3", "IMAGE/background/ending3.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 255, 255));
	_IMG4 = IMAGEMANAGER->addImage("ending4", "IMAGE/background/ending4.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 255, 255));
	_black = IMAGEMANAGER->addImage("black", "IMAGE/background/black.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 255, 255));

	SOUNDMANAGER->addSound("endingSound", "SOUND/ending.ogg", true, true);
	SOUNDMANAGER->playSound("endingSound", PointMake(0, 0));
	alphaValue = 255;
	IMGNumber = 1;
	fadein = false;
	return S_OK;
}

void endingScene::release()
{
}

void endingScene::update()
{
	if (fadein && IMGNumber < 4)
	{
		alphaValue++;
		if (alphaValue > 255)
		{
			alphaValue = 255;
			if (IMGNumber < 4)
			{
				IMGNumber++;
				fadein = false;
			}
		}
	}

	if (!fadein)
	{
		alphaValue--;
		if (alphaValue < 0)
		{
			alphaValue = 0;
			fadein = true;
		}
	}
}

void endingScene::render()
{
	switch (IMGNumber)
	{
	case 1: _IMG1->render(getMemDC()); break;
	case 2: _IMG2->render(getMemDC()); break;
	case 3: _IMG3->render(getMemDC()); break;
	case 4: _IMG4->render(getMemDC()); break;
	}
	_black->alphaRender(getMemDC(), alphaValue);
}

endingScene::endingScene()
{
}

endingScene::~endingScene()
{
}

HRESULT testScene::init()
{
	DATABASE->loadDataFromFile();	//파일로부터 플레이어의 데이터를 불러와 셋팅합니다. 앞으로 플레이어의 초기화에 필요합니다.
	DATABASE->setBaseTime(TIMEMANAGER->getWorldTime());
	DATABASE->setDestCamX(WINSIZEX / 2);
	DATABASE->setDestCamY(WINSIZEY / 2);
	IMAGEMANAGER->addFrameImage("tileMap", "IMAGE/tile/tile.bmp", 0, 0, 1350, 1200, SAMPLETILEX, SAMPLETILEY, true, RGB(0, 0, 0));
	_image = IMAGEMANAGER->addImage("흰배경", "IMAGE/whiteBackground.bmp", WINSIZEX, WINSIZEY, false, RGB(0, 0, 0));

	_tileMap = new tileMap;
	_tileMap->init("DATA/MAP/Field1.map");

	_objectManager = new objectManager;
	_objectManager->init();

	_attackManager = new attackManager;
	_attackManager->init();

	_enemyManager = new enemyManager;
	_enemyManager->init(_tileMap, _attackManager, _objectManager);

	//플레이어를 초기화 하기 전에 싱글톤에 데이터를 로드 해줘야 합니다.
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
	//_test = IMAGEMANAGER->addImage("테스트배경", "IMAGE/test.bmp", TILESIZEX, TILESIZEY, false, RGB(0, 0, 0));
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

	_objectManager->release();
	SAFE_DELETE(_objectManager);
}

void testScene::update()
{
	_player->update();											//플레이어에서 보고자 하는 대상의 위치를 먼저 전송합니다.
	_playerUI->update();
	_attackManager->update();
	_enemyManager->update();
	_tileMap->update();
	_objectManager->update();
	_collision->update(_player, _enemyManager->getEnemyVector(), _attackManager->getAttackVector(), _objectManager->getItemVector());
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

	if (KEYMANAGER->isOnceKeyDown('H'))
	{
		_saveCount = 2;
		DATABASE->saveDataToFile();
	}
	//좌표 설정이 끝난뒤에 Camera함수에 진입합니다.
	cameraMove();
	portal();
}

void testScene::render()
{
	_tileMap->render();
	_enemyManager->render();
	_player->render();
	_attackManager->render();
	_objectManager->render();
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
		_enemyManager->addEnemyX(diffrence);
		_objectManager->addItemX(diffrence);
	}
	if (Background.left > 0)
	{
		int diffrence = Background.left;
		Background.right -= diffrence;
		Background.left -= diffrence;
		_player->addPlayerX(+diffrence);
		_tileMap->moveTileX(-diffrence);
		_enemyManager->addEnemyX(-diffrence);
		_objectManager->addItemX(-diffrence);
	}
	if (Background.top > 0)
	{
		int diffrence = Background.top;
		Background.top -= diffrence;
		Background.bottom -= diffrence;
		_player->addPlayerY(diffrence);
		_tileMap->moveTileY(-diffrence);
		_enemyManager->addEnemyY(-diffrence);
		_objectManager->addItemY(-diffrence);
	}

	if (Background.bottom < WINSIZEY)
	{
		int diffrence = WINSIZEY - Background.bottom;
		Background.top += diffrence;
		Background.bottom += diffrence;
		_player->addPlayerY(-diffrence);
		_tileMap->moveTileY(+diffrence);
		_enemyManager->addEnemyY(diffrence);
		_objectManager->addItemY(diffrence);
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
		_objectManager->addItemX(-distanceX / 10);
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
		_objectManager->addItemX(distanceX / 10);
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
		_objectManager->addItemY(-distanceY / 10);
	}

	if (DATABASE->getSourCamY() < DATABASE->getDestCamY())		//화면 위쪽으로 움직일때
	{
		Background.top += distanceY / 10;
		Background.bottom += distanceY / 10;
		_player->addPlayerY(distanceY / 10);
		_tileMap->moveTileY(distanceY / 10);
		_attackManager->moveAttackY(distanceY / 10);
		_enemyManager->addEnemyY(distanceY / 10);
		_objectManager->addItemY(distanceY / 10);
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
		_objectManager->addItemX(diffrence);
	}
	if (Background.left > 0)
	{
		int diffrence = Background.left;
		Background.right -= diffrence;
		Background.left -= diffrence;
		_player->addPlayerX(+diffrence);
		_tileMap->moveTileX(-diffrence);
		_objectManager->addItemX(-diffrence);
	}
	if (Background.top > 0)
	{
		int diffrence = Background.top;
		Background.top -= diffrence;
		Background.bottom -= diffrence;
		_player->addPlayerY(diffrence);
		_tileMap->moveTileY(-diffrence);
		_objectManager->addItemY(-diffrence);
	}

	if (Background.bottom < WINSIZEY)
	{
		int diffrence = WINSIZEY - Background.bottom;
		Background.top += diffrence;
		Background.bottom += diffrence;
		_player->addPlayerY(-diffrence);
		_tileMap->moveTileY(+diffrence);
		_objectManager->addItemY(diffrence);
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
		_objectManager->addItemX(-distanceX);
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