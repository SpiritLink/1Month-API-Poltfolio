#pragma once

#include "gameNode.h"

class progressBar : public gameNode
{
private:
	RECT _rc;
	int _x;
	int _y;
	float _width;

	char* _keyBarBottom;
	char* _keyBarTop;

	image* _progressBarDown;
	image* _progressBarUp;

public:
	virtual HRESULT init(int x, int y, int width, int height);
	virtual HRESULT init(char* btnUpImageKeyName, char* btnDownImageKeyName,
		int x, int y, int width, int height);
	virtual void release();
	virtual void update();
	virtual void render();

	void setGuage(float currentScore, float maxScore);
	void setX(int x) { _x = x; }
	void setY(int y) { _y = y; }

	RECT getRect() { return _rc; }

	progressBar();
	virtual ~progressBar();
};

