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

	RECT _Sky;		//하늘을 표시할 영역
	RECT _Ground;	//대지를 표시할 영역

	int playerYTileNumber;	//현재 플레이어의 Y타일 위치를 저장, 배경의 y축에 변화를 줍니다.
	int valueX;		//배경을 움직이기 위해 필요한 변수
	int valueY;		//배경을 움직이기 위해 필요한 변수
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