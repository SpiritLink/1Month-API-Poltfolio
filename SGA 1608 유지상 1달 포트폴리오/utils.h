#pragma once

#define DEG_TO_RAD	0.017453f
#define PI			3.141592654f
#define PI2			6.283185308f

#define PI_8 float(PI/8.0f)
#define PI_16 float(PI/16.0f)
#define PI_32 float(PI/32.0f)
#define PI_64 float(PI/64.0f)
#define PI_128 float(PI/128.0f)

#define FLOAT_EPSILON	0.001f;
#define FLOAT_TO_INT(f1) static_cast<int>(f1+ FLOAT_EPSILON)
#define FLOAT_EQUAL(f1,f2) (fabs(f1-f2) <= FLOAT_EPSILON)
//fabs는 소수점 차의 절대값을 반환한다

namespace MY_UTIL
{
	//두 점 사이의 거리를 구한다
	float getDistance(float x1, float y1, float x2, float y2);

	///두 점 사이의 각도를 구한다.
	float getAngle(float x1, float y1, float x2, float y2);

};

