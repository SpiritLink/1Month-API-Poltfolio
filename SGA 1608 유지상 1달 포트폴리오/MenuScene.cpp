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
	currentTime = TIMEMANAGER->getWorldTime();
	showName = true;
	showLogo = false;
	showMenu = false;
	showKey = false;
	SelectMenu = 0;
	alphaValue = 0;
	fadeOut = false;
	selectFile = -1;
	
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
		if (SelectMenu != 3)IMAGEMANAGER->findImage("selectArea")->render(getMemDC(), 50, 500);
		if (SelectMenu != 4)IMAGEMANAGER->findImage("selectArea")->render(getMemDC(), 300, 500);
		if (SelectMenu != 5)IMAGEMANAGER->findImage("selectArea")->render(getMemDC(), 550, 500);

		switch (SelectMenu)
		{
		case 0:	IMAGEMANAGER->findImage("saveArea")->alphaRender(getMemDC(), 0, 0, 120);		break;
		case 1: IMAGEMANAGER->findImage("saveArea")->alphaRender(getMemDC(), 0, 150, 120);		break;
		case 2: IMAGEMANAGER->findImage("saveArea")->alphaRender(getMemDC(), 0, 300, 120);		break;
		case 3: IMAGEMANAGER->findImage("selectArea")->alphaRender(getMemDC(), 50, 500, 120);	break;
		case 4:	IMAGEMANAGER->findImage("selectArea")->alphaRender(getMemDC(), 300, 500, 120);	break;
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

		HFONT oldFont;
		HFONT font1;

		font1 = CreateFont(
			30,					//문자높이
			20,					//문자폭
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
			TEXT("굴림체"));	//폰트

		SetTextColor(getMemDC(), RGB(216, 213, 199));
		oldFont = (HFONT)SelectObject(getMemDC(), font1);
		sprintf(str, "New Game");

		if (!(MAXHP[0] == -1 || HP[0] == -1 || MP[0] == -1))	//첫번째 값이 비어있는 값이 아니라면
		{

		}
		else if (MAXHP[0] == -1 || HP[0] == -1 || MP[0] == -1)		//첫번째 값이 비어있는 값이라면
		{
			TextOut(getMemDC(), 100, 65, str, strlen(str));
		}

		if (!(MAXHP[1] == -1 || HP[1] == -1 || MP[1] == -1))	//두번째 값이 비어있는 값이 아니라면
		{

		}
		else if (MAXHP[1] == -1 || HP[1] == -1 || MP[1] == -1)		//두번째 값이 비어있는 값이라면
		{
			TextOut(getMemDC(), 100, 210, str, strlen(str));
		}

		if (!(MAXHP[2] == -1 || HP[2] == -1 || MP[2] == -1))	//세번째 값이 비어있는 값이 아니라면
		{

		}
		else if (MAXHP[2] == -1 || HP[2] == -1 || MP[2] == -1)		//세번째 값이 비어있는 값이라면
		{
			TextOut(getMemDC(), 100, 360, str, strlen(str));
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
		case 0:	selectFile = 0; break;		//1번째 세이브 파일
		case 1:	selectFile = 1; break;		//2번째 세이브 파일
		case 2:	selectFile = 2; break;		//3번째 세이브 파일
		case 3:	break;		//딜리트 세이브 파일
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
			case 2:	MAXHP[i] = (int)atoi(arrString[i].c_str()); break;
			case 3:	HP[i] = (int)atoi(arrString[i].c_str()); break;
			case 4:	MP[i] = (int)atoi(arrString[i].c_str()); break;
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
