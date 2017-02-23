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

	void mouseClick();	//���콺 Ŭ���� �����ϴ� �Լ�
	void setup();		//��ư��ġ �� ũ�� , ���� �ʱ�ȭ �Լ�
	void lineRender();	//���� �׸��� �Լ� (���� ���� ������ �����ϱ� ����)

	void moveMaptoolX(int tileNum);	//�� RECT���� X��ǥ �̵�
	void moveMapToolY(int tileNum);	//�� RECT���� Y��ǥ �̵�
	void defaultMapRect();			//�� RECT��ġ �ʱ�ȭ �Լ�
	OBJECT objSelect(int frameX, int frameY);		//OBJ�� ������ �����ϴ� �Լ�
	TERRAIN terrainSelect(int frameX, int frameY);	//TERRAIN�� ������ �����ϴ� �Լ�
	void load(const char * fileName);				//���Ϸκ��� �����͸� �о���� �Լ�
	void save(const char * fileName);				//�����͸� ���Ϸ� �����ϴ� �Լ�

	void changeOBJType();	//������ ������Ʈ ������ �����ϱ� ���� ����

	mapTool();
	virtual ~mapTool();
};

