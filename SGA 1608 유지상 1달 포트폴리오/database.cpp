#include "stdafx.h"
#include "database.h"


void database::saveDataToFile()
{
	vector<string> arrString;
	char temp[100];

	arrString.push_back((char*)itoa(_sceneNumber,temp,10));
	arrString.push_back((char*)itoa(playerCollisionTile, temp, 10));
	arrString.push_back((char*)itoa(MAXHP, temp, 10));
	arrString.push_back((char*)itoa(HP, temp, 10));
	arrString.push_back((char*)itoa(MP, temp, 10));

	switch (_saveCount)
	{
	case 0:	TXTMANAGER->save("DATA/SAVE/save1.data", arrString);	break;
	case 1: TXTMANAGER->save("DATA/SAVE/save2.data", arrString);	break;
	case 2: TXTMANAGER->save("DATA/SAVE/save3.data", arrString);	break;
	}
}

void database::loadDataFromFile()
{
	vector<string> arrString;

	switch (_saveCount)
	{
	case 0: arrString = TXTMANAGER->load("DATA/SAVE/save1.data");	break;
	case 1:	arrString = TXTMANAGER->load("DATA/SAVE/save2.data");	break;
	case 2:	arrString = TXTMANAGER->load("DATA/SAVE/save3.data");	break;
	}

	if (arrString.empty())
	{
		//초기 충돌타일 설정
		_sceneNumber = 1;
		playerCollisionTile = 20709;
		MAXHP = DEFAULT_MAXHP;
		HP = DEFAULT_HP;
		MP = DEFAULT_MP;
	}
	else
	{
		for (int i = 0; i < arrString.size(); ++i)
		{
			switch (i)
			{
			case 0:	_sceneNumber = (int)atoi(arrString[i].c_str()); break;
			case 1:	playerCollisionTile = (int)atoi(arrString[i].c_str()); break;
			case 2:	MAXHP = (int)atoi(arrString[i].c_str()); break;
			case 3:	HP = (int)atoi(arrString[i].c_str()); break;
			case 4:	MP = (int)atoi(arrString[i].c_str()); break;
			}
		}

		//데이터중 일부라도 정상적인 데이터가 아니라면 (초기화한 데이터라면)
		if (_sceneNumber == -1 || playerCollisionTile == -1 || MAXHP == -1 || HP == -1 || MP == -1)
		{
			_sceneNumber = 1;
			playerCollisionTile = 20709;
			MAXHP = DEFAULT_MAXHP;
			HP = DEFAULT_HP;
			MP = DEFAULT_MP;
		}
	}
}

vector<string> database::loadDataFromFile(int value)
{
	vector<string> arrString;

	switch (value)
	{
	case 0: arrString = TXTMANAGER->load("DATA/SAVE/save1.data");	break;
	case 1:	arrString = TXTMANAGER->load("DATA/SAVE/save2.data");	break;
	case 2:	arrString = TXTMANAGER->load("DATA/SAVE/save3.data");	break;
	}
	return arrString;
}

database::database()
{
}


database::~database()
{
}

HRESULT database::init()
{
	initBackgroundCount();
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
