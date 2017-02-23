#include "stdafx.h"
#include "MenuScene.h"


HRESULT MenuScene::init()
{
	initData();
	IMAGEMANAGER->addImage("black", "IMAGE/UI/black.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 0));
	IMAGEMANAGER->addImage("redCircle", "IMAGE/UI/redCircle.bmp", 30, 30, true, RGB(255, 255, 255));
	IMAGEMANAGER->addImage("saveArea", "IMAGE/UI/SaveArea.bmp", 800, 150, true, RGB(255, 0, 0));
	IMAGEMANAGER->addImage("selectArea", "IMAGE/UI/SelectArea.bmp", 200, 51, true, RGB(255, 0, 0));
	IMAGEMANAGER->addImage("name", "IMAGE/UI/name.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 0));
	IMAGEMANAGER->addImage("title", "IMAGE/UI/title.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 0));
	IMAGEMANAGER->addImage("keyBoard", "IMAGE/UI/keyboard.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 0));
	IMAGEMANAGER->addFrameImage("heart", "IMAGE/UI/heart2.bmp", 84, 24, 3, 1, true, RGB(255, 255, 255));
	IMAGEMANAGER->addImage("Controls", "IMAGE/UI/Controls.bmp", 190, 41, true, RGB(255, 0, 0));
	IMAGEMANAGER->addImage("DeleteSaveFile", "IMAGE/UI/DeleteSaveFile.bmp", 190, 41, true, RGB(255, 0, 0));
	IMAGEMANAGER->addImage("selectDeleteArea", "IMAGE/UI/selectDeleteArea.bmp", 200, 51, true, RGB(255, 0, 0));

	SOUNDMANAGER->addSound("title", "SOUND/title.ogg", true, true);
	SOUNDMANAGER->addSound("stage1", "SOUND/stage1.ogg", true, true);
	SOUNDMANAGER->addSound("stage2", "SOUND/stage2.ogg", true, true);
	SOUNDMANAGER->addSound("stage3", "SOUND/stage3.ogg", true, true);
	SOUNDMANAGER->addSound("battle1", "SOUND/battle1.ogg", true, true);

	currentTime = TIMEMANAGER->getWorldTime();
	showName = true;
	showLogo = false;
	showMenu = false;
	showKey = false;
	SelectMenu = 0;
	alphaValue = 0;
	fadeOut = false;
	selectFile = -1;
	deleteFile = false;
	SOUNDMANAGER->stopAllSound();
	SOUNDMANAGER->play("title", 0.5f);
	return S_OK;
}

void MenuScene::release()
{
}

void MenuScene::update()
{
	keyboardInput();
	changeScene();
}

void MenuScene::render()
{
	IMAGEMANAGER->findImage("black")->render(getMemDC());
	if (showName) IMAGEMANAGER->findImage("name")->render(getMemDC(), 0, 0);

	if (showLogo) IMAGEMANAGER->findImage("title")->alphaRender(getMemDC(), 0, 0, alphaValue);

	if (showMenu)
	{
		if (SelectMenu != 0)IMAGEMANAGER->findImage("saveArea")->render(getMemDC(), 0, 0);
		if (SelectMenu != 1)IMAGEMANAGER->findImage("saveArea")->render(getMemDC(), 0, 150);
		if (SelectMenu != 2)IMAGEMANAGER->findImage("saveArea")->render(getMemDC(), 0, 300);
		if (SelectMenu != 3)
		{
			if(!(deleteFile))	IMAGEMANAGER->findImage("selectArea")->render(getMemDC(), 50, 500);
			if(deleteFile)		IMAGEMANAGER->findImage("selectDeleteArea")->render(getMemDC(), 50, 500);
		}
		if (SelectMenu != 3)IMAGEMANAGER->findImage("DeleteSaveFile")->render(getMemDC(), 55, 503);
		if (SelectMenu != 4)IMAGEMANAGER->findImage("selectArea")->render(getMemDC(), 300, 500);
		if (SelectMenu != 4)IMAGEMANAGER->findImage("Controls")->render(getMemDC(), 305, 503);
		if (SelectMenu != 5)IMAGEMANAGER->findImage("selectArea")->render(getMemDC(), 550, 500);

		switch (SelectMenu)
		{
		case 0:	IMAGEMANAGER->findImage("saveArea")->alphaRender(getMemDC(), 0, 0, 120);		break;
		case 1: IMAGEMANAGER->findImage("saveArea")->alphaRender(getMemDC(), 0, 150, 120);		break;
		case 2: IMAGEMANAGER->findImage("saveArea")->alphaRender(getMemDC(), 0, 300, 120);		break;
		case 3: 
			if(!(deleteFile))	IMAGEMANAGER->findImage("selectArea")->alphaRender(getMemDC(), 50, 500, 120);	
			if(deleteFile)		IMAGEMANAGER->findImage("selectDeleteArea")->render(getMemDC(), 50, 500);
			IMAGEMANAGER->findImage("DeleteSaveFile")->alphaRender(getMemDC(), 55, 503, 120);
			break;
		case 4:	
			IMAGEMANAGER->findImage("selectArea")->alphaRender(getMemDC(), 300, 500, 120);	
			IMAGEMANAGER->findImage("Controls")->alphaRender(getMemDC(), 305, 503, 120);
			break;
		case 5: IMAGEMANAGER->findImage("selectArea")->alphaRender(getMemDC(), 550, 500, 120);	break;
		}

		switch (selectFile)
		{
		case 0:	IMAGEMANAGER->findImage("redCircle")->render(getMemDC(), WINSIZEX - 100, 65); break;
		case 1:	IMAGEMANAGER->findImage("redCircle")->render(getMemDC(), WINSIZEX - 100, 210); break;
		case 2:	IMAGEMANAGER->findImage("redCircle")->render(getMemDC(), WINSIZEX - 100, 360); break;
		}

		//폰트@!!!!!
		char str[128];
		char slot1[128];
		char slot2[128];
		char slot3[128];
		HFONT oldFont;
		HFONT font1;

		font1 = CreateFont(
			30,					//문자높이
			15,					//문자폭
			00,					//문자 기울기
			00,					//문자 방향
			FW_NORMAL,			//문자 굵기
			false,				//문자 기울일건가?
			false,				//문자 밑줄칠건가?
			false,				//문자 취소선할건가?
			HANGEUL_CHARSET,		//문자 셋팅
			0,					//출력정확도
			0,					//클리핑 정확도
			0,					//출력의 질
			10,					//자간
			TEXT("Consolas"));	//폰트

		SetBkMode(getMemDC(),TRANSPARENT);
		SetTextColor(getMemDC(), RGB(216, 213, 199));
		oldFont = (HFONT)SelectObject(getMemDC(), font1);
		sprintf(str, "New Game");
		sprintf(slot1, "slot1");
		sprintf(slot2, "slot2");
		sprintf(slot3, "slot3");

		if (!(MAXHP[0] == -1 || HP[0] == -1 || MP[0] == -1))	//첫번째 값이 비어있는 값이 아니라면
		{
			for (int i = 0; i < (HP[0] - 1) / 3 + 1; ++i)
			{
				TextOut(getMemDC(), 50, 65, slot1, strlen(slot1));
				if (i != (HP[0] - 1) / 3) IMAGEMANAGER->findImage("heart")->frameRender(getMemDC(), 170+ IMAGEMANAGER->findImage("heart")->getFrameWidth() / 2 * i, 40, 0, 0);
				else IMAGEMANAGER->findImage("heart")->frameRender(getMemDC(), 170 + IMAGEMANAGER->findImage("heart")->getFrameWidth() * i, 40, HP[0] % 3, 0);
			}
		}
		else if (MAXHP[0] == -1 || HP[0] == -1 || MP[0] == -1)		//첫번째 값이 비어있는 값이라면
		{
			TextOut(getMemDC(), 50, 65, str, strlen(str));
		}

		if (!(MAXHP[1] == -1 || HP[1] == -1 || MP[1] == -1))	//두번째 값이 비어있는 값이 아니라면
		{
			TextOut(getMemDC(), 50, 210, slot2, strlen(slot2));
			for (int i = 0; i < (HP[1] - 1) / 3 + 1; ++i)
			{
				if (i != (HP[1] - 1) / 3) IMAGEMANAGER->findImage("heart")->frameRender(getMemDC(), 170 + IMAGEMANAGER->findImage("heart")->getFrameWidth() / 2 * i, 180, 0, 0);
				else IMAGEMANAGER->findImage("heart")->frameRender(getMemDC(), 170 + IMAGEMANAGER->findImage("heart")->getFrameWidth() * i, 180, HP[1] % 3, 0);
			}
		}
		else if (MAXHP[1] == -1 || HP[1] == -1 || MP[1] == -1)		//두번째 값이 비어있는 값이라면
		{
			TextOut(getMemDC(), 50, 210, str, strlen(str));
		}

		if (!(MAXHP[2] == -1 || HP[2] == -1 || MP[2] == -1))	//세번째 값이 비어있는 값이 아니라면
		{
			TextOut(getMemDC(), 50, 360, slot3, strlen(slot3));
			for (int i = 0; i < (HP[2] - 1) / 3 + 1; ++i)
			{
				if (i != (HP[2] - 1) / 3) IMAGEMANAGER->findImage("heart")->frameRender(getMemDC(), 170 + IMAGEMANAGER->findImage("heart")->getFrameWidth() / 2 * i, 330, 0, 0);
				else IMAGEMANAGER->findImage("heart")->frameRender(getMemDC(), 170 + IMAGEMANAGER->findImage("heart")->getFrameWidth() * i, 330, HP[2] % 3, 0);
			}
		}
		else if (MAXHP[2] == -1 || HP[2] == -1 || MP[2] == -1)		//세번째 값이 비어있는 값이라면
		{
			TextOut(getMemDC(), 50, 360, str, strlen(str));
		}

		SelectObject(getMemDC(), oldFont);
		DeleteObject(font1);
	}
	
	if (showKey) IMAGEMANAGER->findImage("keyBoard")->render(getMemDC());
}

void MenuScene::keyboardInput()
{
	if (showMenu && KEYMANAGER->isOnceKeyDown(VK_DOWN) && SelectMenu < 3)	SelectMenu++;
	if (showMenu && KEYMANAGER->isOnceKeyDown(VK_UP) && SelectMenu > 0) SelectMenu--;
	if (showMenu && KEYMANAGER->isOnceKeyDown(VK_RIGHT) && SelectMenu < 5)	SelectMenu++;
	if (showMenu && KEYMANAGER->isOnceKeyDown(VK_LEFT) && SelectMenu > 3) SelectMenu--;

	//플레이어의 점프 또는 공격버튼을 누르면 현재 선택 메뉴의 번호에 따라 특정한 행동을 하게 지시합니다.
	if (showMenu && (KEYMANAGER->isOnceKeyDown('Z') || KEYMANAGER->isOnceKeyDown('X')))
	{
		switch (SelectMenu)
		{
		case 0:
			if (selectFile == 0)
			{
				_saveCount = 0;
				DATABASE->loadDataFromFile();
				switch (_sceneNumber)
				{
				case 1: SCENEMANAGER->changeScene("townScene");	return;
				case 2:	SCENEMANAGER->changeScene("field1Scene");	return;
				}
			}
			selectFile = 0; 
			break;		//1번째 세이브 파일
		case 1:
			if (selectFile == 1)
			{
				_saveCount = 1;
				DATABASE->loadDataFromFile();
				switch (_sceneNumber)
				{
				case 1:	SCENEMANAGER->changeScene("townScene");	return;
				case 2:	SCENEMANAGER->changeScene("field1Scene");	return;
				}
			}
			selectFile = 1; 
			break;		//2번째 세이브 파일
		case 2:
			if (selectFile == 2)
			{
				_saveCount = 2;
				DATABASE->loadDataFromFile();
				switch (_sceneNumber)
				{
				case 1:	SCENEMANAGER->changeScene("townScene");	return;
				case 2:	SCENEMANAGER->changeScene("field1Scene");	return;
				}
			}
			selectFile = 2; 
			break;		//3번째 세이브 파일
		case 3:
			switch (deleteFile)
			{
			case true: deleteFile = false;	break;
			case false: deleteFile = true;	break;
			}
			break;		//딜리트 세이브 파일
			//사용하는 키 안내
		case 4:
			showMenu = false;
			showKey = true;
			break;
		case 5:
		{
			switch (selectFile)
			{
			case 0:	_saveCount = 0;	break;
			case 1:	_saveCount = 1;	break;
			case 2:	_saveCount = 2;	break;
			}
			DATABASE->loadDataFromFile();
			_sceneNumber = 2;
			switch (_sceneNumber)
			{
			case 1:	SCENEMANAGER->changeScene("townScene");	return;
			case 2:	SCENEMANAGER->changeScene("field1Scene");	return;
			}
		}break;		//게임 시작
		}
	}

	if (showKey && (KEYMANAGER->isOnceKeyDown('Z') || KEYMANAGER->isOnceKeyDown('X')))
	{
		showKey = false;
		showMenu = true;
	}

	if (deleteFile)
	{
		switch (selectFile)
		{
		case 0:
			_saveCount = 0;
			DATABASE->setCollisionTile(-1);
			DATABASE->setPlayerX(-1);
			DATABASE->setPlayerY(-1);
			DATABASE->setMaxHP(-1);
			_sceneNumber = 1;
			DATABASE->saveDataToFile();
			deleteFile = false;
			selectFile = -1;
			initData();
			break;
		case 1:
			_saveCount = 1;
			DATABASE->setCollisionTile(-1);
			DATABASE->setPlayerX(-1);
			DATABASE->setPlayerY(-1);
			DATABASE->setMaxHP(-1);
			_sceneNumber = 1;
			DATABASE->saveDataToFile();
			deleteFile = false;
			selectFile = -1;
			initData();
			break;
		case 2:
			_saveCount = 2;
			DATABASE->setCollisionTile(-1);
			DATABASE->setPlayerX(-1);
			DATABASE->setPlayerY(-1);
			DATABASE->setMaxHP(-1);
			_sceneNumber = 1;
			DATABASE->saveDataToFile();
			deleteFile = false;
			selectFile = -1;
			initData();
			break;
		}
	}
}

void MenuScene::changeScene()
{
	if (showName && currentTime + 1.5f < TIMEMANAGER->getWorldTime())
	{
		currentTime = TIMEMANAGER->getWorldTime();
		showName = false;
		showLogo = true;
	}

	if (showLogo)
	{
		if (alphaValue < 254 && !(fadeOut)) alphaValue += 4;
		if (!(fadeOut) && alphaValue >= 250) fadeOut = true;
		if (alphaValue > 1 && fadeOut) alphaValue -= 4;
		if (fadeOut && alphaValue <= 10)
		{
			fadeOut = false;
			alphaValue = 255;
			showLogo = false;
			showMenu = true;
		}
	}
}

void MenuScene::initData()
{
	//오류인지 확인하기 위해 -1값을 삽입했습니다.
	for (int i = 0; i < 3; ++i)
	{
		MAXHP[i] = -1;
		HP[i] = -1;
		MP[i] = -1;
	}

	for (int i = 0; i < 3; ++i)
	{
		vector<string> arrString;
		arrString = DATABASE->loadDataFromFile(i);
		for (int j = 0; j < arrString.size(); ++j)
		{
			switch (j)
			{
			case 0: continue; break;
			case 1: continue; break;
			case 2:	MAXHP[i] = (int)atoi(arrString[j].c_str()); break;
			case 3:	HP[i] = (int)atoi(arrString[j].c_str()); break;
			case 4:	MP[i] = (int)atoi(arrString[j].c_str()); break;
			}
		}
	}
}

MenuScene::MenuScene()
{
}


MenuScene::~MenuScene()
{
}
