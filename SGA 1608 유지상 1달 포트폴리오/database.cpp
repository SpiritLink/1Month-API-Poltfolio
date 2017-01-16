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
	loadDatabase("databaseSave.txt");

	return S_OK;
}

void database::release()
{

}

void database::loadDatabase(const char* fileName)
{
	arrElements vTemp;
	vTemp = TXTMANAGER->load(fileName);

	string str;
	int count = 0;

	if (vTemp.empty())
	{
		for (int i = 0; i < 2; ++i)
		{
			elements* em = new elements;
			if (i == 0)
			{
				str = "battle";
				_mTotalElement.insert(make_pair(str, em));
			}
			else
			{
				str = "carrier";
				_mTotalElement.insert(make_pair(str, em));
			}
			iterElement mIter = _mTotalElement.find(str);
			mIter->second->name = str.c_str();
			mIter->second->increaseSpeed = 0.0f;
			mIter->second->maxSpeed = 0.0f;
			mIter->second->angle = 0.0f;
			mIter->second->currentHP = 0;
			mIter->second->maxHP = 0;

		}
	}



	for (int i = 0; i < vTemp.size(); ++i)
	{
		if (vTemp[i] == "|")
		{
			elements* em = new elements;
			str = vTemp[i + 1];
			_mTotalElement.insert(make_pair(str, em));
			if (i != 0) count += 7;
			continue;
		}
		iterElement mIter = _mTotalElement.find(str);
		if (i == count + 1) mIter->second->name = vTemp[i].c_str();
		else if (i == count + 2) mIter->second->increaseSpeed = (float)atof(vTemp[i].c_str());
		else if (i == count + 3) mIter->second->maxSpeed = (float)atof(vTemp[i].c_str());
		else if (i == count + 4) mIter->second->angle = (float)atof(vTemp[i].c_str());
		else if (i == count + 5) mIter->second->currentHP = (int)atoi(vTemp[i].c_str());
		else if (i == count + 6) mIter->second->maxHP = (int)atoi(vTemp[i].c_str());

	}
	vTemp.clear();
}

void database::saveDatabase()
{
	arrElements vTemp;
	iterElement mIter = _mTotalElement.find("battle");
	char temp[100];

	vTemp.push_back("|");
	vTemp.push_back(mIter->first);
	vTemp.push_back((char*)gcvt(mIter->second->increaseSpeed, 2, temp));
	vTemp.push_back((char*)gcvt(mIter->second->maxSpeed, 2, temp));
	vTemp.push_back((char*)gcvt(mIter->second->angle, 2, temp));
	vTemp.push_back((char*)itoa(mIter->second->currentHP, temp, 10));
	vTemp.push_back((char*)itoa(mIter->second->maxHP, temp, 10));

	//실수를 문자열로 변환
	//원형 char* gcvt(double value, int nod, char* buf);
	//val : 변환될 실수 값
	//nod : 부호와 소수점을 제외한 숫자 갯수
	//buf : 변환된 val값을 받을 문자열

	mIter = _mTotalElement.find("carrier");

	vTemp.push_back("|");
	vTemp.push_back(mIter->first);
	vTemp.push_back((char*)gcvt(mIter->second->increaseSpeed, 2, temp));
	vTemp.push_back((char*)gcvt(mIter->second->maxSpeed, 2, temp));
	vTemp.push_back((char*)gcvt(mIter->second->angle, 2, temp));
	vTemp.push_back((char*)itoa(mIter->second->currentHP, temp, 10));
	vTemp.push_back((char*)itoa(mIter->second->maxHP, temp, 10));

	TXTMANAGER->save("databaseSave.txt", vTemp);

	vTemp.clear();
}

void database::setElementDataIncreaseSpeed(string str, float is)
{
	iterElement mIter = _mTotalElement.find(str);
	mIter->second->increaseSpeed = is;
}

void database::setElementDataMaxSpeed(string str, float ms)
{
	iterElement mIter = _mTotalElement.find(str);
	mIter->second->maxSpeed = ms;
}

void database::setElementDataAngle(string str, float a)
{
	iterElement mIter = _mTotalElement.find(str);
	mIter->second->angle = a;


}

void database::setElementDataCurrentHP(string str, int ch)
{
	iterElement mIter = _mTotalElement.find(str);
	mIter->second->currentHP = ch;
}

void database::setElementDataMaxHP(string str, int mh)
{
	iterElement mIter = _mTotalElement.find(str);
	mIter->second->maxHP = mh;
}

float database::getCamDistanceX()
{
	float distance = getDistance(sourCamX, sourCamY, destCamX, destCamY);
	float angle = getAngle(sourCamX, sourCamY, destCamX, destCamY);

	if (angle <= 2.0f * PI) return cosf(angle) * distance;
	else					return 0.0f;
}

float database::getCamDistanceY()
{
	float distance = getDistance(sourCamX, sourCamY, destCamX, destCamY);
	float angle = getAngle(sourCamX, sourCamY, destCamX, destCamY);

	if (angle <= 2.0f * PI) return -sinf(angle) * distance;
	else					return 0.0f;
}
