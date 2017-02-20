#include "stdafx.h"
#include "timeManager.h"


timeManager::timeManager()
{
}


timeManager::~timeManager()
{
}

//초기화
HRESULT timeManager::init()
{
	//타이머 생성한다
	_timer = new timer;
	_timer->init();

	return S_OK;
}

//릴리즈
void timeManager::release()
{
	//타이머 삭제

	SAFE_DELETE(_timer);
	_timer = NULL;

}

//프레임 적용
void timeManager::update(float lock)
{
	if (_timer != NULL)
	{
		_timer->tick(lock);
	}
}

//해당 HDC에 정보 찍는다
void timeManager::render(HDC hdc)
{
	char str[256];
	string strFrame;

	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(0, 0, 0));

	//if (_timer != NULL)
	//{
	//	//프레임 찍는다
	//	sprintf(str, "FramePerSec : %d", _timer->getFrameRate());
	//	TextOut(hdc, 0, WINSIZEY - 60, str, strlen(str));

	//	//경과시간 찍는다
	//	sprintf(str, "worldTime : %f", _timer->getWorldTime());
	//	TextOut(hdc, 0, WINSIZEY - 40, str, strlen(str));

	//	//갱신시간 찍는다
	//	sprintf(str, "elapsedTime : %f", _timer->getElapsedTime());
	//	TextOut(hdc, 0, WINSIZEY - 20, str, strlen(str));
	//}
}
