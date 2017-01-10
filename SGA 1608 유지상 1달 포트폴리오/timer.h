#pragma once
class timer
{
private:
	bool			_isHardware;		//고급시계 지원 되냐?
	float			_timeScale;			//경과시간을 조절
	float			_timeElapsed;		//마지막 시간과 현재시간의 경과값

	__int64			_curTime;			//현재시간
	__int64			_lastTime;			//이전시간
	__int64			_periodFrequency;	//시간주기

	unsigned long	_frameRate;			//FPS(초당 프레임 수)
	unsigned long	_FPSFrameCount;		//FPS카운트
	float			_FPSTimeElapsed;	//FPS경과시간
	float			_worldTime;			//게임이 시작된 후 경과된 전체시간

public:
	//초기화
	HRESULT init();

	//현재 시간을 계산한다
	void tick(float lockFPS = 0.0f);

	//현재 FPS
	unsigned long getFrameRate(char* str = NULL) const;

	//마지막 시간과 현재 시간의 경과량
	inline float getElapsedTime() const { return _timeElapsed; }

	//전체 경과 시간
	inline float getWorldTime() const { return _worldTime; }

	timer() {};
	~timer() {};
};

