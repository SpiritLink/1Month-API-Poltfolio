#include "stdafx.h"
#include "timeManager.h"


timeManager::timeManager()
{
}


timeManager::~timeManager()
{
}

//�ʱ�ȭ
HRESULT timeManager::init()
{
	//Ÿ�̸� �����Ѵ�
	_timer = new timer;
	_timer->init();

	return S_OK;
}

//������
void timeManager::release()
{
	//Ÿ�̸� ����

	SAFE_DELETE(_timer);
	_timer = NULL;

}

//������ ����
void timeManager::update(float lock)
{
	if (_timer != NULL)
	{
		_timer->tick(lock);
	}
}

//�ش� HDC�� ���� ��´�
void timeManager::render(HDC hdc)
{
	char str[256];
	string strFrame;

	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(0, 0, 0));

	//if (_timer != NULL)
	//{
	//	//������ ��´�
	//	sprintf(str, "FramePerSec : %d", _timer->getFrameRate());
	//	TextOut(hdc, 0, WINSIZEY - 60, str, strlen(str));

	//	//����ð� ��´�
	//	sprintf(str, "worldTime : %f", _timer->getWorldTime());
	//	TextOut(hdc, 0, WINSIZEY - 40, str, strlen(str));

	//	//���Žð� ��´�
	//	sprintf(str, "elapsedTime : %f", _timer->getElapsedTime());
	//	TextOut(hdc, 0, WINSIZEY - 20, str, strlen(str));
	//}
}
