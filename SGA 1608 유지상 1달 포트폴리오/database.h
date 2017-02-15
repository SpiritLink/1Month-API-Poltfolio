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

	float playerX;			//�÷��̾��� X��ǥ
	float playerY;			//�÷��̾��� Y��ǥ
	int backgroundCount;	//����� �����̱� ���� ����

	float eriX;				//���� �⺻���� ��ǥ ������Ʈ�� ���� ����
	float eriY;				//���� �⺻���� ��ǥ ������Ʈ�� ���� ����
	int HP;					//�÷��̾��� HP
	int MP;					//�÷��̾��� MP
	int MAXHP;				//�÷��̾��� �ִ�ü��
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
	float getPlayerX() { return playerX; }
	float getPlayerY() { return playerY; }
	float getEriX() { return eriX; }
	float getEriY() { return eriY; }
	int getbackgroundCount() { return backgroundCount; }
	bool getShowPlayer() { return showPlayer; }
	int getMaxHP() { return MAXHP; }

	bool setShowPlayer(bool trueOrFalse) { showPlayer = trueOrFalse; }
	void setSourCamX(int X) { sourCamX = X; }	//������ (�÷��̾�) X�� ����
	void setSourCamY(int Y) { sourCamY = Y; }	//������ (�÷��̾�) Y�� ����
	void setDestCamX(int X) { destCamX = X; }	//�������� (�þ�) X�� ����
	void setDestCamY(int Y) { destCamY = Y; }	//�������� (�þ�) Y�� ����
	void setBaseTime(float time) { baseTime = time; }	//���ؽð� (������Ʈ Ƚ�� ����) ����
	void setCollisionTile(int tileNum) { playerCollisionTile = tileNum; }
	void setHP(int value) { HP = value; }
	void setMP(int value) { MP = value; }
	void setPlayerX(float x) { playerX = x; }
	void setPlayerY(float y) { playerY = y; }
	void setEriX(float x) { eriX = x; }
	void setEriY(float y) { eriY = y; }
	void setMaxHP(int value) { MAXHP = value; }

	void saveDataToFile();		//�÷��̾��� ������ ���Ͽ� �����ϴ� �Լ��Դϴ�.
	void loadDataFromFile();	//�÷��̾��� ������ ���Ϸκ��� �ҷ����� �Լ��Դϴ�.
	void addBackgroundCount(int value) { backgroundCount += value; }
	
	void initBackgroundCount() { backgroundCount = 0; }
	database();
	~database();
};

