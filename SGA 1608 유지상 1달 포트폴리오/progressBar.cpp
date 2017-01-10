#include "stdafx.h"
#include "progressBar.h"


progressBar::progressBar()
{
}


progressBar::~progressBar()
{
}

HRESULT progressBar::init(int x, int y, int width, int height)
{
	_x = x;
	_y = y;

	_rc = RectMakeCenter(_x, _y, width, height);

	_progressBarDown = IMAGEMANAGER->addImage("barDown", "hpBarDown.bmp",
		0, 0, width, height, true, RGB(255, 0, 255));

	_progressBarUp = IMAGEMANAGER->addImage("barUp", "hpBarUp.bmp",
		0, 0, width, height, true, RGB(255, 0, 255));

	_width = width;


	return S_OK;
}

HRESULT progressBar::init(char * btnUpImageKeyName, char * btnDownImageKeyName, int x, int y, int width, int height)
{
	_keyBarBottom = btnDownImageKeyName;
	_keyBarTop = btnUpImageKeyName;

	_x = x;
	_y = y;

	_rc = RectMakeCenter(_x, _y, width, height);

	char strUpKey[128];
	char strUpName[128];
	char strDownKey[128];
	char strDownName[128];

	ZeroMemory(strUpKey, sizeof(strUpKey));
	ZeroMemory(strUpName, sizeof(strUpName));
	ZeroMemory(strDownKey, sizeof(strDownKey));
	ZeroMemory(strDownName, sizeof(strDownName));

	sprintf(strUpKey, btnUpImageKeyName);
	sprintf(strUpName, "%s.bmp", btnUpImageKeyName);
	sprintf(strDownKey, btnDownImageKeyName);
	sprintf(strDownName, "%s.bmp", btnDownImageKeyName);

	_progressBarDown = IMAGEMANAGER->addImage(strDownKey, strDownName,
		0, 0, width, height, true, RGB(255, 0, 255));

	_progressBarUp = IMAGEMANAGER->addImage(strUpKey, strUpName,
		0, 0, width, height, true, RGB(255, 0, 255));

	_width = width;


	return S_OK;
}

void progressBar::release()
{

}

void progressBar::update()
{
	_rc = RectMakeCenter(_x, _y, _progressBarDown->getWidth(), _progressBarDown->getHeight());
}

void progressBar::render()
{
	_progressBarDown->render(getMemDC(), _rc.left, _rc.top, 0, 0, _progressBarDown->getWidth(), _progressBarDown->getHeight());

	_progressBarUp->render(getMemDC(), _rc.left, _rc.top, 0, 0, _width, _progressBarDown->getHeight());
}

void progressBar::setGuage(float currentScore, float maxScore)
{
	_width = (currentScore / maxScore) * _progressBarDown->getWidth();
}

