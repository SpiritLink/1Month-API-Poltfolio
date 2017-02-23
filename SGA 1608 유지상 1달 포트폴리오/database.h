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

	float playerX;			//�÷��̾��� X��ǥ
	float playerY;			//�÷��̾��� Y��ǥ
	int backgroundCount;	//����� �����̱� ���� ����

	float eriX;				//���� �⺻���� ��ǥ ������Ʈ�� ���� ����
	float eriY;				//���� �⺻���� ��ǥ ������Ʈ�� ���� ����
	int HP;					//�÷��̾��� HP
	int MP;					//�÷��̾��� MP
	int MAXHP;				//�÷��̾��� �ִ�ü��

	float saveTime;
	bool canSave;

	int blackAlphaValue;	//���� ȭ���� ������ �����մϴ�.
	int whiteAlphaValue;	//�� ȭ���� ������ �����մϴ�.

	bool goEnding;			//�������� ���� Ȯ���ϴ� ����
	bool playerDie;			//�÷��̾ �׾����� Ȯ���ϴ� ����
	bool restart;			//������ ����ŸƮ�� ����������
	bool menu;				//������ �޴��� ����������
	bool isBossDie;			//������ �׾����� Ȯ���ϴ� ����
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
	int getCollisionTile() { return playerCollisionTile; }
	int getHP() { return HP; }
	int getMP() { return MP; }
	float getPlayerX() { return playerX; }
	float getPlayerY() { return playerY; }
	float getEriX() { return eriX; }
	float getEriY() { return eriY; }
	int getbackgroundCount() { return backgroundCount; }
	int getMaxHP() { return MAXHP; }
	float getSaveTime() { return saveTime; }
	bool getCanSave() { return canSave; }
	bool getGoEnding() { return goEnding; }
	int getBlackAlphaValue() { return blackAlphaValue; }
	int getWhiteAlphaValue() { return whiteAlphaValue; }
	bool getPlayerDie() { return playerDie; }
	bool getRestart() { return restart; }
	bool getMenu() { return menu; }
	bool getBossDie() { return isBossDie; }

	void setSourCamX(int X) { sourCamX = X; }	//������ (�÷��̾�) X�� ����
	void setSourCamY(int Y) { sourCamY = Y; }	//������ (�÷��̾�) Y�� ����
	void setDestCamX(int X) { destCamX = X; }	//�������� (�þ�) X�� ����
	void setDestCamY(int Y) { destCamY = Y; }	//�������� (�þ�) Y�� ����
	void setCollisionTile(int tileNum) { playerCollisionTile = tileNum; }
	void setHP(int value) { HP = value; }
	void setMP(int value) { MP = value; }
	void setPlayerX(float x) { playerX = x; }
	void setPlayerY(float y) { playerY = y; }
	void setEriX(float x) { eriX = x; }
	void setEriY(float y) { eriY = y; }
	void setMaxHP(int value) { MAXHP = value; }
	void setSaveTime(float time) { saveTime = time; }
	void setCanSave(bool can) { canSave = can; }
	void setGoEnding(bool value) { goEnding = value; }
	void setBlackAlphaValue(int value) { blackAlphaValue = value; }
	void setWhiteAlphaValue(int value) { whiteAlphaValue = value; }
	void setPlayerDie(bool value) { playerDie = value; }
	void setRestart(bool value) { restart = value; }
	void setMenu(bool value) { menu = value; }
	void setBossDie(bool value) { isBossDie = value; }


	void saveDataToFile();		//�÷��̾��� ������ ���Ͽ� �����ϴ� �Լ��Դϴ�.
	void loadDataFromFile();	//�÷��̾��� ������ ���Ϸκ��� �ҷ����� �Լ��Դϴ�.
	vector<string> loadDataFromFile(int value);	//�÷��̾��� ������ �ҷ��µ� ��ȯ�ϴ� �Լ��Դϴ�.
	void addBackgroundCount(int value) { backgroundCount += value; }
	
	void initBackgroundCount() {  }
	database();
	~database();
};

