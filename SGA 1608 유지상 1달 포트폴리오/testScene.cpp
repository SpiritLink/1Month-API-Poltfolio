#include "stdafx.h"
#include "testScene.h"


HRESULT testScene::init()
{
	DATABASE->setBaseTime(TIMEMANAGER->getWorldTime());
	DATABASE->setDestCamX(WINSIZEX / 2);
	DATABASE->setDestCamY(WINSIZEY / 2);
	IMAGEMANAGER->addFrameImage("tileMap", "IMAGE/tile/tile.bmp", 0, 0, 1350, 1200, SAMPLETILEX, SAMPLETILEY, true, RGB(0, 0, 0));
	_image = IMAGEMANAGER->addImage("����", "IMAGE/whiteBackground.bmp", WINSIZEX, WINSIZEY, false, RGB(0, 0, 0));

	_tileMap = new tileMap;
	_tileMap->init("DATA/MAP/Town.map");

	_player = new player;
	_player->init();
	_player->setTileMapMemoryAddress(_tileMap);
	_player->firstCollisionTileCheck();

	cameraX = 0;
	cameraY = 0;

	_test = IMAGEMANAGER->addImage("�׽�Ʈ���", "IMAGE/test.bmp", TILESIZEX, TILESIZEY, false, RGB(0, 0, 0));
	Background = RectMake(0, 0, _test->getWidth(), _test->getHeight());
	return S_OK;
}

void testScene::release()
{
	_player->release();
	SAFE_DELETE(_player);

	_tileMap->release();
	SAFE_DELETE(_tileMap);
}

void testScene::update()
{
	_player->update();											//�÷��̾�� ������ �ϴ� ����� ��ġ�� ���� �����մϴ�.

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
	
	//��ǥ ������ �����ڿ� Camera�Լ��� �����մϴ�.
	cameraMove();

}

void testScene::render()
{
	_image->render(getMemDC());
	Rectangle(getMemDC(), Background.left, Background.top, Background.right, Background.bottom);
	_test->render(getMemDC(), Background.left, Background.top);
	_tileMap->render();
	_player->render();
	if (KEYMANAGER->isToggleKey(VK_SHIFT)) _tileMap->miniMapRender();

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
	}

	if (DATABASE->getSourCamX() < DATABASE->getDestCamX())		//ȭ�� �������� �����϶�
	{
		Background.left += distanceX / 10;
		Background.right += distanceX / 10;
		_player->addPlayerX(distanceX / 10);
		_tileMap->moveTileX(distanceX / 10);
	}

	//Y��ǥ �̵�
	if (DATABASE->getSourCamY() > DATABASE->getDestCamY())		//ȭ�� �Ʒ������� �����϶�
	{
		Background.top -= distanceY / 10;
		Background.bottom -= distanceY / 10;
		_player->addPlayerY(-distanceY / 10);
		_tileMap->moveTileY(-distanceY / 10);
	}

	if (DATABASE->getSourCamY() < DATABASE->getDestCamY())		//ȭ�� �������� �����϶�
	{
		Background.top += distanceY / 10;
		Background.bottom += distanceY / 10;
		_player->addPlayerY(distanceY / 10);
		_tileMap->moveTileY(distanceY / 10);
	}
}


testScene::testScene()
{
}

testScene::~testScene()
{
}
