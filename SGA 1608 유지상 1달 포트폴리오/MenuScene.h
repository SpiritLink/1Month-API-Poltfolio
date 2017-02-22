#pragma once

#include "gameNode.h"
class MenuScene : public gameNode
{
private:
	int SelectMenu;
	int selectFile;		//���� �� ���̺� ������ ǥ�����ݴϴ�.
	bool showName;		//��ó�� ȸ���̸��� ��Ÿ��
	bool showLogo;		//�״��� ���ӷΰ� ��Ÿ��
	bool showMenu;		//�״��� �޴�ȭ���� ��Ÿ��
	bool showKey;		//Ű���� ���ȳ� ȭ���� ��Ÿ��
	int alphaValue;		//�޴� ���ķ����� ���� ����
	bool fadeOut;		//ȭ���� ��ο����� ���� ��� ���� ����
	float currentTime;	//�ð��� �����ϴ� ������
	bool deleteFile;	//���̺� ���� ������ ���� ����

	int MAXHP[3];		//���̺� ��Ͽ� ǥ���ϱ� ���� ����
	int HP[3];			//���̺� ��Ͽ� ǥ���ϱ� ���� ����
	int MP[3];			//���̺� ��Ͽ� ǥ���ϱ� ���� ����
public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void keyboardInput();
	void changeScene();
	void initData();	//���Ͽ��� �����͸� �о� ���ε� ���������� �����մϴ�.
	MenuScene();
	virtual ~MenuScene();
};

