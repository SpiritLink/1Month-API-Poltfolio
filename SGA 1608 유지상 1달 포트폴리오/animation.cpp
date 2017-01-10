#include "stdafx.h"
#include "animation.h"


animation::animation()
	:_frameNum(0)
	, _frameWidth(0)
	, _frameHeight(0)
	, _frameNumWidth(0)
	, _frameNumHeight(0)
	, _loop(false)
	, _frameUpdateSec(0)
	, _elapsedSec(0)
	, _nowPlayInx(0)
	, _isPlay(false)
	, _callbackFunction(NULL)
{
}


animation::~animation()
{
}

HRESULT animation::init(int totalW, int totalH, int frameW, int frameH)
{
	//가로 프레임
	_frameWidth = frameW;
	_frameNumWidth = totalW / _frameWidth;

	//세로 프레임
	_frameHeight = frameH;
	_frameNumHeight = totalH / _frameHeight;

	//총 프레임 갯수
	_frameNum = _frameNumWidth * _frameNumHeight;

	//프레임 위치 리스트 셋팅
	_frameList.clear();
	for (int i = 0; i < _frameNumHeight; ++i)
	{
		for (int j = 0; j < _frameNumWidth; ++j)
		{
			POINT framePos;
			framePos.x = j * _frameWidth;
			framePos.y = i * _frameHeight;

			_frameList.push_back(framePos);
		}
	}

	setDefPlayFrame();

	return S_OK;
}

void animation::release()
{

}

void animation::update()
{

}

void animation::render()
{

}

void animation::setDefPlayFrame(BOOL reverse, BOOL loop)
{
	//뺑뺑이 돌거냐?
	_loop = loop;

	_playList.clear();

	//갈 때 프레임
	for (int i = 0; i < _frameNum; ++i)
	{
		_playList.push_back(i);
	}
	if (reverse)
	{
		for (int i = _frameNum - 1; i >= 0; --i)
		{
			_playList.push_back(i);
		}
	}
}

//원하는 프레임만 재생
void animation::setPlayFrame(int* playArr, int arrLen, BOOL loop)
{
	//뺑뺑이
	_loop = loop;

	//플레이 리스트 클리어
	_playList.clear();

	//갈때 프레임
	for (int i = 0; i < arrLen; ++i)
	{
		_playList.push_back(playArr[i]);
	}
}

//구간을 잘라서 재생
void animation::setPlayFrame(int start, int end, BOOL reverse, BOOL loop)
{
	_loop = loop;

	_playList.clear();

	if (start == end)
	{
		_playList.push_back(start);
		return;
	}

	if (start > end)
	{
		//갈 때
		for (int i = start; i >= end; --i)
		{
			_playList.push_back(i);
		}
		if (reverse)
		{
			//올 때
			for (int i = end + 1; i < start; ++i)
			{
				_playList.push_back(i);
			}
		}

	}
	else
	{
		//갈 때
		for (int i = start; i <= end; ++i)
		{
			_playList.push_back(i);
		}
		if (reverse)
		{
			//올 때
			for (int i = end - 1; i > start; --i)
			{
				_playList.push_back(i);
			}
		}
	}
}

//초당 프레임 갱신 횟수
void animation::setFPS(int framePerSec)
{
	_frameUpdateSec = 1.0 / framePerSec;
}

//프레임 업데이트
void animation::frameUpdate(float elapsedTime)
{
	if (_isPlay)
	{
		_elapsedSec += elapsedTime;

		//프레임 업데이트 시간이 다 되었으면
		if (_elapsedSec >= _frameUpdateSec)
		{
			_elapsedSec -= _frameUpdateSec;
			_nowPlayInx++;
			if (_nowPlayInx == _playList.size())
			{
				//뺑뺑이냐?
				if (_loop)
				{
					_nowPlayInx = 0;
				}
				else
				{
					_nowPlayInx--;
					_isPlay = false;
					if (_callbackFunction != NULL) _callbackFunction(_targetClass);
				}
			}
		}
	}
}

void animation::start()
{
	_isPlay = true;
	_nowPlayInx = 0;
}

void animation::start(CALLBACKCLASS cbFunction, void * targetClass)
{
	_isPlay = true;
	_nowPlayInx = 0;

	_callbackFunction = static_cast<CALLBACKCLASS>(cbFunction);
	_targetClass = targetClass;
}

void animation::stop()
{
	_isPlay = false;
	_nowPlayInx = 0;
}

void animation::pause()
{
	_isPlay = false;
}

void animation::resume()
{
	_isPlay = TRUE;
}
