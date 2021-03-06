#pragma once

#include "singletonBase.h"
#include <time.h>
#include "stdlib.h"

class randomFunction : public singletonBase<randomFunction>
{
public:
	randomFunction()
	{
		srand(GetTickCount()); //밀리세컨 1000 == 1초
	}
	~randomFunction()
	{
	}

	//getInt
	int getInt(int num) { return rand() % num; }

	int getFromIntTo(int fromNum, int toNum)
	{
		return (rand() % (toNum - fromNum + 1)) + fromNum;
	}

	//getFloat
	//0.0~1.0 RAND_MAX의 최대값(32767)
	float getFloat() { return (float)rand() / (float)RAND_MAX; }
	float getFloat(float num) { return (float)rand() / (float)RAND_MAX * num; }
	float getFromFloatTo(float fromNum, float toNum)
	{
		float rnd = (float)rand() / (float)RAND_MAX;
		return (rnd * (toNum - fromNum) + fromNum);
	}
};