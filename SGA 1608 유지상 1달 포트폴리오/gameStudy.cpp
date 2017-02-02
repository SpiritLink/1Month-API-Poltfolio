#include "stdafx.h"
#include "gameStudy.h"
#include "testScene.h"
#include "mapTool.h"
#include "townScene.h"
#include "field1Scene.h"
#include "field2Scene.h"
#include "bossScene.h"

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
	SCENEMANAGER->addScene("testScene", new testScene);		//각종 실험을 위한 CPP
	SCENEMANAGER->addScene("mapTool", new mapTool);			//맵을 만드는 도구
	SCENEMANAGER->addScene("townScene", new townScene);		//마을
	SCENEMANAGER->addScene("field1Scene", new field1Scene);	//사냥터 1
	SCENEMANAGER->addScene("field2Scene", new field2Scene);	//사냥터 2
	SCENEMANAGER->addScene("bossScene", new bossScene);		//보스방

	SCENEMANAGER->changeScene("bossScene");					//현재 실험용 맵으로 진입한다.
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
	TIMEMANAGER->render(getMemDC());

	//모든 이미지를 뿌려놓은 백버퍼를 화면 버퍼에 마지막으로 출력해준다
	this->getBackBuffer()->render(getHDC());
}

//함수 구현------------------------------------------



//--------------------------------------------------
