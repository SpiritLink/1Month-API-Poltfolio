#include "stdafx.h"
#include "player.h"


HRESULT player::init()
{
	playerIMG = IMAGEMANAGER->addFrameImage("player", "IMAGE/player/player.bmp", IMAGESIZEX * 2, IMAGESIZEY * 2, 7, 18, true, RGB(0, 0, 255));
	//x = DATABASE->getPlayerX();	//싱글톤으로 부터
	//y = DATABASE->getPlayerY();	//싱글톤으로 부터
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
	collisionTileCheck();	//몇번 타일에 충돌중인지
	keyboardInput();		//어떤 키보드 입력을 받았는지
	playerStatusCheck();	//플레이어의 상태는 어떤지
	if(KEYMANAGER->isToggleKey('Y')) playerMove();			//플레이어의 상태와 키보드의 상태에 따라 움직임을 결정함
	if(!(KEYMANAGER->isToggleKey('Y'))) testPlayerMove();
	sendDataToSingleton();	//플레이어의 데이터를 싱글톤으로 전송합니다.

	PlayerRect = RectMake(x - PLAYERAREAX / 2, y - PLAYERAREAY + 10, PLAYERAREAX, PLAYERAREAY);
}

void player::render()
{
	playerRender();	//플레이어를 그리는 함수
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
	//중력을 항상 증가시킵니다. (단 중력은 타일 한개의 크기 보다는 적게)
	if(gravity < TILESIZE) gravity += GRAVITY;
	//키보드 좌 , 우 입력을 처리하는 부분입니다.
	if (keyStatus & KEYBOARD_LEFT)
	{
		//중력과 함께 움직였을때 대각선 타일로 이동하는지 검사합니다.
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
		//대각선타일로 이동하지 않는다면 옆타일로 이동하는지 확인합니다.
		else if (PtInRect(&_tileMap->getTiles()[currentCollisionTile - 1].rc, PointMake(x - SPEED, y)))	//이동하고 나서 좌표가 왼쪽 타일에 닿았을때						
		{
			switch (_tileMap->getTiles()[currentCollisionTile - 1].obj)
			{
			case OBJ_GROUND:
				break;
			case OBJ_PIXEL://이때 y좌표를 픽셀확인후 이동시켜줘야 한다.
				x -= SPEED;
				break;
			case OBJ_NONE:
				x -= SPEED;
				break;
			}
		}
		//다른 타일로 이동 없이 타일 한개 내에서 움직인다면
		else																						//이동해도 옆타일에 안닿는다면
			x -= SPEED;																				//이동한다.
	}
	if (keyStatus & KEYBOARD_RIGHT)
	{
		//중력과 함께 움직였을때 오른위 타일로 이동하는지 검사합니다.
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
		//대각선 타일로 이동하지 않는다면 옆타일로 이동하는지 확인합니다.
		else if (PtInRect(&_tileMap->getTiles()[currentCollisionTile + 1].rc, PointMake(x + SPEED, y)))	//이동하고 나서 좌표가 오른쪽 타일에 닿았을때						
		{
			switch (_tileMap->getTiles()[currentCollisionTile + 1].obj)
			{
			case OBJ_GROUND:
				break;
			case OBJ_PIXEL://이때 여기서 오른타일의 픽셀을 확인하고 y좌표를 변동시켜 줘야한다.
			{
				int playerTileX, playerTileY;
				playerTileX = x + SPEED - _tileMap->getTiles()[currentCollisionTile + 1].rc.left;
				playerTileY = y - _tileMap->getTiles()[currentCollisionTile].rc.top;

				//타일의 frameX, frameY를 이용해 이미지에서 찾을 부분의 기준을 정합니다.
				//이미지는 현재 1:1비율로 사용되고 있기 때문에 좌표도 변형없이 그대로 적용해줍니다.
				int imageX, imageY;
				imageX = _tileMap->getTileObjX(currentCollisionTile + 1) * TILESIZE;
				imageY = _tileMap->getTileObjY(currentCollisionTile) * TILESIZE;

				//픽셀충돌 연산에 사용할 좌표를 구합니다.
				int pixelX, pixelY;
				pixelX = playerTileX + imageX;
				pixelY = playerTileY + imageY;

				//색상의 정보를 저장할 임시 변수
				COLORREF color;

				//원하는 좌표의 색상 정보를 이미지에서 얻어옵니다
				color = GetPixel(IMAGEMANAGER->findImage("tilePIXEL")->getMemDC(), pixelX, pixelY);

				//좌표의 RGB값을 개별로 저장합니다
				int r = GetRValue(color);
				int g = GetGValue(color);
				int b = GetBValue(color);

				//이미지가 있는 부분이라면 y의 좌표를 변경합니다.
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
		//다른 타일로 이동 없이 타일 한개 내에서 움직인다면.
		else																						//이동해도 옆타일에 안닿는다면
			x += SPEED;																				//이동한다.
	}
	if (keyStatus & KEYBOARD_X)
	{
		if (!(Action & ACTION_JUMP))					//이미 점프를 한 상태가 아니라면
		{
			SOUNDMANAGER->playSound("jump", PointMake(x, y));
			Action = Action | ACTION_JUMP;				//상태에 점프를 넣어줍니다.
			gravity = -15;								//중력을 바꿔준다.
		}
	}

	//현재 충돌하고 있는 타일의 종류에 따라 움직임을 결정합니다.
	switch (_tileMap->getTiles()[currentCollisionTile].obj)
	{
	case OBJ_NONE:
		//중력이 화면 상단으로 향할때
		if (gravity < 0)
		{	//중력만큼 이동해서 바로 위타일과 충돌하는지 확인합니다.
			if (PtInRect(&_tileMap->getTiles()[currentCollisionTile - TILEX].rc, PointMake(x, y + gravity)))
			{	//만약 위타일에 충돌했을때 위타일이 땅이라면
				if (_tileMap->getTiles()[currentCollisionTile - TILEX].obj == OBJ_GROUND ||
					_tileMap->getTiles()[currentCollisionTile - TILEX].obj == OBJ_PIXEL)
				{	//위타일의 바텀 + 1 좌표로 플레이어 y좌표를 고정시킵니다.
					y = _tileMap->getTiles()[currentCollisionTile - TILEX].rc.bottom + 1;
					gravity = 0;
				}
				else
				{	//위타일이 땅이 아니라면 중력만큼 이동시킵니다.
					y += gravity;
				}
			}
			else
			{	//중력만큼 이동해도 한타일내에서 움직인다면 이동시킵니다.
				y += gravity;
			}
		}

		//중력이 화면 하단으로 향할때
		if (gravity > 0)
		{	//중력만큼 이동해서 바로 아래 타일과 충돌하는지 확인합니다.
			if (PtInRect(&_tileMap->getTiles()[currentCollisionTile + TILEX].rc, PointMake(x, y + gravity)))
			{	//만약 좌표가 아래타일로 넘어간다면
				switch (_tileMap->getTiles()[currentCollisionTile + TILEX].obj)
				{
				case OBJ_GROUND:
					gravity = 0;	//중력을 0으로 변경시킵니다.
					y = _tileMap->getTiles()[currentCollisionTile + TILEX].rc.top - 1;	//타일의 top - 1에 좌표를 고정합니다.
					if (Action & ACTION_JUMP) Action -= ACTION_JUMP;					//점프를 다시 할수있게 상태를 변경시킵니다.
					break;
				case OBJ_PIXEL:
					//한 타일 내에서 플레이어의 좌표를 구합니다.
					//중력이 적용되있다는 전제가 깔려있기 때문에 계산좌표에도 미리 중력을 적용시킵니다.
					int playerTileX, playerTileY;
					playerTileX = x - _tileMap->getTiles()[currentCollisionTile + TILEX].rc.left;
					playerTileY = y + gravity - _tileMap->getTiles()[currentCollisionTile + TILEX].rc.top;

					//타일의 frameX, frameY를 이용해 이미지에서 찾을 부분의 기준을 정합니다.
					//이미지는 현재 1:1비율로 사용되고 있기 때문에 좌표도 변형없이 그대로 적용해줍니다.
					int imageX, imageY;
					imageX = _tileMap->getTileObjX(currentCollisionTile + TILEX) * TILESIZE;
					imageY = _tileMap->getTileObjY(currentCollisionTile + TILEX) * TILESIZE;

					//픽셀충돌 연산에 사용할 좌표를 구합니다.
					int pixelX, pixelY;
					pixelX = playerTileX + imageX;
					pixelY = playerTileY + imageY;

					//색상의 정보를 받아올 임시변수를 생성합니다.
					COLORREF color;
					color = GetPixel(IMAGEMANAGER->findImage("tileMap")->getMemDC(), pixelX, pixelY);
					//이미지가 있는 부분이 아니라면 중력만큼 이동합니다.
					if (GetRValue(color) == 0 && GetGValue(color) == 0 && GetBValue(color) == 0) y += gravity;
					//이미지가 있는 부분이라면 y좌표를 변경합니다.
					else
					{
						//현재 점프가 불가능한 상태라면 가능한 상태로 변경합니다.
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
			{//중력만큼 이동해도 한 타일내에서 이동한다면 중력만큼 이동시킵니다.
				y += gravity;
			}
		}
		break;
	case OBJ_GROUND:												//GROUND 타일 처리
		y = _tileMap->getTiles()[currentCollisionTile].rc.top - 1;	//좌표	변경
		gravity = 0;												//중력	변경
		break;
	case OBJ_PIXEL:													//PIXEL 타일 처리
		//현재 위치한 타일 내에서 플레이어의 좌표를 구합니다.
		int playerTileX, playerTileY;
		playerTileX = x - _tileMap->getTiles()[currentCollisionTile].rc.left;
		playerTileY = y - _tileMap->getTiles()[currentCollisionTile].rc.top;

		//타일의 frameX, frameY를 이용해 이미지에서 찾을 부분의 기준을 정합니다.
		//이미지는 현재 1:1비율로 사용되고 있기 때문에 좌표도 변형없이 그대로 적용해줍니다.
		int imageX, imageY;
		imageX = _tileMap->getTileObjX(currentCollisionTile) * TILESIZE;
		imageY = _tileMap->getTileObjY(currentCollisionTile) * TILESIZE;

		//픽셀충돌 연산에 사용할 좌표를 구합니다.
		int pixelX, pixelY;
		pixelX = playerTileX + imageX;
		pixelY = playerTileY + imageY;

		//색상의 정보를 저장할 임시 변수
		COLORREF color;

		//원하는 좌표의 색상 정보를 이미지에서 얻어옵니다
		color = GetPixel(IMAGEMANAGER->findImage("tilePIXEL")->getMemDC(), pixelX, pixelY);

		//좌표의 RGB값을 개별로 저장합니다
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		//이미지가 없는 부분이라면 y는 중력값 만큼 이동해 줍니다.
		//여기서 중력이 1일때 떨리면서 내려가는 현상을 수정해줘야 할듯.
		if (r != 0 && g != 0 && b != 0)		y += gravity;
		//이미지가 있는 부분이라면 y의 좌표를 변경합니다.
		else
		{
			if (Action & ACTION_JUMP)	Action -= ACTION_JUMP;	//점프 상태를 해제
			if (gravity > 0)	gravity = 0;					//중력 변경

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
	TextOut(getMemDC(), WINSIZEX / 2, WINSIZEY / 2, str20, strlen(str20));		//중점으로 부터 플레이어 까지의 거리
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

	//프레임을 증가시키는 부분 (모든프레임은 0.05초마다 증가합니다)
	if (currentTime + 0.05f < TIMEMANAGER->getWorldTime())
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
