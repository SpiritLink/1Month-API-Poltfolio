#include "stdafx.h"
#include "player.h"


HRESULT player::init()
{
	playerIMG = IMAGEMANAGER->addFrameImage("player", "IMAGE/player/player.bmp", 672, 512, 7, 8, true, RGB(0, 0, 255));
	x = WINSIZEX / 2;
	y = WINSIZEY / 2;
	gravity = 0;
	PlayerRect = RectMakeCenter(x, y, 50, 50);
	STR = DEFAULT_STR;
	DEF = DEFAULT_DEF;
	SPEED = DEFAULT_SPEED;
	ATK = STR * 3;

	keyStatus = 0;
	playerStatus = 0;

	direction = RIGHT;
	frameCount = 0;
	return S_OK;
}

void player::release()
{
}

void player::update()
{
	collisionTileCheck();	//��� Ÿ�Ͽ� �浹������
	keyboardInput();		//� Ű���� �Է��� �޾Ҵ���
	playerStatusCheck();	//�÷��̾��� ���´� ���
	playerMove();			//�÷��̾��� ���¿� Ű������ ���¿� ���� �������� ������

	//

	PlayerRect = RectMakeCenter(x, y, 5, 5);

	DATABASE->setSourCamX(x);							//������ �� ��ǥ�� �÷��̾� X��ǥ�� �����Ѵ�.
	DATABASE->setSourCamY(y);							//������ �� ��ǥ�� �÷��̾� y��ǥ�� �����Ѵ�.
	DATABASE->setCollisionTile(currentCollisionTile);	//������ �� Ÿ���� �÷��̾� �浹 Ÿ�Ϲ�ȣ�� �����Ѵ�.

}

void player::render()
{
	playerRender();	//�÷��̾ �׸��� �Լ�
	Rectangle(getMemDC(), PlayerRect.left, PlayerRect.top, PlayerRect.right, PlayerRect.bottom);	//�浹������ ������
	testFunction();	//���� ǥ���ϱ� ���� �׽�Ʈ�� �Լ�.
}

void player::keyboardInput()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))	keyStatus = keyStatus | KEYBOARD_LEFT;
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))keyStatus += KEYBOARD_RIGHT;
	if (KEYMANAGER->isOnceKeyDown(VK_UP))	keyStatus += KEYBOARD_UP;
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))	keyStatus += KEYBOARD_DOWN;
	if (KEYMANAGER->isOnceKeyDown('Z'))		keyStatus += KEYBOARD_Z;
	if (KEYMANAGER->isOnceKeyDown('X'))		keyStatus += KEYBOARD_X;
	if (KEYMANAGER->isOnceKeyDown('C'))		keyStatus += KEYBOARD_C;

	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))	keyStatus -= KEYBOARD_LEFT;
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))	keyStatus -= KEYBOARD_RIGHT;
	if (KEYMANAGER->isOnceKeyUp(VK_UP))		keyStatus -= KEYBOARD_UP;
	if (KEYMANAGER->isOnceKeyUp(VK_DOWN))	keyStatus -= KEYBOARD_DOWN;
	if (KEYMANAGER->isOnceKeyUp('Z'))		keyStatus -= KEYBOARD_Z;
	if (KEYMANAGER->isOnceKeyUp('X'))		keyStatus -= KEYBOARD_X;
	if (KEYMANAGER->isOnceKeyUp('C'))		keyStatus -= KEYBOARD_C;

	

	//�������, ���� Ű�� ������ ������ �ٷ� ���Եȴ�.
	if (keyStatus & KEYBOARD_LEFT) direction = LEFT;
	if (keyStatus & KEYBOARD_RIGHT) direction = RIGHT;
	//if (keyStatus & KEYBOARD_UP) direction = UP;
	//if (keyStatus & KEYBOARD_DOWN) direction = DOWN;
}

void player::playerMove()
{
	//�߷�ó��
	gravity += GRAVITY;
	//�÷��̾�� Ÿ���� �浹�� ó��
	if (_tileMap->getTiles()[currentCollisionTile].obj == OBJ_GROUND)
	{
		gravity = 0;
		y = _tileMap->getTiles()[currentCollisionTile].rc.top;
	}

	//Ű���� �Է��� ó��
	if (keyStatus & KEYBOARD_LEFT) x -= SPEED;
	if (keyStatus & KEYBOARD_RIGHT) x += SPEED;
	if (keyStatus & KEYBOARD_UP) y -= SPEED;
	if (keyStatus & KEYBOARD_DOWN) y += SPEED;
	if (keyStatus & KEYBOARD_X) gravity = -10;

	//Ÿ���� �Ӽ��� ������.
	y += gravity;
}

void player::testFunction()
{
	char str1[128];
	char str2[128];
	char str3[128];
	char str4[128];
	char str5[128];
	char str6[128];
	char str7[128];
	char str8[128];
	char str9[128];
	char str10[128];

	if (keyStatus & KEYBOARD_LEFT)	sprintf(str1, "��"); else sprintf(str1, " ");
	if (keyStatus & KEYBOARD_RIGHT) sprintf(str2, "��"); else sprintf(str2, " ");
	if (keyStatus & KEYBOARD_UP)	sprintf(str3, "��"); else sprintf(str3, " ");
	if (keyStatus & KEYBOARD_DOWN)	sprintf(str4, "��"); else sprintf(str4, " ");
	if (keyStatus & KEYBOARD_Z)		sprintf(str5, "Z"); else sprintf(str5, " ");
	if (keyStatus & KEYBOARD_X)		sprintf(str6, "X"); else sprintf(str6, " ");
	if (keyStatus & KEYBOARD_C)		sprintf(str7, "C"); else sprintf(str7, " ");
	sprintf(str8, "%d", currentCollisionTile);
	sprintf(str9, "%0.3f", gravity);
	sprintf(str10, "%d", playerStatus);

	SetTextColor(getMemDC(), RGB(255, 255, 255));
	TextOut(getMemDC(), 300, 20, str1, strlen(str1));
	TextOut(getMemDC(), 320, 20, str2, strlen(str2));
	TextOut(getMemDC(), 340, 20, str3, strlen(str3));
	TextOut(getMemDC(), 360, 20, str4, strlen(str4));
	TextOut(getMemDC(), 380, 20, str5, strlen(str5));
	TextOut(getMemDC(), 400, 20, str6, strlen(str6));
	TextOut(getMemDC(), 420, 20, str7, strlen(str7));
	TextOut(getMemDC(), 440, 20, str8, strlen(str8));
	TextOut(getMemDC(), 480, 20, str9, strlen(str9));
	TextOut(getMemDC(), 300, 40, str10, strlen(str10));

}

void player::playerStatusCheck()
{
	if (gravity > 0)
	{
		playerStatus = playerStatus | STATUS_JUMP;						//���� ���·� ������
		if (playerStatus & STATUS_LAND) playerStatus -= STATUS_LAND;	//���� ���¸� �����Ѵ�.
		if (playerStatus & STATUS_RUN) playerStatus -= STATUS_RUN;		//�޸� ���¸� �����Ѵ�.
		if (playerStatus & STATUS_STAND) playerStatus -= STATUS_STAND;
	}
	if (gravity < 0)
	{
		playerStatus = playerStatus | STATUS_LAND;						//���� ���·� ������.
		if (playerStatus & STATUS_JUMP) playerStatus -= STATUS_JUMP;	//���� ���¸� �����Ѵ�.
		if (playerStatus & STATUS_RUN) playerStatus -= STATUS_RUN;		//�޸� ���¸� �����Ѵ�.
		if (playerStatus & STATUS_STAND) playerStatus -= STATUS_STAND;
	}
	if (gravity == 0)
	{
		if (!(keyStatus & KEYBOARD_LEFT) && !(keyStatus & KEYBOARD_RIGHT))
		{
			playerStatus = playerStatus | STATUS_STAND;
			if (playerStatus & STATUS_RUN) playerStatus -= STATUS_RUN;
		}
		if (keyStatus & KEYBOARD_LEFT || keyStatus & KEYBOARD_RIGHT)
		{
			playerStatus = playerStatus | STATUS_RUN;
			if (playerStatus & STATUS_STAND) playerStatus -= STATUS_STAND;
		}
		if (playerStatus & STATUS_JUMP)	playerStatus -= STATUS_JUMP;
		if (playerStatus & STATUS_LAND) playerStatus -= STATUS_LAND;
	}

	
}

void player::firstCollisionTileCheck()
{
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		if (PtInRect(&_tileMap->getTiles()[i].rc, PointMake(x, y)))
		{
			currentCollisionTile = i;
			break;
		}
	}
}

void player::collisionTileCheck()
{
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		if (PtInRect(&_tileMap->getTiles()[i].rc, PointMake(x, y)))
		{
			currentCollisionTile = i;
			break;
		}
	}
}

void player::playerRender()
{
	//�������� ������Ű�� �κ�
	switch (playerStatus)
	{
	case STATUS_STAND:
		frameCount = 0;
		break;
	case STATUS_RUN:
		++frameCount;
		if (frameCount > 5) frameCount = 0;
		break;
	case STATUS_JUMP:
		++frameCount;
		if (frameCount > 1) frameCount = 0;
		break;
	case STATUS_LAND:
		++frameCount;
		if (frameCount > 1) frameCount = 0;
		break;
	}

	//����� ���¿� ���� �����ϴ� �κ�
	switch (direction)
	{
	case RIGHT:
		if(playerStatus & STATUS_STAND)
			playerIMG->frameRender(getMemDC(), x - playerIMG->getFrameWidth() / 2, y - playerIMG->getFrameHeight(), frameCount, 0);
		if(playerStatus & STATUS_RUN)
			playerIMG->frameRender(getMemDC(), x - playerIMG->getFrameWidth() / 2, y - playerIMG->getFrameHeight(), frameCount, 2);
		if (playerStatus & STATUS_JUMP)
			playerIMG->frameRender(getMemDC(), x - playerIMG->getFrameWidth() / 2, y - playerIMG->getFrameHeight(), frameCount, 6);
		if(playerStatus & STATUS_LAND)
			playerIMG->frameRender(getMemDC(), x - playerIMG->getFrameWidth() / 2, y - playerIMG->getFrameHeight(), frameCount, 4);
		break;
	case UP:
		break;
	case LEFT:
		if(playerStatus & STATUS_STAND)
			playerIMG->frameRender(getMemDC(), x - playerIMG->getFrameWidth() / 2, y - playerIMG->getFrameHeight(), frameCount, 1);
		if (playerStatus & STATUS_RUN)
			playerIMG->frameRender(getMemDC(), x - playerIMG->getFrameWidth() / 2, y - playerIMG->getFrameHeight(), frameCount, 3);
		if(playerStatus & STATUS_JUMP)
			playerIMG->frameRender(getMemDC(), x - playerIMG->getFrameWidth() / 2, y - playerIMG->getFrameHeight(), frameCount, 7);
		if (playerStatus & STATUS_LAND)
			playerIMG->frameRender(getMemDC(), x - playerIMG->getFrameWidth() / 2, y - playerIMG->getFrameHeight(), frameCount, 5);
		break;
	case DOWN:
		break;
	}

}

player::player()
{
}


player::~player()
{
}
