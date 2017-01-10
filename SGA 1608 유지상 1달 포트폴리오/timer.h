#pragma once
class timer
{
private:
	bool			_isHardware;		//��޽ð� ���� �ǳ�?
	float			_timeScale;			//����ð��� ����
	float			_timeElapsed;		//������ �ð��� ����ð��� �����

	__int64			_curTime;			//����ð�
	__int64			_lastTime;			//�����ð�
	__int64			_periodFrequency;	//�ð��ֱ�

	unsigned long	_frameRate;			//FPS(�ʴ� ������ ��)
	unsigned long	_FPSFrameCount;		//FPSī��Ʈ
	float			_FPSTimeElapsed;	//FPS����ð�
	float			_worldTime;			//������ ���۵� �� ����� ��ü�ð�

public:
	//�ʱ�ȭ
	HRESULT init();

	//���� �ð��� ����Ѵ�
	void tick(float lockFPS = 0.0f);

	//���� FPS
	unsigned long getFrameRate(char* str = NULL) const;

	//������ �ð��� ���� �ð��� �����
	inline float getElapsedTime() const { return _timeElapsed; }

	//��ü ��� �ð�
	inline float getWorldTime() const { return _worldTime; }

	timer() {};
	~timer() {};
};

