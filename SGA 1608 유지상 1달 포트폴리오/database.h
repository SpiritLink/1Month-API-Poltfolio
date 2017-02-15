#pragma once

#include "singletonBase.h"

class database : public singletonBase <database>
{
private:
	float angle;			//각도
	int sourCamX;			//기준점 (플레이어)
	int sourCamY;
	int destCamX;			//목적지점 (시야가 고정되기를 원하는 좌표)
	int destCamY;
	int playerCollisionTile;//플레이어가 충돌중인 타일 번호
	float baseTime;			//기준시간 (업데이트 횟수를 적당히 줄이기 위해서)

	float playerX;			//플레이어의 X좌표
	float playerY;			//플레이어의 Y좌표
	int backgroundCount;	//배경을 움직이기 위한 변수

	float eriX;				//보스 기본공격 좌표 업데이트를 위한 변수
	float eriY;				//보스 기본공격 좌표 업데이트를 위한 변수
	int HP;					//플레이어의 HP
	int MP;					//플레이어의 MP
	int MAXHP;				//플레이어의 최대체력
	bool showPlayer;
public:
	HRESULT init();
	void release();

	int getSourCamX() { return sourCamX; }	//기준점 X좌표를 얻어옴
	int getSourCamY() { return sourCamY; }	//기준점 Y좌표를 얻어옴
	int getDestCamX() { return destCamX; }	//목적지점 X좌표를 얻어옴
	int getDestCamY() { return destCamY; }	//목적지점 Y좌표를 얻어옴
	int getCamDistanceX();					//두 좌표 사이의 X 이동거리를 얻어옴
	int getCamDistanceY();					//두 좌표 사이의 Y 이동거리를 얻어옴
	int getCamDistance();
	float getCamAngle();	//두 좌표의 각도를 얻어온다.
	float getBaseTime() { return baseTime; }	//기준시간을 반환함 (업데이트 횟수 조절을 위한 용도)
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
	void setSourCamX(int X) { sourCamX = X; }	//기준점 (플레이어) X를 설정
	void setSourCamY(int Y) { sourCamY = Y; }	//기준점 (플레이어) Y를 설정
	void setDestCamX(int X) { destCamX = X; }	//목적지점 (시야) X를 설정
	void setDestCamY(int Y) { destCamY = Y; }	//목적지점 (시야) Y를 설정
	void setBaseTime(float time) { baseTime = time; }	//기준시간 (업데이트 횟수 조절) 설정
	void setCollisionTile(int tileNum) { playerCollisionTile = tileNum; }
	void setHP(int value) { HP = value; }
	void setMP(int value) { MP = value; }
	void setPlayerX(float x) { playerX = x; }
	void setPlayerY(float y) { playerY = y; }
	void setEriX(float x) { eriX = x; }
	void setEriY(float y) { eriY = y; }
	void setMaxHP(int value) { MAXHP = value; }

	void saveDataToFile();		//플레이어의 정보를 파일에 저장하는 함수입니다.
	void loadDataFromFile();	//플레이어의 정보를 파일로부터 불러오는 함수입니다.
	void addBackgroundCount(int value) { backgroundCount += value; }
	
	void initBackgroundCount() { backgroundCount = 0; }
	database();
	~database();
};

