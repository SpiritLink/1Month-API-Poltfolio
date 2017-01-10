#pragma once

#include "singletonBase.h"

#define SAVEBUFFER 128
#define LOADBUFFER 128

class txtDataManager :public singletonBase<txtDataManager>
{
private:

public:
	HRESULT init();
	void release();

	//���̺�
	void save(const char* fileName, vector<string> vStr);
	char* vectorArrayCombine(vector<string> vArray);

	//�ε�
	vector<string> load(const char* fileName);
	vector<string> charArraySeparation(char charArray[]);

	txtDataManager();
	~txtDataManager();
};

