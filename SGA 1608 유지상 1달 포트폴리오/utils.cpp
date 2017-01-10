#include "stdafx.h"
#include "utils.h"

namespace MY_UTIL
{
	float getDistance(float x1, float y1, float x2, float y2)
	{
		float x = x2 - x1;
		float y = y2 - y1;
		return sqrtf(x*x + y*y);
	}

	float getAngle(float x1, float y1, float x2, float y2)
	{
		float x = x2 - x1;
		float y = y2 - y1;
		float d = sqrtf(x*x + y*y);
		float angle = acosf(x / d);
		//float angle = atanf(y/x);

		//acosf(x) x�� -1~1�� ���� ������ (���� ��)
		//cos�� ���Լ��̸�, ġ���� (0~180 degree)
		//180���� �Ѿ�� 181���� �ƴ϶� 179���� �ȴ�

		if (y > 0) angle = PI * 2 - angle;
		return angle;
	}
}