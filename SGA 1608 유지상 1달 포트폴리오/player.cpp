#include "stdafx.h"
#include "player.h"


HRESULT player::init()
{
	playerIMG = IMAGEMANAGER->addFrameImage("player", "IMAGE/player/player.bmp", IMAGESIZEX * 2, IMAGESIZEY * 2, 7, 18, true, RGB(0, 0, 255));
	//x = DATABASE->getPlayerX();	//�̱������� ����
	//y = DATABASE->getPlayerY();	//�̱������� ����
	//MAXHP = DATABASE->getMaxHP();
	//HP = DATABASE->getHP();
	//MP = DATABASE->getMP();
	x = WINSIZEX / 2;
	y = WINSIZEY / 2;
	MAXHP = 6;
	HP = 6;
	MP = 3;
	gravity = 0;
	PlayerRect = RectMakeCenter(x, y, 50, 50);
	SPEED = DEFAULT_SPEED;
	currentTime = TIMEMANAGER->getWorldTime();
	invincibleTime = TIMEMANAGER->getWorldTime();
	countTime = 0;

	keyStatus = 0;
	playerStatus = 0;

	direction = RIGHT;
	Action = ACTION_NONE;
	frameCount = 0;

	alphaValue = 255;
	SOUNDMANAGER->addSound("playerSlash", "SOUND/punch2.wav", false, false);
	SOUNDMANAGER->addSound("playerThrow", "SOUND/seal.wav", false, false);
	SOUNDMANAGER->addSound("hit", "SOUND/hit.wav", false, false);
	SOUNDMANAGER->addSound("jump", "SOUND/jump.wav", false, false);
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
	if(KEYMANAGER->isToggleKey('Y')) playerMove();			//�÷��̾��� ���¿� Ű������ ���¿� ���� �������� ������
	if(!(KEYMANAGER->isToggleKey('Y'))) testPlayerMove();
	sendDataToSingleton();	//�÷��̾��� �����͸� �̱������� �����մϴ�.

	PlayerRect = RectMake(x - PLAYERAREAX / 2, y - PLAYERAREAY + 10, PLAYERAREAX, PLAYERAREAY);
}

void player::render()
{
	playerRender();	//�÷��̾ �׸��� �Լ�
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
}

void player::playerMove()
{
	//�߷��� �׻� ������ŵ�ϴ�. (�� �߷��� Ÿ�� �Ѱ��� ũ�� ���ٴ� ����)
	if(gravity < TILESIZE) gravity += GRAVITY;
	//Ű���� �� , �� �Է��� ó���ϴ� �κ��Դϴ�.
	if (keyStatus & KEYBOARD_LEFT)
	{
		//�߷°� �Բ� ���������� �밢�� Ÿ�Ϸ� �̵��ϴ��� �˻��մϴ�.
		if (gravity < 0 && PtInRect(&_tileMap->getTiles()[currentCollisionTile - 1 - TILEX].rc, PointMake(x - SPEED, y + gravity)))
		{
			switch (_tileMap->getTiles()[currentCollisionTile - 1 - TILEX].obj)
			{
			case OBJ_GROUND:
				break;
			case OBJ_PIXEL:
				break;
			case OBJ_NONE: 
				x -= SPEED;
				break;
			}
		}
		//�밢��Ÿ�Ϸ� �̵����� �ʴ´ٸ� ��Ÿ�Ϸ� �̵��ϴ��� Ȯ���մϴ�.
		else if (PtInRect(&_tileMap->getTiles()[currentCollisionTile - 1].rc, PointMake(x - SPEED, y)))	//�̵��ϰ� ���� ��ǥ�� ���� Ÿ�Ͽ� �������						
		{
			switch (_tileMap->getTiles()[currentCollisionTile - 1].obj)
			{
			case OBJ_GROUND:
				break;
			case OBJ_PIXEL://�̶� y��ǥ�� �ȼ�Ȯ���� �̵�������� �Ѵ�.
				x -= SPEED;
				break;
			case OBJ_NONE:
				x -= SPEED;
				break;
			}
		}
		//�ٸ� Ÿ�Ϸ� �̵� ���� Ÿ�� �Ѱ� ������ �����δٸ�
		else																						//�̵��ص� ��Ÿ�Ͽ� �ȴ�´ٸ�
			x -= SPEED;																				//�̵��Ѵ�.
	}
	if (keyStatus & KEYBOARD_RIGHT)
	{
		//�߷°� �Բ� ���������� ������ Ÿ�Ϸ� �̵��ϴ��� �˻��մϴ�.
		if (gravity < 0 && PtInRect(&_tileMap->getTiles()[currentCollisionTile + 1 - TILEX].rc, PointMake(x + SPEED, y + gravity)))
		{
			switch (_tileMap->getTiles()[currentCollisionTile + 1 - TILEX].obj)
			{
			case OBJ_GROUND:
				break;
			case OBJ_PIXEL:
				break;
			case OBJ_NONE: 
				x += SPEED;
				break;
			}
		}
		//�밢�� Ÿ�Ϸ� �̵����� �ʴ´ٸ� ��Ÿ�Ϸ� �̵��ϴ��� Ȯ���մϴ�.
		else if (PtInRect(&_tileMap->getTiles()[currentCollisionTile + 1].rc, PointMake(x + SPEED, y)))	//�̵��ϰ� ���� ��ǥ�� ������ Ÿ�Ͽ� �������						
		{
			switch (_tileMap->getTiles()[currentCollisionTile + 1].obj)
			{
			case OBJ_GROUND:
				break;
			case OBJ_PIXEL://�̶� ���⼭ ����Ÿ���� �ȼ��� Ȯ���ϰ� y��ǥ�� �������� ����Ѵ�.
			{
				int playerTileX, playerTileY;
				playerTileX = x + SPEED - _tileMap->getTiles()[currentCollisionTile + 1].rc.left;
				playerTileY = y - _tileMap->getTiles()[currentCollisionTile].rc.top;

				//Ÿ���� frameX, frameY�� �̿��� �̹������� ã�� �κ��� ������ ���մϴ�.
				//�̹����� ���� 1:1������ ���ǰ� �ֱ� ������ ��ǥ�� �������� �״�� �������ݴϴ�.
				int imageX, imageY;
				imageX = _tileMap->getTileObjX(currentCollisionTile + 1) * TILESIZE;
				imageY = _tileMap->getTileObjY(currentCollisionTile) * TILESIZE;

				//�ȼ��浹 ���꿡 ����� ��ǥ�� ���մϴ�.
				int pixelX, pixelY;
				pixelX = playerTileX + imageX;
				pixelY = playerTileY + imageY;

				//������ ������ ������ �ӽ� ����
				COLORREF color;

				//���ϴ� ��ǥ�� ���� ������ �̹������� ���ɴϴ�
				color = GetPixel(IMAGEMANAGER->findImage("tilePIXEL")->getMemDC(), pixelX, pixelY);

				//��ǥ�� RGB���� ������ �����մϴ�
				int r = GetRValue(color);
				int g = GetGValue(color);
				int b = GetBValue(color);

				//�̹����� �ִ� �κ��̶�� y�� ��ǥ�� �����մϴ�.
				if(r != 0 || g != 0 || b != 0)
				{
					for (int i = imageY + playerTileY; i > imageY - TILESIZE; --i)
					{
						COLORREF tempColor;
						tempColor = GetPixel(IMAGEMANAGER->findImage("tilePIXEL")->getMemDC(), pixelX, i);

						int tempR = GetRValue(tempColor);
						int tempG = GetGValue(tempColor);
						int tempB = GetBValue(tempColor);

						if (tempR != 0 || tempG != 0 || tempB != 0)
						{
							y = _tileMap->getTiles()[currentCollisionTile].rc.top + (i % 50);
							gravity = 0;
							break;
						}
					}
				}
				x += SPEED;
			}

				break;
			case OBJ_NONE:
				x += SPEED;
				break;
			}
		}
		//�ٸ� Ÿ�Ϸ� �̵� ���� Ÿ�� �Ѱ� ������ �����δٸ�.
		else																						//�̵��ص� ��Ÿ�Ͽ� �ȴ�´ٸ�
			x += SPEED;																				//�̵��Ѵ�.
	}
	if (keyStatus & KEYBOARD_X)
	{
		if (!(Action & ACTION_JUMP))					//�̹� ������ �� ���°� �ƴ϶��
		{
			SOUNDMANAGER->playSound("jump", PointMake(x, y));
			Action = Action | ACTION_JUMP;				//���¿� ������ �־��ݴϴ�.
			gravity = -15;								//�߷��� �ٲ��ش�.
		}
	}

	//���� �浹�ϰ� �ִ� Ÿ���� ������ ���� �������� �����մϴ�.
	switch (_tileMap->getTiles()[currentCollisionTile].obj)
	{
	case OBJ_NONE:
		//�߷��� ȭ�� ������� ���Ҷ�
		if (gravity < 0)
		{	//�߷¸�ŭ �̵��ؼ� �ٷ� ��Ÿ�ϰ� �浹�ϴ��� Ȯ���մϴ�.
			if (PtInRect(&_tileMap->getTiles()[currentCollisionTile - TILEX].rc, PointMake(x, y + gravity)))
			{	//���� ��Ÿ�Ͽ� �浹������ ��Ÿ���� ���̶��
				if (_tileMap->getTiles()[currentCollisionTile - TILEX].obj == OBJ_GROUND ||
					_tileMap->getTiles()[currentCollisionTile - TILEX].obj == OBJ_PIXEL)
				{	//��Ÿ���� ���� + 1 ��ǥ�� �÷��̾� y��ǥ�� ������ŵ�ϴ�.
					y = _tileMap->getTiles()[currentCollisionTile - TILEX].rc.bottom + 1;
					gravity = 0;
				}
				else
				{	//��Ÿ���� ���� �ƴ϶�� �߷¸�ŭ �̵���ŵ�ϴ�.
					y += gravity;
				}
			}
			else
			{	//�߷¸�ŭ �̵��ص� ��Ÿ�ϳ����� �����δٸ� �̵���ŵ�ϴ�.
				y += gravity;
			}
		}

		//�߷��� ȭ�� �ϴ����� ���Ҷ�
		if (gravity > 0)
		{	//�߷¸�ŭ �̵��ؼ� �ٷ� �Ʒ� Ÿ�ϰ� �浹�ϴ��� Ȯ���մϴ�.
			if (PtInRect(&_tileMap->getTiles()[currentCollisionTile + TILEX].rc, PointMake(x, y + gravity)))
			{	//���� ��ǥ�� �Ʒ�Ÿ�Ϸ� �Ѿ�ٸ�
				switch (_tileMap->getTiles()[currentCollisionTile + TILEX].obj)
				{
				case OBJ_GROUND:
					gravity = 0;	//�߷��� 0���� �����ŵ�ϴ�.
					y = _tileMap->getTiles()[currentCollisionTile + TILEX].rc.top - 1;	//Ÿ���� top - 1�� ��ǥ�� �����մϴ�.
					if (Action & ACTION_JUMP) Action -= ACTION_JUMP;					//������ �ٽ� �Ҽ��ְ� ���¸� �����ŵ�ϴ�.
					break;
				case OBJ_PIXEL:
					//�� Ÿ�� ������ �÷��̾��� ��ǥ�� ���մϴ�.
					//�߷��� ������ִٴ� ������ ����ֱ� ������ �����ǥ���� �̸� �߷��� �����ŵ�ϴ�.
					int playerTileX, playerTileY;
					playerTileX = x - _tileMap->getTiles()[currentCollisionTile + TILEX].rc.left;
					playerTileY = y + gravity - _tileMap->getTiles()[currentCollisionTile + TILEX].rc.top;

					//Ÿ���� frameX, frameY�� �̿��� �̹������� ã�� �κ��� ������ ���մϴ�.
					//�̹����� ���� 1:1������ ���ǰ� �ֱ� ������ ��ǥ�� �������� �״�� �������ݴϴ�.
					int imageX, imageY;
					imageX = _tileMap->getTileObjX(currentCollisionTile + TILEX) * TILESIZE;
					imageY = _tileMap->getTileObjY(currentCollisionTile + TILEX) * TILESIZE;

					//�ȼ��浹 ���꿡 ����� ��ǥ�� ���մϴ�.
					int pixelX, pixelY;
					pixelX = playerTileX + imageX;
					pixelY = playerTileY + imageY;

					//������ ������ �޾ƿ� �ӽú����� �����մϴ�.
					COLORREF color;
					color = GetPixel(IMAGEMANAGER->findImage("tileMap")->getMemDC(), pixelX, pixelY);
					//�̹����� �ִ� �κ��� �ƴ϶�� �߷¸�ŭ �̵��մϴ�.
					if (GetRValue(color) == 0 && GetGValue(color) == 0 && GetBValue(color) == 0) y += gravity;
					//�̹����� �ִ� �κ��̶�� y��ǥ�� �����մϴ�.
					else
					{
						//���� ������ �Ұ����� ���¶�� ������ ���·� �����մϴ�.
						if (Action & ACTION_JUMP) Action -= ACTION_JUMP;
						y -= 1;
						gravity = -1;
					}
					break;
				case OBJ_NONE:
					y += gravity;
					break;
				}
			}
			else
			{//�߷¸�ŭ �̵��ص� �� Ÿ�ϳ����� �̵��Ѵٸ� �߷¸�ŭ �̵���ŵ�ϴ�.
				y += gravity;
			}
		}
		break;
	case OBJ_GROUND:												//GROUND Ÿ�� ó��
		y = _tileMap->getTiles()[currentCollisionTile].rc.top - 1;	//��ǥ	����
		gravity = 0;												//�߷�	����
		break;
	case OBJ_PIXEL:													//PIXEL Ÿ�� ó��
		//���� ��ġ�� Ÿ�� ������ �÷��̾��� ��ǥ�� ���մϴ�.
		int playerTileX, playerTileY;
		playerTileX = x - _tileMap->getTiles()[currentCollisionTile].rc.left;
		playerTileY = y - _tileMap->getTiles()[currentCollisionTile].rc.top;

		//Ÿ���� frameX, frameY�� �̿��� �̹������� ã�� �κ��� ������ ���մϴ�.
		//�̹����� ���� 1:1������ ���ǰ� �ֱ� ������ ��ǥ�� �������� �״�� �������ݴϴ�.
		int imageX, imageY;
		imageX = _tileMap->getTileObjX(currentCollisionTile) * TILESIZE;
		imageY = _tileMap->getTileObjY(currentCollisionTile) * TILESIZE;

		//�ȼ��浹 ���꿡 ����� ��ǥ�� ���մϴ�.
		int pixelX, pixelY;
		pixelX = playerTileX + imageX;
		pixelY = playerTileY + imageY;

		//������ ������ ������ �ӽ� ����
		COLORREF color;

		//���ϴ� ��ǥ�� ���� ������ �̹������� ���ɴϴ�
		color = GetPixel(IMAGEMANAGER->findImage("tilePIXEL")->getMemDC(), pixelX, pixelY);

		//��ǥ�� RGB���� ������ �����մϴ�
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		//�̹����� ���� �κ��̶�� y�� �߷°� ��ŭ �̵��� �ݴϴ�.
		//���⼭ �߷��� 1�϶� �����鼭 �������� ������ ��������� �ҵ�.
		if (r != 0 && g != 0 && b != 0)		y += gravity;
		//�̹����� �ִ� �κ��̶�� y�� ��ǥ�� �����մϴ�.
		else
		{
			if (Action & ACTION_JUMP)	Action -= ACTION_JUMP;	//���� ���¸� ����
			if (gravity > 0)	gravity = 0;					//�߷� ����

			for (int i = imageY + playerTileY; i > imageY - TILESIZE; --i)
			{
				COLORREF tempColor;
				tempColor = GetPixel(IMAGEMANAGER->findImage("tilePIXEL")->getMemDC(), pixelX, i);

				int tempR = GetRValue(tempColor);
				int tempG = GetGValue(tempColor);
				int tempB = GetBValue(tempColor);

				if ((tempR != 0 || tempG != 0 || tempB != 0) && i > imageY)
				{
					y = _tileMap->getTiles()[currentCollisionTile].rc.top + (i % 50);
					gravity = 0;
					break;
				}

				if ((tempR != 0 || tempG != 0 || tempB != 0) && i < imageY)
				{
					y = _tileMap->getTiles()[currentCollisionTile - TILEX].rc.top + (i % 50);
					gravity = 0;
					break;
				}
			}
		}
		break;
	}
}

void player::playerAttack()
{
	if (keyStatus & KEYBOARD_Z && !(keyStatus & KEYBOARD_UP))	//�������� Ű�� ���� �����϶�
	{
		if (!(Action & ACTION_SLASH_ATTACK) && !(Action & ACTION_THROW_ATTACK))	//���� �ൿ�� ���� �ൿ�� �ƴ϶��
		{
			SOUNDMANAGER->playSound("playerSlash", PointMake(x,y));
			_attackManager->playerSlashAttack(x, y, direction);
			attackType = (attackType == true) ? false : true;
			frameCount = 0;
			Action = Action | ACTION_SLASH_ATTACK;				//���� �ൿ�� �����ൿ����
			playerStatus = playerStatus | STATUS_ATTACK;	//���� ���¸� ���ݻ��·�
		}
	}

	if (keyStatus & KEYBOARD_Z && keyStatus & KEYBOARD_UP)		//���Ÿ� ���� Ű�� ���� �����϶�
	{
		if (!(Action & ACTION_SLASH_ATTACK) && !(Action & ACTION_THROW_ATTACK))	//���� �ൿ�� ���� �ൿ�� �ƴ϶��
		{
			SOUNDMANAGER->playSound("playerThrow", PointMake(x, y));
			_attackManager->playerThrowAttack(x, y - playerIMG->getFrameHeight() / 3, direction);
			frameCount = 0;
			Action = Action | ACTION_THROW_ATTACK;
			playerStatus = playerStatus | STATUS_ATTACK;
		}
	}
}

void player::testPlayerMove()
{
	if (keyStatus & KEYBOARD_LEFT) x -= SPEED;
	if (keyStatus & KEYBOARD_RIGHT) x += SPEED;
	if (keyStatus & KEYBOARD_UP) y -= SPEED;
	if (keyStatus & KEYBOARD_DOWN) y += SPEED;
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
	char str11[128];
	char str12[128];
	char str13[128];
	char str14[128];
	char str15[128];
	char str16[128];
	char str17[128];
	char str18[128];
	char str19[128];
	char str20[128];

	if (keyStatus & KEYBOARD_LEFT)	sprintf(str1, "��"); else sprintf(str1, " ");
	if (keyStatus & KEYBOARD_RIGHT) sprintf(str2, "��"); else sprintf(str2, " ");
	if (keyStatus & KEYBOARD_UP)	sprintf(str3, "��"); else sprintf(str3, " ");
	if (keyStatus & KEYBOARD_DOWN)	sprintf(str4, "��"); else sprintf(str4, " ");
	if (keyStatus & KEYBOARD_Z)		sprintf(str5, "Z"); else sprintf(str5, " ");
	if (keyStatus & KEYBOARD_X)		sprintf(str6, "X"); else sprintf(str6, " ");
	if (keyStatus & KEYBOARD_C)		sprintf(str7, "C"); else sprintf(str7, " ");
	sprintf(str8, "%d", currentCollisionTile);
	sprintf(str9, "%0.3f", gravity);
	if (playerStatus & STATUS_STAND)				sprintf(str10, "STATUS_STAND");
	else if(!(playerStatus & STATUS_STAND))			sprintf(str10, " ");
	if (playerStatus & STATUS_RUN)					sprintf(str11, "STATUS_RUN");
	else if(!(playerStatus & STATUS_RUN))			sprintf(str11, " ");
	if (playerStatus & STATUS_JUMP)					sprintf(str12, "STATUS_JUMP");
	else if(!(playerStatus & STATUS_JUMP))			sprintf(str12, " ");
	if (playerStatus & STATUS_LAND)					sprintf(str13, "STATUS_LAND");
	else if(!(playerStatus & STATUS_LAND))			sprintf(str13, " ");
	if (playerStatus & STATUS_ATTACK)				sprintf(str14, "STATUS_ATTACK");
	else if(!(playerStatus & STATUS_ATTACK))		sprintf(str14, " ");
	if (Action & ACTION_NONE)						sprintf(str15, "ACTION_NONE");
	else if(!(Action & ACTION_NONE))				sprintf(str15, " ");
	if (Action & ACTION_JUMP)						sprintf(str16, "ACTION_JUMP"); 
	else if(!(Action & ACTION_JUMP))				sprintf(str16, " ");
	if (Action & ACTION_SLASH_ATTACK)				sprintf(str17, "ACTION_SLASH");
	else if(!(Action & ACTION_SLASH_ATTACK))		sprintf(str17, " ");
	if (Action & ACTION_THROW_ATTACK)				sprintf(str18, "ACTION_THROW");
	else if (!(Action & ACTION_THROW_ATTACK))		sprintf(str18, " ");

	switch (_tileMap->getTiles()[currentCollisionTile].obj)
	{
	case OBJ_NONE: sprintf(str20, "OBJ_NONE"); break;
	case OBJ_GROUND:	sprintf(str20, "OBJ_GROUND"); break;
	case OBJ_PIXEL:		sprintf(str20, "OBJ_PIXEL"); break;
	}
	
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
	TextOut(getMemDC(), 100, 300, str10, strlen(str10));
	TextOut(getMemDC(), 100, 330, str11, strlen(str11));
	TextOut(getMemDC(), 100, 360, str12, strlen(str12));
	TextOut(getMemDC(), 100, 390, str13, strlen(str13));
	TextOut(getMemDC(), 100, 420, str14, strlen(str14));
	TextOut(getMemDC(), 100, 450, str15, strlen(str15));
	TextOut(getMemDC(), 100, 480, str16, strlen(str16));
	TextOut(getMemDC(), 100, 510, str17, strlen(str17));
	TextOut(getMemDC(), 100, 540, str18, strlen(str18));
	TextOut(getMemDC(), WINSIZEX / 2, WINSIZEY / 2, str20, strlen(str20));		//�������� ���� �÷��̾� ������ �Ÿ�
}

void player::playerStatusCheck()
{
	if (gravity > 1)
	{
		playerStatus = playerStatus | STATUS_LAND;						//���� ���·� ������
		if (playerStatus & STATUS_JUMP) playerStatus -= STATUS_JUMP;	//���� ���¸� �����Ѵ�.
		if (playerStatus & STATUS_RUN) playerStatus -= STATUS_RUN;		//�޸� ���¸� �����Ѵ�.
		if (playerStatus & STATUS_STAND) playerStatus -= STATUS_STAND;	//���ִ� ���¸� �����Ѵ�.
	}
	if (gravity < -1)
	{
		playerStatus = playerStatus | STATUS_JUMP;						//���� ���·� ������.
		if (playerStatus & STATUS_LAND) playerStatus -= STATUS_LAND;	//���� ���¸� �����Ѵ�.
		if (playerStatus & STATUS_RUN) playerStatus -= STATUS_RUN;		//�޸� ���¸� �����Ѵ�.
		if (playerStatus & STATUS_STAND) playerStatus -= STATUS_STAND;	//���ִ� ���¸� �����Ѵ�.
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

	if (keyStatus & KEYBOARD_Z) playerAttack();

}

void player::sendDataToSingleton()
{
	DATABASE->setSourCamX(x);							//������ �� ��ǥ�� �÷��̾� X��ǥ�� �����Ѵ�.
	DATABASE->setSourCamY(y);							//������ �� ��ǥ�� �÷��̾� y��ǥ�� �����Ѵ�.
	DATABASE->setHP(HP);
	DATABASE->setMP(MP);
	DATABASE->setCollisionTile(currentCollisionTile);	//������ �� Ÿ���� �÷��̾� �浹 Ÿ�Ϲ�ȣ�� �����Ѵ�.
	DATABASE->setPlayerX(x);
	DATABASE->setPlayerY(y);
	DATABASE->setMaxHP(MAXHP);
}

void player::setPlayerTilePosition(int tileNum)
{
	x = (_tileMap->getTiles()[tileNum].rc.left + _tileMap->getTiles()[tileNum].rc.right) / 2;
	y = (_tileMap->getTiles()[tileNum].rc.top + _tileMap->getTiles()[tileNum].rc.bottom) / 2;
}

void player::setPlayerHit(float value)
{
	if (invincibleTime + value < TIMEMANAGER->getWorldTime())
	{
		invincibleTime = TIMEMANAGER->getWorldTime();
		countTime = value;
		HP--;
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
	//�浹������ �� ���� ����� ���� ������ ����.
	for (int i = currentCollisionTile - 1; i < currentCollisionTile + 2; ++i)
	{
		for (int j = -1; j < 2; ++j)
		{
			//ĳ���� �ֺ� 25���� Ÿ���� �浹�� ����Ѵ�. �̶� ������ ����� �ʵ��� ������ ������ ��� �Ѵ�.
			if (PtInRect(&_tileMap->getTiles()[i + j * TILEX].rc, PointMake(x, y)))
			{
				currentCollisionTile = i + j * TILEX;
				break;
			}
		}
	}
}

void player::playerRender()
{
	//�÷��̾��� ���¿� ���� alpha���� �����ϴ� �κ�
	if (invincibleTime + countTime > TIMEMANAGER->getWorldTime())
	{
		int a = TIMEMANAGER->getWorldTime() / 0.2f;
		switch (a % 2)
		{
		case 0:		alphaValue = 125;	break;
		case 1:		alphaValue = 255;	break;
		}
	}
	else
	{
		alphaValue = 255;
	}

	//�������� ������Ű�� �κ� (����������� 0.05�ʸ��� �����մϴ�)
	if (currentTime + 0.05f < TIMEMANAGER->getWorldTime())
	{
		currentTime = TIMEMANAGER->getWorldTime();
		++frameCount;
	}

	//�ִ� �������� �Ѿ�� �ʱ�ȭ �ϴ� �κ�
	if (playerStatus & STATUS_STAND && !(playerStatus & STATUS_ATTACK)) 	frameCount = 0;
	if (playerStatus & STATUS_RUN && !(playerStatus & STATUS_ATTACK))	if (frameCount > 5) frameCount = 0;	//�޸��鼭 ������ ���Ҷ�
	if (playerStatus & STATUS_JUMP && !(playerStatus & STATUS_ATTACK)) 	if (frameCount > 1) frameCount = 0;	//�ٸ鼭 ������ ���ҋ�
	if (playerStatus & STATUS_LAND && !(playerStatus & STATUS_ATTACK))	if (frameCount > 1) frameCount = 0;	//�����ϸ鼭 ������ ���ҋ�

	//�������� , ������ ����, �����̸鼭 ������ �� ó���� ��� �Ѵ�.
	if (playerStatus & STATUS_ATTACK)	
		if (frameCount > 2)
		{
			if (Action & ACTION_SLASH_ATTACK) Action -= ACTION_SLASH_ATTACK;
			if (Action & ACTION_THROW_ATTACK) Action -= ACTION_THROW_ATTACK;
			if (playerStatus & STATUS_ATTACK) playerStatus -= STATUS_ATTACK;
			frameCount = 0;
		}

	//����� ���¿� ���� �����ϴ� �κ�
	switch (direction)
	{
	case RIGHT:
		if(playerStatus & STATUS_STAND)
			playerIMG->alphaFrameRender(getMemDC(), x - playerIMG->getFrameWidth() / 2, y - playerIMG->getFrameHeight(), frameCount, 0, alphaValue);
		if(playerStatus & STATUS_RUN)
			playerIMG->alphaFrameRender(getMemDC(), x - playerIMG->getFrameWidth() / 2, y - playerIMG->getFrameHeight(), frameCount, 2, alphaValue);
		if(playerStatus & STATUS_JUMP)
			playerIMG->alphaFrameRender(getMemDC(), x - playerIMG->getFrameWidth() / 2, y - playerIMG->getFrameHeight(), frameCount, 4, alphaValue);
		if(playerStatus & STATUS_LAND)
			playerIMG->alphaFrameRender(getMemDC(), x - playerIMG->getFrameWidth() / 2, y - playerIMG->getFrameHeight(), frameCount, 6, alphaValue);
		if (playerStatus & STATUS_ATTACK)
		{
			if (Action & ACTION_SLASH_ATTACK)	//�⺻ ���� ���¶��
				switch (attackType)
				{
				case true:
					playerIMG->alphaFrameRender(getMemDC(), x - playerIMG->getFrameWidth() / 2, y - playerIMG->getFrameHeight(), frameCount, 8, alphaValue);
					break;
				case false:
					playerIMG->alphaFrameRender(getMemDC(), x - playerIMG->getFrameWidth() / 2, y - playerIMG->getFrameHeight(), frameCount, 9, alphaValue);
					break;
				}
			if (Action & ACTION_THROW_ATTACK)	//����ü ���� ���¶��
			{
				playerIMG->alphaFrameRender(getMemDC(), x - playerIMG->getFrameWidth() / 2, y - playerIMG->getFrameHeight(), frameCount, 16, alphaValue);
				break;
			}
		}
		break;
	case LEFT:
		if(playerStatus & STATUS_STAND)
			playerIMG->alphaFrameRender(getMemDC(), x - playerIMG->getFrameWidth() / 2, y - playerIMG->getFrameHeight(), frameCount, 1, alphaValue);
		if(playerStatus & STATUS_RUN)
			playerIMG->alphaFrameRender(getMemDC(), x - playerIMG->getFrameWidth() / 2, y - playerIMG->getFrameHeight(), frameCount, 3, alphaValue);
		if(playerStatus & STATUS_JUMP)
			playerIMG->alphaFrameRender(getMemDC(), x - playerIMG->getFrameWidth() / 2, y - playerIMG->getFrameHeight(), frameCount, 5, alphaValue);
		if(playerStatus & STATUS_LAND)
			playerIMG->alphaFrameRender(getMemDC(), x - playerIMG->getFrameWidth() / 2, y - playerIMG->getFrameHeight(), frameCount, 7, alphaValue);
		if (playerStatus & STATUS_ATTACK)
		{
			if (Action & ACTION_SLASH_ATTACK)		//�⺻ ���� ���¶��
				switch (attackType)
				{
				case true:
					playerIMG->alphaFrameRender(getMemDC(), x - playerIMG->getFrameWidth() / 2, y - playerIMG->getFrameHeight(), frameCount, 12, alphaValue);
					break;
				case false:
					playerIMG->alphaFrameRender(getMemDC(), x - playerIMG->getFrameWidth() / 2, y - playerIMG->getFrameHeight(), frameCount, 13, alphaValue);
					break;
				}
			if (Action & ACTION_THROW_ATTACK)		//����ü ���� ���¶��
			{
				playerIMG->alphaFrameRender(getMemDC(), x - playerIMG->getFrameWidth() / 2, y - playerIMG->getFrameHeight(), frameCount, 17, alphaValue);
				break;
			}
		}
		break;
	}

}

player::player()
{
}


player::~player()
{
}
