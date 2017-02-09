#pragma once
#include "gameNode.h"

class tileMap : public gameNode
{
private:
	tagTile _tiles[TILEX * TILEY];
	image* _miniMapIMG;
	image* _miniRedTile;

	image* _BgSky;
	image* _BgMt1;
	image* _BgMt2;
	image* _BgMt3;

	RECT _Sky;		//�ϴ��� ǥ���� ����
	RECT _Ground;	//������ ǥ���� ����

	int playerYTileNumber;	//���� �÷��̾��� YŸ�� ��ġ�� ����, ����� y�࿡ ��ȭ�� �ݴϴ�.
	int valueX;		//����� �����̱� ���� �ʿ��� ����
	int valueY;		//����� �����̱� ���� �ʿ��� ����
public:
	virtual HRESULT init(const char* fileName);
	virtual void release();
	virtual void update();
	virtual void render();

	void moveTileX(int value);
	void moveTileY(int value);
	void miniMapRender();

	int getTileObjX(int tileNum) {	return _tiles[tileNum].objFrameX;	}
	int getTileObjY(int tileNum) {	return _tiles[tileNum].objFrameY;	}

	tagTile* getTiles() { return _tiles; }

	tileMap();
	virtual ~tileMap();
};