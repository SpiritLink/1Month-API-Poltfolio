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

//�ʱ�ȭ
HRESULT gameStudy::init()
{
	gameNode::init();

	//------------------------------------------
	_whiteBackground = IMAGEMANAGER->addImage("whiteSpace", "IMAGE/background/WhiteSpace.bmp", 1600, 900, false, RGB(0, 0, 0));
	SCENEMANAGER->addScene("testScene", new testScene);		//���� ������ ���� CPP
	SCENEMANAGER->addScene("mapTool", new mapTool);			//���� ����� ����
	SCENEMANAGER->addScene("townScene", new townScene);		//����
	SCENEMANAGER->addScene("field1Scene", new field1Scene);	//����� 1
	SCENEMANAGER->addScene("field2Scene", new field2Scene);	//����� 2
	SCENEMANAGER->addScene("bossScene", new bossScene);		//������

	SCENEMANAGER->changeScene("bossScene");					//���� ����� ������ �����Ѵ�.
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


	_whiteBackground->render(getMemDC());
	//---------------------------------------------

	SCENEMANAGER->render();
	TIMEMANAGER->render(getMemDC());

	//��� �̹����� �ѷ����� ����۸� ȭ�� ���ۿ� ���������� ������ش�
	this->getBackBuffer()->render(getHDC());
}

//�Լ� ����------------------------------------------



//--------------------------------------------------
