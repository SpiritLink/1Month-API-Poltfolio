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

	float angle;			//����
	float sourCamX;			//������ (�÷��̾�)
	float sourCamY;
	float destCamX;			//�������� (�þ߰� �����Ǳ⸦ ���ϴ� ��ǥ)
	float destCamY;
	float baseTime;			//���ؽð� (������Ʈ Ƚ���� ������ ���̱� ���ؼ�)
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

	float getSourCamX() { return sourCamX; }	//������ X��ǥ�� ����
	float getSourCamY() { return sourCamY; }	//������ Y��ǥ�� ����
	float getDestCamX() { return destCamX; }	//�������� X��ǥ�� ����
	float getDestCamY() { return destCamY; }	//�������� Y��ǥ�� ����
	float getCamDistanceX();					//�� ��ǥ ������ X �̵��Ÿ��� ����
	float getCamDistanceY();					//�� ��ǥ ������ Y �̵��Ÿ��� ����
	float getCamAngle();	//�� ��ǥ�� ������ ���´�.
	float getBaseTime() { return baseTime; }	//���ؽð��� ��ȯ�� (������Ʈ Ƚ�� ������ ���� �뵵)

	void setSourCamX(float X) { sourCamX = X; }	//������ (�÷��̾�) X�� ����
	void setSourCamY(float Y) { sourCamY = Y; }	//������ (�÷��̾�) Y�� ����
	void setDestCamX(float X) { destCamX = X; }	//�������� (�þ�) X�� ����
	void setDestCamY(float Y) { destCamY = Y; }	//�������� (�þ�) Y�� ����
	void setBaseTime(float time) { baseTime = time; }	//���ؽð� (������Ʈ Ƚ�� ����) ����

	database();
	~database();
};

