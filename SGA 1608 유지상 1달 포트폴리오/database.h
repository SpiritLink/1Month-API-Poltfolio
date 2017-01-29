#pragma once

#include "singletonBase.h"

class database : public singletonBase <database>
{
private:
	float angle;			//����
	int sourCamX;			//������ (�÷��̾�)
	int sourCamY;
	int destCamX;			//�������� (�þ߰� �����Ǳ⸦ ���ϴ� ��ǥ)
	int destCamY;
	int playerCollisionTile;//�÷��̾ �浹���� Ÿ�� ��ȣ
	float baseTime;			//���ؽð� (������Ʈ Ƚ���� ������ ���̱� ���ؼ�)

	int HP;					//�÷��̾��� HP
	int MP;					//�÷��̾��� MP
	bool showPlayer;
public:
	HRESULT init();
	void release();

	int getSourCamX() { return sourCamX; }	//������ X��ǥ�� ����
	int getSourCamY() { return sourCamY; }	//������ Y��ǥ�� ����
	int getDestCamX() { return destCamX; }	//�������� X��ǥ�� ����
	int getDestCamY() { return destCamY; }	//�������� Y��ǥ�� ����
	int getCamDistanceX();					//�� ��ǥ ������ X �̵��Ÿ��� ����
	int getCamDistanceY();					//�� ��ǥ ������ Y �̵��Ÿ��� ����
	int getCamDistance();
	float getCamAngle();	//�� ��ǥ�� ������ ���´�.
	float getBaseTime() { return baseTime; }	//���ؽð��� ��ȯ�� (������Ʈ Ƚ�� ������ ���� �뵵)
	int getCollisionTile() { return playerCollisionTile; }
	int getHP() { return HP; }
	int getMP() { return MP; }

	bool getShowPlayer() { return showPlayer; }
	bool setShowPlayer(bool trueOrFalse) { showPlayer = trueOrFalse; }

	void setSourCamX(int X) { sourCamX = X; }	//������ (�÷��̾�) X�� ����
	void setSourCamY(int Y) { sourCamY = Y; }	//������ (�÷��̾�) Y�� ����
	void setDestCamX(int X) { destCamX = X; }	//�������� (�þ�) X�� ����
	void setDestCamY(int Y) { destCamY = Y; }	//�������� (�þ�) Y�� ����
	void setBaseTime(float time) { baseTime = time; }	//���ؽð� (������Ʈ Ƚ�� ����) ����
	void setCollisionTile(int tileNum) { playerCollisionTile = tileNum; }
	void setHP(int value) { HP = value; }
	void setMP(int value) { MP = value; }
	database();
	~database();
};

