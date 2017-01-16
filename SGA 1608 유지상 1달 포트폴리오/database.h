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

	float cameraX;
	float cameraY;
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

	float getCameraX() { return cameraX; }
	float getCameraY() { return cameraY; }
	float getBaseTime() { return baseTime; }

	void setCameraX(float addCameraXValue) { cameraX = addCameraXValue; }
	void setCameraY(float addCameraYValue) { cameraY = addCameraYValue; }
	void setBaseTime(float time) { baseTime = time; }

	database();
	~database();
};

