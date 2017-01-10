#pragma once

#include "gameNode.h"

typedef void(*CALLBACKCLASS)(void* targetClass);

class animation : public gameNode
{
private:
	typedef vector<POINT> _vFrameList;
	typedef vector<int> _vPlayList;

	int _frameNum;				//������ ��

	_vFrameList _frameList;		//������ ��ġ ����Ʈ
	_vPlayList _playList;		//�÷��� ����Ʈ

	int	_frameWidth;			//������ ����ũ��
	int _frameHeight;			//������ ����ũ��

	int _frameNumWidth;			//���� ������ �� ����
	int _frameNumHeight;		//���� ������ �� ����

	BOOL _loop;					//�����̳�?
	float _frameUpdateSec;		//�ʴ� ������ ������Ʈ ��
	float _elapsedSec;			//�����Ӱ� ������ ������ �ð�

	DWORD _nowPlayInx;			//���� �÷��� �ε���
	BOOL _isPlay;				//�÷��� ���̳�?

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

	//�ʴ� ������ ���� Ƚ��
	void setFPS(int framePerSec);

	//������ ������Ʈ
	void frameUpdate(float elapsedTime);

	void start();
	void start(CALLBACKCLASS cbFunction, void* targetClass);
	void stop();
	void pause();
	void resume();

	//�÷��� ���̳�?
	inline BOOL isPlay() { return _isPlay; }

	//������ ��ġ ���´�
	inline POINT getFramePos() { return _frameList[_playList[_nowPlayInx]]; }

	//���� �ִϸ��̼� ������ ��ġ ������ ���´�
	inline int getFrameIdx()
	{
		POINT ptPos = getFramePos();
		int frameX = ptPos.x / _frameNumWidth;
		int frameY = ptPos.y / _frameNumHeight;
		return frameX + frameY * _frameNumWidth;
	}

	//������ ����ũ�⸦ ���´�
	inline int getFrameWidth() { return _frameWidth; }

	//������ ����ũ�⸦ ���´�
	inline int getFrameHeight() { return _frameHeight; }

	//���� ���° ������ �������� ��´�
	inline DWORD getNowPlayIdx();

	animation();
	virtual ~animation();
};

