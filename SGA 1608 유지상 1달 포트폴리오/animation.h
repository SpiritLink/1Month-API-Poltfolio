#pragma once

#include "gameNode.h"

typedef void(*CALLBACKCLASS)(void* targetClass);

class animation : public gameNode
{
private:
	typedef vector<POINT> _vFrameList;
	typedef vector<int> _vPlayList;

	int _frameNum;				//프레임 수

	_vFrameList _frameList;		//프레임 위치 리스트
	_vPlayList _playList;		//플레이 리스트

	int	_frameWidth;			//프레임 가로크기
	int _frameHeight;			//프레인 세로크기

	int _frameNumWidth;			//가로 프레임 총 갯수
	int _frameNumHeight;		//세로 프레임 총 갯수

	BOOL _loop;					//뺑뺑이냐?
	float _frameUpdateSec;		//초당 프레임 업데이트 수
	float _elapsedSec;			//프레임과 프레임 사이의 시간

	DWORD _nowPlayInx;			//현재 플레이 인덱스
	BOOL _isPlay;				//플레이 중이냐?

	CALLBACKCLASS _callbackFunction;
	void* _targetClass;

public:
	virtual HRESULT init(int totalW, int totalH, int frameW, int frameH);
	virtual void release();
	virtual void update();
	virtual void render();

	void setDefPlayFrame(BOOL reverse = NULL, BOOL loop = NULL);
	void setPlayFrame(int* playArr = NULL, int arrLen = 0, BOOL loop = NULL);
	void setPlayFrame(int start, int end, BOOL reverse = NULL, BOOL loop = NULL);

	//초당 프레임 갱신 횟수
	void setFPS(int framePerSec);

	//프레임 업데이트
	void frameUpdate(float elapsedTime);

	void start();
	void start(CALLBACKCLASS cbFunction, void* targetClass);
	void stop();
	void pause();
	void resume();

	//플레이 중이냐?
	inline BOOL isPlay() { return _isPlay; }

	//프레임 위치 얻어온다
	inline POINT getFramePos() { return _frameList[_playList[_nowPlayInx]]; }

	//현재 애니메이션 프레임 위치 순서를 얻어온다
	inline int getFrameIdx()
	{
		POINT ptPos = getFramePos();
		int frameX = ptPos.x / _frameNumWidth;
		int frameY = ptPos.y / _frameNumHeight;
		return frameX + frameY * _frameNumWidth;
	}

	//프레임 가로크기를 얻어온다
	inline int getFrameWidth() { return _frameWidth; }

	//프레임 세로크기를 얻어온다
	inline int getFrameHeight() { return _frameHeight; }

	//현재 몇번째 프레임 순서인지 얻는다
	inline DWORD getNowPlayIdx();

	animation();
	virtual ~animation();
};

