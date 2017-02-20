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

//�ʱ�ȭ
HRESULT gameStudy::init()
{
	gameNode::init();

	//------------------------------------------
	_saveCount		= -1;		//�÷��̾��� ���̺� ī��Ʈ
	_sceneNumber	= 0;		//����ȯ�� �����ϱ� ���� ī��Ʈ
	_whiteBackground = IMAGEMANAGER->addImage("whiteSpace", "IMAGE/background/WhiteSpace.bmp", 1600, 900, false, RGB(0, 0, 0));
	SCENEMANAGER->addScene("menuScene", new MenuScene);		//���ӽ����� �޴��� �����ϴ� ȭ��
	SCENEMANAGER->addScene("testScene", new testScene);		//���� ������ ���� CPP
	SCENEMANAGER->addScene("mapTool", new mapTool);			//���� ����� ����
	SCENEMANAGER->addScene("townScene", new townScene);		//����
	SCENEMANAGER->addScene("field1Scene", new field1Scene);	//����� 1
	SCENEMANAGER->addScene("endingScene", new endingScene);	//������ �����ִ� ��
	
	SCENEMANAGER->changeScene("menuScene");					//���� ����� ������ �����Ѵ�.
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
