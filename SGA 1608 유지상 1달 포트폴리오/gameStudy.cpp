#include "stdafx.h"
#include "gameStudy.h"
#include "mapTool.h"
#include "ingameScene.h"
#include "MenuScene.h"

gameStudy::gameStudy()
{
}


gameStudy::~gameStudy()
{
}

//초기화
HRESULT gameStudy::init()
{
	gameNode::init();

	//------------------------------------------
	_whiteBackground = IMAGEMANAGER->addImage("whiteSpace", "IMAGE/background/WhiteSpace.bmp", 1600, 900, false, RGB(0, 0, 0));
	SCENEMANAGER->addScene("menuScene", new MenuScene);		//게임시작전 메뉴를 선택하는 화면
	SCENEMANAGER->addScene("testScene", new testScene);		//각종 실험을 위한 CPP
	SCENEMANAGER->addScene("mapTool", new mapTool);			//맵을 만드는 도구
	SCENEMANAGER->addScene("townScene", new townScene);		//마을
	SCENEMANAGER->addScene("field1Scene", new field1Scene);	//사냥터 1
	SCENEMANAGER->addScene("endingScene", new endingScene);	//엔딩을 보여주는 씬
	
	SCENEMANAGER->changeScene("menuScene");					//현재 실험용 맵으로 진입한다.
	//------------------------------------------
	return S_OK;
}

//메모리 해제
void gameStudy::release()
{
	gameNode::release();
	//------------------------------------------
	//-------------------------------------------
}

//데이터 갱신
void gameStudy::update()
{
	gameNode::update();

	//-------------------------------------------
	SCENEMANAGER->update();
	//--------------------------------------------
}

//화면 출력
void gameStudy::render()
{
	//--------------------------------------------
	_whiteBackground->render(getMemDC());
	//---------------------------------------------
	SCENEMANAGER->render();
	//모든 이미지가 렌더된 백 버퍼를 현재 DC에 출력합니다.
	this->getBackBuffer()->render(getHDC());
}

//함수 구현------------------------------------------
//--------------------------------------------------
