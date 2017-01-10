#pragma once

#include "singletonBase.h"
#include "timer.h"

class timeManager : public singletonBase<timeManager>
{
private:
	timer* _timer;

public:
	//초기화
	HRESULT init();

	//릴리즈
	void release();

	//프레임 적용
	void update(float lock = 0.0f);

	//해당 HDC에 정보 찍는다
	void render(HDC hdc);

	//전체 시간 가져온다
	inline float getWorldTime() const { return _timer->getWorldTime(); }

	//프레임 경과 시간
	inline float getElapsedTime() const { return _timer->getElapsedTime(); }

	timeManager();
	~timeManager();
};

