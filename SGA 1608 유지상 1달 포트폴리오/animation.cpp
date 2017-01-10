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
	//���� ������
	_frameWidth = frameW;
	_frameNumWidth = totalW / _frameWidth;

	//���� ������
	_frameHeight = frameH;
	_frameNumHeight = totalH / _frameHeight;

	//�� ������ ����
	_frameNum = _frameNumWidth * _frameNumHeight;

	//������ ��ġ ����Ʈ ����
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
	//������ ���ų�?
	_loop = loop;

	_playList.clear();

	//�� �� ������
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

//���ϴ� �����Ӹ� ���
void animation::setPlayFrame(int* playArr, int arrLen, BOOL loop)
{
	//������
	_loop = loop;

	//�÷��� ����Ʈ Ŭ����
	_playList.clear();

	//���� ������
	for (int i = 0; i < arrLen; ++i)
	{
		_playList.push_back(playArr[i]);
	}
}

//������ �߶� ���
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
		//�� ��
		for (int i = start; i >= end; --i)
		{
			_playList.push_back(i);
		}
		if (reverse)
		{
			//�� ��
			for (int i = end + 1; i < start; ++i)
			{
				_playList.push_back(i);
			}
		}

	}
	else
	{
		//�� ��
		for (int i = start; i <= end; ++i)
		{
			_playList.push_back(i);
		}
		if (reverse)
		{
			//�� ��
			for (int i = end - 1; i > start; --i)
			{
				_playList.push_back(i);
			}
		}
	}
}

//�ʴ� ������ ���� Ƚ��
void animation::setFPS(int framePerSec)
{
	_frameUpdateSec = 1.0 / framePerSec;
}

//������ ������Ʈ
void animation::frameUpdate(float elapsedTime)
{
	if (_isPlay)
	{
		_elapsedSec += elapsedTime;

		//������ ������Ʈ �ð��� �� �Ǿ�����
		if (_elapsedSec >= _frameUpdateSec)
		{
			_elapsedSec -= _frameUpdateSec;
			_nowPlayInx++;
			if (_nowPlayInx == _playList.size())
			{
				//�����̳�?
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
