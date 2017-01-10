#pragma once

template <typename T>
class  singletonBase
{
protected:
	static T* singleton;		//�̱��� �ν��Ͻ� ����

	singletonBase() {};
	~singletonBase() {};

public:
	static T* getSingleton();	//�ν��Ͻ� ���´�
	void releaseSingleton();	//�ν��Ͻ� �����Ѵ�

};

//�̱��� �ʱ�ȭ
template <typename T>
T* singletonBase<T>::singleton = NULL;

//�̱��� �� �����´�
template <typename T>
T* singletonBase<T>::getSingleton()
{
	if (!singleton) singleton = new T;
	return singleton;
}

//�̱��� �޸� ����
template <typename T>
void singletonBase<T>::releaseSingleton()
{
	if (singleton)
	{
		delete singleton;
		singleton = NULL;
	}
}
