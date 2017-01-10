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

		//acosf(x) x는 -1~1의 값을 가진다 (라디안 값)
		//cos의 역함수이며, 치역은 (0~180 degree)
		//180도가 넘어가면 181도가 아니라 179도가 된다

		if (y > 0) angle = PI * 2 - angle;
		return angle;
	}
}