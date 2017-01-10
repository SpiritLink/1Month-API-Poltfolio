#pragma once

#include "singletonBase.h"
#include "timer.h"

class timeManager : public singletonBase<timeManager>
{
private:
	timer* _timer;

public:
	//�ʱ�ȭ
	HRESULT init();

	//������
	void release();

	//������ ����
	void update(float lock = 0.0f);

	//�ش� HDC�� ���� ��´�
	void render(HDC hdc);

	//��ü �ð� �����´�
	inline float getWorldTime() const { return _timer->getWorldTime(); }

	//������ ��� �ð�
	inline float getElapsedTime() const { return _timer->getElapsedTime(); }

	timeManager();
	~timeManager();
};

