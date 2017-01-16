#pragma once

namespace MY_UTIL
{
	//두 점 사이의 거리를 구한다
	float getDistance(float x1, float y1, float x2, float y2);

	//두 점 사이의 각도를 구한다.
	float getAngle(float x1, float y1, float x2, float y2);

	//디그리를 라디안 값으로
	float degreeToRadian(float degree);

	//라디안을 디그리 값으로
	float radianToDegree(float Radian);
};

