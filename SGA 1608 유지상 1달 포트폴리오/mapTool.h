#pragma once
#include "gameNode.h"

class mapTool : public gameNode
{
private:
	image* _whiteBackground;
	image* _sampleTile;
	image* _miniMapIMG;

	RECT _moveRight;
	RECT _moveLeft;
	RECT _moveUp;
	RECT _moveDown;

	RECT _saveTown;
	RECT _saveField1;
	RECT _saveField2;
	RECT _saveBoss;

	RECT _loadTown;
	RECT _loadField1;
	RECT _loadField2;
	RECT _loadBoss;

	HWND _btnTerrainDraw;
	HWND _btnObjDraw;
	HWND _btnTerrainEraser;
	HWND _btnObjEraser;

	tagCurrentTile _currentTile;
	tagTile _tiles[TILEX * TILEY];
	tagSampleTile _sampleTiles[SAMPLETILEX * SAMPLETILEY];
	int _ctrlSelect;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void mouseClick();	//마우스 클릭을 감지하는 함수
	void setup();		//버튼위치 및 크기 , 영역 초기화 함수
	void lineRender();	//선을 그리는 함수 (좀더 쉽게 영역을 구분하기 위해)

	void moveMaptoolX(int tileNum);	//맵 RECT들의 X좌표 이동
	void moveMapToolY(int tileNum);	//맵 RECT들의 Y좌표 이동
	void defaultMapRect();			//맵 RECT위치 초기화 함수
	OBJECT objSelect(int frameX, int frameY);		//OBJ의 종류를 설정하는 함수
	TERRAIN terrainSelect(int frameX, int frameY);	//TERRAIN의 종류를 설정하는 함수
	void load(const char * fileName);				//파일로부터 데이터를 읽어오는 함수
	void save(const char * fileName);				//데이터를 파일로 저장하는 함수

	void changeOBJType();	//기존의 오브젝트 종류를 변경하기 위한 설정

	mapTool();
	virtual ~mapTool();
};

