#include "stdafx.h"
#include "player.h"


HRESULT player::init()
{
	playerIMG = IMAGEMANAGER->addFrameImage("player", "IMAGE/player/player.bmp", IMAGESIZEX * 2, IMAGESIZEY * 2, 7, 18, true, RGB(0, 0, 255));
	x = WINSIZEX / 2;
	y = WINSIZEY / 2;
	gravity = 0;
	PlayerRect = RectMakeCenter(x, y, 50, 50);
	SPEED = DEFAULT_SPEED;
	ATK = 1;
	currentTime = TIMEMANAGER->getWorldTime();
	invincibleTime = TIMEMANAGER->getWorldTime();
	countTime = 0;

	keyStatus = 0;
	playerStatus = 0;

	MAXHP = 5;
	HP = 5;
	MP = 4;
	direction = RIGHT;
	Action = ACTION_NONE;
	frameCount = 0;

	alphaValue = 255;
	SOUNDMANAGER->addSound("playerSlash", "SOUND/hit.wav", false, false);
	SOUNDMANAGER->addSound("playerThrow", "SOUND/seal.wav", false, false);
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
	//testPlayerMove();
	sendDataToSingleton();	//�÷��̾��� �����͸� �̱������� �����մϴ�.

	PlayerRect = RectMakeCenter(x, y, 5, 5);
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
}

void player::playerMove()
{
	//�߷�ó��
	gravity += GRAVITY;
	//Ű���� �Է��� ó��
	//Ÿ�ϰ� �ε����ٸ� �������� ���ϵ��� ó��.
	if (keyStatus & KEYBOARD_LEFT)
	{
		if (PtInRect(&_tileMap->getTiles()[currentCollisionTile - 1].rc, PointMake(x - SPEED, y)))	//�̵��ϰ� ���� ��ǥ�� ���� Ÿ�Ͽ� �������						
		{
			if (_tileMap->getTiles()[currentCollisionTile - 1].obj != OBJ_GROUND) x -= SPEED;		//Ÿ���� ������ ���� �ƴ϶��																		//�̵��Ѵ�
		}
		else																						//�̵��ص� ��Ÿ�Ͽ� �ȴ�´ٸ�
			x -= SPEED;																				//�̵��Ѵ�.
	}
	if (keyStatus & KEYBOARD_RIGHT)
	{
		if (PtInRect(&_tileMap->getTiles()[currentCollisionTile + 1].rc, PointMake(x + SPEED, y)))	//�̵��ϰ� ���� ��ǥ�� ���� Ÿ�Ͽ� �������						
		{
			if (_tileMap->getTiles()[currentCollisionTile + 1].obj != OBJ_GROUND) x += SPEED;		//Ÿ���� ������ ���� �ƴ϶��																		//�̵��Ѵ�
		}
		else																						//�̵��ص� ��Ÿ�Ͽ� �ȴ�´ٸ�
			x += SPEED;																				//�̵��Ѵ�.
	}
	if (keyStatus & KEYBOARD_X)
	{
		if (!(Action & ACTION_JUMP))
		{
			Action = Action | ACTION_JUMP;
			gravity = -15;								//�߷��� �ٲ��ش�.
		}
	}


	//�÷��̾�� Ÿ���� �浹�� ó��
	if (_tileMap->getTiles()[currentCollisionTile].obj == OBJ_GROUND)
	{
		if (gravity > 0) y = _tileMap->getTiles()[currentCollisionTile].rc.top - 1;		//�߷��� ������ ���Ҷ�

		if (gravity < 0)//�߷��� ���� ���Ҷ� ���� �浹�ϰ� �ȴٸ�
		{
			gravity = 1;
			y = _tileMap->getTiles()[currentCollisionTile].rc.bottom + 1;
		}
		//�÷��̾ ���� �浹�ϰ� �ְ� �� Ÿ�� ���� �ƹ��͵� ���� �����϶� (���� ���� ������ �ذ��ϱ� ���� ����ó��)
		if (Action & ACTION_JUMP && _tileMap->getTiles()[currentCollisionTile - TILEX].obj == OBJ_NONE) Action -= ACTION_JUMP;								//���� ������ �����̸� �������� ����								
		gravity = 0;
	}

	//�߷��� ����Ͽ� ó���Ѵ�.
	if (_tileMap->getTiles()[currentCollisionTile].obj == OBJ_NONE)
	{
		if (gravity < 0)	//�߷��� ȭ�� ������� ���Ҷ�
		{
			if (PtInRect(&_tileMap->getTiles()[currentCollisionTile - TILEX].rc, PointMake(x, y + gravity)))
			{
				if (_tileMap->getTiles()[currentCollisionTile - TILEX].obj == OBJ_GROUND)
				{
					gravity = 1;
					y = _tileMap->getTiles()[currentCollisionTile - TILEX].rc.bottom + 1;
				}
				else
				{
					y += gravity;
				}
			}
			else
			{
				y += gravity;
			}
		}

		if (gravity > 0)	//�߷��� ȭ�� �ϴ����� ���Ҷ�
		{
			if (PtInRect(&_tileMap->getTiles()[currentCollisionTile + TILEX].rc, PointMake(x, y + gravity)))
			{
				if (_tileMap->getTiles()[currentCollisionTile + TILEX].obj == OBJ_GROUND)
				{
					gravity = 0;
					y = _tileMap->getTiles()[currentCollisionTile + TILEX].rc.top - 1;
					if (Action & ACTION_JUMP) Action -= ACTION_JUMP;
				}
				else
				{
					y += gravity;
				}
			}
			else
			{
				y += gravity;
			}
		}
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
			_attackManager->playerThrowAttack(x, y, direction);
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

	sprintf(str20, "%0.3f", getDistance(WINSIZEX / 2, (WINSIZEY / 4) * 3, x, y));

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
	//TextOut(getMemDC(), 300, 100, str20, strlen(str20));		//�������� ���� �÷��̾� ������ �Ÿ�
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

	//�������� ������Ű�� �κ�
	if (playerStatus & STATUS_ATTACK && currentTime + 0.05f < TIMEMANAGER->getWorldTime())
	{
		currentTime = TIMEMANAGER->getWorldTime();
		++frameCount;
	}
	
	if(!(playerStatus & STATUS_ATTACK) && currentTime + 0.1f < TIMEMANAGER->getWorldTime())
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
