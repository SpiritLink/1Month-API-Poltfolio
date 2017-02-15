#pragma once

#include "gameNode.h"
class MenuScene : public gameNode
{
private:
	int SelectMenu;
	bool showName;		//��ó�� ȸ���̸��� ��Ÿ��
	bool showLogo;		//�״��� ���ӷΰ� ��Ÿ��
	bool showMenu;		//�״��� �޴�ȭ���� ��Ÿ��
	bool showKey;		//Ű���� ���ȳ� ȭ���� ��Ÿ��
	int alphaValue;		//�޴� ���ķ����� ���� ����
	bool fadeOut;		//ȭ���� ��ο����� ���� ��� ���� ����
	float currentTime;	//�ð��� �����ϴ� ������
public:

	void keyboardInput();
	void changeScene();
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	MenuScene();
	virtual ~MenuScene();
};

