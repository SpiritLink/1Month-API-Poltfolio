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
	collisionTileCheck();	//몇번 타일에 충돌중인지
	keyboardInput();		//어떤 키보드 입력을 받았는지
	playerStatusCheck();	//플레이어의 상태는 어떤지
	playerMove();			//플레이어의 상태와 키보드의 상태에 따라 움직임을 결정함
	//testPlayerMove();
	sendDataToSingleton();	//플레이어의 데이터를 싱글톤으로 전송합니다.

	PlayerRect = RectMakeCenter(x, y, 5, 5);
}

void player::render()
{
	playerRender();	//플레이어를 그리는 함수
	Rectangle(getMemDC(), PlayerRect.left, PlayerRect.top, PlayerRect.right, PlayerRect.bottom);	//충돌영역을 보여줌
	testFunction();	//값을 표시하기 위한 테스트용 함수.
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

	//실험목적, 현재 키를 누르면 방향이 바로 삽입된다.
	if (keyStatus & KEYBOARD_LEFT) direction = LEFT;
	if (keyStatus & KEYBOARD_RIGHT) direction = RIGHT;
}

void player::playerMove()
{
	//중력처리
	gravity += GRAVITY;
	//키보드 입력을 처리
	//타일과 부딪힌다면 움직이지 못하도록 처리.
	if (keyStatus & KEYBOARD_LEFT)
	{
		if (PtInRect(&_tileMap->getTiles()[currentCollisionTile - 1].rc, PointMake(x - SPEED, y)))	//이동하고 나서 좌표가 왼쪽 타일에 닿았을때						
		{
			if (_tileMap->getTiles()[currentCollisionTile - 1].obj != OBJ_GROUND) x -= SPEED;		//타일의 종류가 땅이 아니라면																		//이동한다
		}
		else																						//이동해도 옆타일에 안닿는다면
			x -= SPEED;																				//이동한다.
	}
	if (keyStatus & KEYBOARD_RIGHT)
	{
		if (PtInRect(&_tileMap->getTiles()[currentCollisionTile + 1].rc, PointMake(x + SPEED, y)))	//이동하고 나서 좌표가 왼쪽 타일에 닿았을때						
		{
			if (_tileMap->getTiles()[currentCollisionTile + 1].obj != OBJ_GROUND) x += SPEED;		//타일의 종류가 땅이 아니라면																		//이동한다
		}
		else																						//이동해도 옆타일에 안닿는다면
			x += SPEED;																				//이동한다.
	}
	if (keyStatus & KEYBOARD_X)
	{
		if (!(Action & ACTION_JUMP))
		{
			Action = Action | ACTION_JUMP;
			gravity = -15;								//중력을 바꿔준다.
		}
	}


	//플레이어와 타일의 충돌을 처리
	if (_tileMap->getTiles()[currentCollisionTile].obj == OBJ_GROUND)
	{
		if (gravity > 0) y = _tileMap->getTiles()[currentCollisionTile].rc.top - 1;		//중력이 밑으로 향할때

		if (gravity < 0)//중력이 위로 향할때 땅과 충돌하게 된다면
		{
			gravity = 1;
			y = _tileMap->getTiles()[currentCollisionTile].rc.bottom + 1;
		}
		//플레이어가 땅에 충돌하고 있고 그 타일 위가 아무것도 없는 상태일때 (무한 점프 현상을 해결하기 위한 예외처리)
		if (Action & ACTION_JUMP && _tileMap->getTiles()[currentCollisionTile - TILEX].obj == OBJ_NONE) Action -= ACTION_JUMP;								//현재 점프중 상태이면 점프상태 제거								
		gravity = 0;
	}

	//중력을 계산하여 처리한다.
	if (_tileMap->getTiles()[currentCollisionTile].obj == OBJ_NONE)
	{
		if (gravity < 0)	//중력이 화면 상단으로 향할때
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

		if (gravity > 0)	//중력이 화면 하단으로 향할때
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
	if (keyStatus & KEYBOARD_Z && !(keyStatus & KEYBOARD_UP))	//근접공격 키를 누른 상태일때
	{
		if (!(Action & ACTION_SLASH_ATTACK) && !(Action & ACTION_THROW_ATTACK))	//현재 행동이 공격 행동이 아니라면
		{
			SOUNDMANAGER->playSound("playerSlash", PointMake(x,y));
			_attackManager->playerSlashAttack(x, y, direction);
			attackType = (attackType == true) ? false : true;
			frameCount = 0;
			Action = Action | ACTION_SLASH_ATTACK;				//현재 행동을 공격행동으로
			playerStatus = playerStatus | STATUS_ATTACK;	//현재 상태를 공격상태로
		}
	}

	if (keyStatus & KEYBOARD_Z && keyStatus & KEYBOARD_UP)		//원거리 공격 키를 누른 상태일때
	{
		if (!(Action & ACTION_SLASH_ATTACK) && !(Action & ACTION_THROW_ATTACK))	//현재 행동이 공격 행동이 아니라면
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

	if (keyStatus & KEYBOARD_LEFT)	sprintf(str1, "←"); else sprintf(str1, " ");
	if (keyStatus & KEYBOARD_RIGHT) sprintf(str2, "→"); else sprintf(str2, " ");
	if (keyStatus & KEYBOARD_UP)	sprintf(str3, "↑"); else sprintf(str3, " ");
	if (keyStatus & KEYBOARD_DOWN)	sprintf(str4, "↓"); else sprintf(str4, " ");
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
	//TextOut(getMemDC(), 300, 100, str20, strlen(str20));		//중점으로 부터 플레이어 까지의 거리
}

void player::playerStatusCheck()
{
	if (gravity > 1)
	{
		playerStatus = playerStatus | STATUS_LAND;						//점프 상태로 변경함
		if (playerStatus & STATUS_JUMP) playerStatus -= STATUS_JUMP;	//착륙 상태를 제거한다.
		if (playerStatus & STATUS_RUN) playerStatus -= STATUS_RUN;		//달림 상태를 제거한다.
		if (playerStatus & STATUS_STAND) playerStatus -= STATUS_STAND;	//서있는 상태를 제거한다.
	}
	if (gravity < -1)
	{
		playerStatus = playerStatus | STATUS_JUMP;						//착륙 상태로 변경함.
		if (playerStatus & STATUS_LAND) playerStatus -= STATUS_LAND;	//점프 상태를 제거한다.
		if (playerStatus & STATUS_RUN) playerStatus -= STATUS_RUN;		//달림 상태를 제거한다.
		if (playerStatus & STATUS_STAND) playerStatus -= STATUS_STAND;	//서있는 상태를 제거한다.
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
	DATABASE->setSourCamX(x);							//기준이 될 좌표를 플레이어 X좌표로 설정한다.
	DATABASE->setSourCamY(y);							//기준이 될 좌표를 플레이어 y좌표로 설정한다.
	DATABASE->setHP(HP);
	DATABASE->setMP(MP);
	DATABASE->setCollisionTile(currentCollisionTile);	//기준이 될 타일을 플레이어 충돌 타일번호로 설정한다.
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
	//충돌연산을 더 줄일 방법에 대해 생각해 보자.
	for (int i = currentCollisionTile - 1; i < currentCollisionTile + 2; ++i)
	{
		for (int j = -1; j < 2; ++j)
		{
			//캐릭터 주변 25개의 타일의 충돌을 계산한다. 이때 범위를 벗어나지 않도록 영역을 조절해 줘야 한다.
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
	//플레이어의 상태에 따라 alpha값을 수정하는 부분
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

	//프레임을 증가시키는 부분
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

	//최대 프레임이 넘어가면 초기화 하는 부분
	if (playerStatus & STATUS_STAND && !(playerStatus & STATUS_ATTACK)) 	frameCount = 0;
	if (playerStatus & STATUS_RUN && !(playerStatus & STATUS_ATTACK))	if (frameCount > 5) frameCount = 0;	//달리면서 공격을 안할때
	if (playerStatus & STATUS_JUMP && !(playerStatus & STATUS_ATTACK)) 	if (frameCount > 1) frameCount = 0;	//뛰면서 공격을 안할떄
	if (playerStatus & STATUS_LAND && !(playerStatus & STATUS_ATTACK))	if (frameCount > 1) frameCount = 0;	//착륙하면서 공격을 안할떄

	//점프공격 , 땅에서 공격, 움직이면서 공격을 다 처리해 줘야 한다.
	if (playerStatus & STATUS_ATTACK)	
		if (frameCount > 2)
		{
			if (Action & ACTION_SLASH_ATTACK) Action -= ACTION_SLASH_ATTACK;
			if (Action & ACTION_THROW_ATTACK) Action -= ACTION_THROW_ATTACK;
			if (playerStatus & STATUS_ATTACK) playerStatus -= STATUS_ATTACK;
			frameCount = 0;
		}

	//방향과 상태에 따라서 렌더하는 부분
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
			if (Action & ACTION_SLASH_ATTACK)	//기본 공격 상태라면
				switch (attackType)
				{
				case true:
					playerIMG->alphaFrameRender(getMemDC(), x - playerIMG->getFrameWidth() / 2, y - playerIMG->getFrameHeight(), frameCount, 8, alphaValue);
					break;
				case false:
					playerIMG->alphaFrameRender(getMemDC(), x - playerIMG->getFrameWidth() / 2, y - playerIMG->getFrameHeight(), frameCount, 9, alphaValue);
					break;
				}
			if (Action & ACTION_THROW_ATTACK)	//투사체 공격 상태라면
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
			if (Action & ACTION_SLASH_ATTACK)		//기본 공격 상태라면
				switch (attackType)
				{
				case true:
					playerIMG->alphaFrameRender(getMemDC(), x - playerIMG->getFrameWidth() / 2, y - playerIMG->getFrameHeight(), frameCount, 12, alphaValue);
					break;
				case false:
					playerIMG->alphaFrameRender(getMemDC(), x - playerIMG->getFrameWidth() / 2, y - playerIMG->getFrameHeight(), frameCount, 13, alphaValue);
					break;
				}
			if (Action & ACTION_THROW_ATTACK)		//투사체 공격 상태라면
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
