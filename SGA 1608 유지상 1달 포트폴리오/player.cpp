#include "stdafx.h"
#include "player.h"


HRESULT player::init()
{
	playerIMG = IMAGEMANAGER->addFrameImage("player", "IMAGE/player/player.bmp", 672, 1024, 7, 16, true, RGB(0, 0, 255));
	x = WINSIZEX / 2;
	y = WINSIZEY / 2;
	gravity = 0;
	PlayerRect = RectMakeCenter(x, y, 50, 50);
	SPEED = DEFAULT_SPEED;
	ATK = 1;
	currentTime = TIMEMANAGER->getWorldTime();

	keyStatus = 0;
	playerStatus = 0;

	HP = 5;
	MP = 4;
	direction = RIGHT;
	Action = ACTION_NONE;
	frameCount = 0;
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

	//

	PlayerRect = RectMakeCenter(x, y, 5, 5);

	DATABASE->setSourCamX(x);							//기준이 될 좌표를 플레이어 X좌표로 설정한다.
	DATABASE->setSourCamY(y);							//기준이 될 좌표를 플레이어 y좌표로 설정한다.
	DATABASE->setHP(HP);
	DATABASE->setMP(MP);
	DATABASE->setCollisionTile(currentCollisionTile);	//기준이 될 타일을 플레이어 충돌 타일번호로 설정한다.

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

	//플레이어와 타일의 충돌을 처리
	if (_tileMap->getTiles()[currentCollisionTile].obj == OBJ_GROUND)
	{
		if (gravity > 0) y = _tileMap->getTiles()[currentCollisionTile].rc.top - 1;		//중력이 밑으로 향할때
		if (gravity < 0) y = _tileMap->getTiles()[currentCollisionTile].rc.bottom + 1;	//중력이 위로 향할때
		if (Action & ACTION_JUMP) Action -= ACTION_JUMP;								//현재 점프중 상태이면 점프상태 제거								
		gravity = 0;
	}

	//중력 예외처리 (땅위에 서있을때)
	if (gravity <= 1)
	{
		if (_tileMap->getTiles()[currentCollisionTile + TILEX].obj == OBJ_GROUND &&
			PtInRect(&_tileMap->getTiles()[currentCollisionTile + TILEX].rc, PointMake(x, y + gravity))) gravity = 0;
	}

	//키보드 입력을 처리
	//타일과 부딪힌다면 움직이지 못하도록 처리.
	if (keyStatus & KEYBOARD_LEFT)
	{
		if (PtInRect(&_tileMap->getTiles()[currentCollisionTile-1].rc, PointMake(x - SPEED, y)))	//이동하고 나서 좌표가 왼쪽 타일에 닿았을때						
		{
			if(_tileMap->getTiles()[currentCollisionTile - 1].obj != OBJ_GROUND) x -= SPEED;		//타일의 종류가 땅이 아니라면																		//이동한다
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
	if (keyStatus & KEYBOARD_UP) y -= SPEED;
	if (keyStatus & KEYBOARD_DOWN) y += SPEED;
	if (keyStatus & KEYBOARD_X)
	{
		if (!(Action & ACTION_JUMP))
		{
			Action = ACTION_JUMP;
			gravity = -10;								//중력을 바꿔준다.
		}
	}

	//타일의 속성을 얻어오자.
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

	if (keyStatus & KEYBOARD_LEFT)	sprintf(str1, "←"); else sprintf(str1, " ");
	if (keyStatus & KEYBOARD_RIGHT) sprintf(str2, "→"); else sprintf(str2, " ");
	if (keyStatus & KEYBOARD_UP)	sprintf(str3, "↑"); else sprintf(str3, " ");
	if (keyStatus & KEYBOARD_DOWN)	sprintf(str4, "↓"); else sprintf(str4, " ");
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
		playerStatus = playerStatus | STATUS_JUMP;						//점프 상태로 변경함
		if (playerStatus & STATUS_LAND) playerStatus -= STATUS_LAND;	//착륙 상태를 제거한다.
		if (playerStatus & STATUS_RUN) playerStatus -= STATUS_RUN;		//달림 상태를 제거한다.
		if (playerStatus & STATUS_STAND) playerStatus -= STATUS_STAND;	//서있는 상태를 제거한다.
	}
	if (gravity < 0)
	{
		playerStatus = playerStatus | STATUS_LAND;						//착륙 상태로 변경함.
		if (playerStatus & STATUS_JUMP) playerStatus -= STATUS_JUMP;	//점프 상태를 제거한다.
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

	if (keyStatus & KEYBOARD_Z)
	{
		if(!(playerStatus & STATUS_ATTACK)) playerStatus = playerStatus | STATUS_ATTACK;
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
	for (int i = currentCollisionTile - 2; i < currentCollisionTile + 2; ++i)
	{
		for (int j = -2; j < 3; ++j)
		{
			//캐릭터 주변 25개의 타일의 충돌을 계산한다. 이때 범위를 벗어나지 않도록 영역을 조절해 줘야 한다.
			if (PtInRect(&_tileMap->getTiles()[i + j * TILEX].rc, PointMake(x, y)))
			{
				currentCollisionTile = i + j * TILEX;
				break;
			}
		}
		//if (PtInRect(&_tileMap->getTiles()[i].rc, PointMake(x, y)))
		//{
		//	currentCollisionTile = i;
		//	break;
		//}
	}
}

void player::playerRender()
{
	//프레임을 증가시키는 부분
	if (currentTime + 0.1f < TIMEMANAGER->getWorldTime())
	{
		currentTime = TIMEMANAGER->getWorldTime();
		++frameCount;
	}

	//최대 프레임이 넘어가면 초기화 하는 부분
	if (playerStatus & STATUS_STAND)	frameCount = 0;
	if (playerStatus & STATUS_RUN)		if (frameCount > 5) frameCount = 0;
	if (playerStatus & STATUS_JUMP) 	if (frameCount > 1) frameCount = 0;
	if (playerStatus & STATUS_LAND)		if (frameCount > 1) frameCount = 0;

	//방향과 상태에 따라서 렌더하는 부분
	switch (direction)
	{
	case RIGHT:
		if(playerStatus & STATUS_STAND)
			playerIMG->frameRender(getMemDC(), x - playerIMG->getFrameWidth() / 2, y - playerIMG->getFrameHeight(), frameCount, 0);
		if(playerStatus & STATUS_RUN)
			playerIMG->frameRender(getMemDC(), x - playerIMG->getFrameWidth() / 2, y - playerIMG->getFrameHeight(), frameCount, 2);
		if(playerStatus & STATUS_JUMP)
			playerIMG->frameRender(getMemDC(), x - playerIMG->getFrameWidth() / 2, y - playerIMG->getFrameHeight(), frameCount, 6);
		if(playerStatus & STATUS_LAND)
			playerIMG->frameRender(getMemDC(), x - playerIMG->getFrameWidth() / 2, y - playerIMG->getFrameHeight(), frameCount, 4);
		break;
	case LEFT:
		if(playerStatus & STATUS_STAND)
			playerIMG->frameRender(getMemDC(), x - playerIMG->getFrameWidth() / 2, y - playerIMG->getFrameHeight(), frameCount, 1);
		if(playerStatus & STATUS_RUN)
			playerIMG->frameRender(getMemDC(), x - playerIMG->getFrameWidth() / 2, y - playerIMG->getFrameHeight(), frameCount, 3);
		if(playerStatus & STATUS_JUMP)
			playerIMG->frameRender(getMemDC(), x - playerIMG->getFrameWidth() / 2, y - playerIMG->getFrameHeight(), frameCount, 7);
		if(playerStatus & STATUS_LAND)
			playerIMG->frameRender(getMemDC(), x - playerIMG->getFrameWidth() / 2, y - playerIMG->getFrameHeight(), frameCount, 5);
		break;
	}

}

player::player()
{
}


player::~player()
{
}
