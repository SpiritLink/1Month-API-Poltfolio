#pragma once

#include "singletonBase.h"

class elements
{
public:
	const char* name;
	float increaseSpeed;
	float maxSpeed;
	float angle;
	int currentHP;
	int maxHP;

	elements() {};
	~elements() {};
};

class database : public singletonBase <database>
{
private:
	typedef vector<string> arrElements;
	typedef vector<string>::iterator iterElements;
	typedef map<string, elements*> arrElement;
	typedef map<string, elements*>::iterator iterElement;

	arrElement _mTotalElement;

	float angle;			//각도
	int sourCamX;			//기준점 (플레이어)
	int sourCamY;
	int destCamX;			//목적지점 (시야가 고정되기를 원하는 좌표)
	int destCamY;
	float baseTime;			//기준시간 (업데이트 횟수를 적당히 줄이기 위해서)
public:
	HRESULT init();
	void release();
	void loadDatabase(const char* fileName);
	void saveDatabase();

	elements* getElementData(string str) { return _mTotalElement.find(str)->second; }

	void setElementDataIncreaseSpeed(string str, float is);
	void setElementDataMaxSpeed(string str, float ms);
	void setElementDataAngle(string str, float a);
	void setElementDataCurrentHP(string str, int ch);
	void setElementDataMaxHP(string str, int mh);

	int getSourCamX() { return sourCamX; }	//기준점 X좌표를 얻어옴
	int getSourCamY() { return sourCamY; }	//기준점 Y좌표를 얻어옴
	int getDestCamX() { return destCamX; }	//목적지점 X좌표를 얻어옴
	int getDestCamY() { return destCamY; }	//목적지점 Y좌표를 얻어옴
	int getCamDistanceX();					//두 좌표 사이의 X 이동거리를 얻어옴
	int getCamDistanceY();					//두 좌표 사이의 Y 이동거리를 얻어옴
	float getCamAngle();	//두 좌표의 각도를 얻어온다.
	float getBaseTime() { return baseTime; }	//기준시간을 반환함 (업데이트 횟수 조절을 위한 용도)

	void setSourCamX(int X) { sourCamX = X; }	//기준점 (플레이어) X를 설정
	void setSourCamY(int Y) { sourCamY = Y; }	//기준점 (플레이어) Y를 설정
	void setDestCamX(int X) { destCamX = X; }	//목적지점 (시야) X를 설정
	void setDestCamY(int Y) { destCamY = Y; }	//목적지점 (시야) Y를 설정
	void setBaseTime(float time) { baseTime = time; }	//기준시간 (업데이트 횟수 조절) 설정

	database();
	~database();
};

