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

	float _angle;

	float sourCamX;
	float sourCamY;
	float destCamX;
	float destCamY;
	float baseTime;
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

	float getSourCamX() { return sourCamX; }
	float getSourCamY() { return sourCamY; }
	float getDestCamX() { return destCamX; }
	float getDestCamY() { return destCamY; }
	float getCamDistanceX();
	float getCamDistanceY();
	float getBaseTime() { return baseTime; }

	void setSourCamX(float X) { sourCamX = X; }
	void setSourCamY(float Y) { sourCamY = Y; }
	void setDestCamX(float X) { destCamX = X; }
	void setDestCamY(float Y) { destCamY = Y; }
	void setBaseTime(float time) { baseTime = time; }

	database();
	~database();
};

