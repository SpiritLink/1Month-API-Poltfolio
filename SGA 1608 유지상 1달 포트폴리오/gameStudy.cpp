#include "stdafx.h"
#include "gameStudy.h"
#include "testScene.h"
#include "mapTool.h"


gameStudy::gameStudy()
{
}


gameStudy::~gameStudy()
{
}

//�ʱ�ȭ
HRESULT gameStudy::init()
{
	gameNode::init();

	//------------------------------------------
	SCENEMANAGER->addScene("testScene", new testScene);
	SCENEMANAGER->addScene("mapTool", new mapTool);
	SCENEMANAGER->changeScene("mapTool");
	//------------------------------------------
	return S_OK;
}

//�޸� ����
void gameStudy::release()
{
	gameNode::release();

	//------------------------------------------

	//-------------------------------------------

}

//������ ����
void gameStudy::update()
{
	gameNode::update();

	//-------------------------------------------

	SCENEMANAGER->update();

	//--------------------------------------------


}

//ȭ�� ���
void gameStudy::render()
{

	//--------------------------------------------



	//---------------------------------------------

	SCENEMANAGER->render();
	TIMEMANAGER->render(getMemDC());

	//��� �̹����� �ѷ����� ����۸� ȭ�� ���ۿ� ���������� ������ش�
	this->getBackBuffer()->render(getHDC());
}

//�Լ� ����------------------------------------------



//--------------------------------------------------
