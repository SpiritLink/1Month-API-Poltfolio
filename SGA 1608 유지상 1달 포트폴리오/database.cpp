#include "stdafx.h"
#include "database.h"


database::database()
{
}


database::~database()
{
}

HRESULT database::init()
{
	return S_OK;
}

void database::release()
{
}

int database::getCamDistanceX()
{
	float distance = getDistance(destCamX, destCamY, sourCamX, sourCamY);
	float angle = getAngle(destCamX, destCamY, sourCamX, sourCamY);

	if (angle <= 2.0f * PI) return cosf(angle) * distance;
	else					return 0.0f;
}

int database::getCamDistanceY()
{
	float distance = getDistance(destCamX, destCamY, sourCamX, sourCamY);
	float angle = getAngle(destCamX, destCamY, sourCamX, sourCamY);

	if (angle <= 2.0f * PI) return -sinf(angle) * distance;
	else					return 0.0f;
}

int database::getCamDistance()
{
	int distance = getDistance(destCamX, destCamY, sourCamX, sourCamY);
	return distance;
}

float database::getCamAngle()
{
	float Angle = getAngle(destCamX, destCamY, sourCamX, sourCamY);
	return Angle;
}
