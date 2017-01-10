#include "stdafx.h"
#include "timer.h"
#include <MMSystem.h>

//TimeGetTime 함수를 사용하기 위한 라이브러리임
#pragma comment (lib, "winmm.lib")

//초기화
HRESULT timer::init()
{
	//고급시계를 쓸 수 있는지 판단
	//_periodFrequency 값에 초당 파악할 수 있는 시간이 들어간다
	//밀리쎄컨까지 계산 가능하다면 1000의 값이 들어감
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&_periodFrequency))
	{
		_isHardware = true;
		QueryPerformanceCounter((LARGE_INTEGER*)&_lastTime);

		//초당 시간을 계산할 수 있는 주기
		_timeScale = 1.0f / _periodFrequency;

	}
	else
	{
		_isHardware = false;
		_lastTime = timeGetTime(); //밀리쎄컨 단위 시간으로 초당 1000
		_timeScale = 0.001f;
	}

	_frameRate = 0;
	_FPSFrameCount = 0;
	_FPSTimeElapsed = 0.0f;
	_worldTime = 0.0f;

	return S_OK;
}

//현재 시간을 계산한다
void timer::tick(float lockFPS)
{
	//지원 되면
	if (_isHardware)
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&_lastTime);
	}
	else
	{
		_curTime = timeGetTime();
	}

	//마지막 시간과 현재시간의 경과량을 측정한다
	_timeElapsed = (_curTime - _lastTime) * _timeScale;

	if (lockFPS > 0.0f)
	{
		while (_timeElapsed < (1.0f / lockFPS))
		{
			if (_isHardware) QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
			else _curTime = timeGetTime();

			//마지막 시간과 현재시간의 경과량을 측정한다
			_timeElapsed = (_curTime - _lastTime) * _timeScale;
		}
	}

	//마지막 시간을 기록한다
	_lastTime = _curTime;

	//초당 프레임 카운트 증가시킨다
	_FPSFrameCount++;

	//초당 프레임 시간 경과량을 측정한다
	_FPSTimeElapsed += _timeElapsed;

	//전체 시간 경과량을 측정한다
	_worldTime += _timeElapsed;

	//프레임 1초마다 초기화 한다
	if (_FPSTimeElapsed > 1.0f)
	{
		_frameRate = _FPSFrameCount;
		_FPSFrameCount = 0;
		_FPSTimeElapsed = 0.0f;
	}
}

//현재 FPS
unsigned long timer::getFrameRate(char* str) const
{
	if (str != NULL)
	{
		sprintf(str, "fps : %d", _frameRate);

	}
	return _frameRate;
}