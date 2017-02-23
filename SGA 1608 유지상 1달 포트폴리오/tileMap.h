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

	int playerYTileNumber;		//현재 플레이어의 Y타일 위치를 저장, 배경의 y축에 변화를 줍니다.
	int beforePlayerYTileNumber;//배경 떨림현상 제거를 위한 변수
	int valueX;					//배경을 움직이기 위해 필요한 변수
	int valueY;					//배경을 움직이기 위해 필요한 변수
	int skyX;					//하늘을 움직이기 위해 필요한 변수 (플레이어가 움직이지 않아도 배경은 움직여야 한다.)
	int correctionY;			//카메라 움직임시 Y축 보정을 주기위한 변수
public:
	virtual HRESULT init(const char* fileName);
	virtual void release();
	virtual void update();
	virtual void render();

	void moveTileX(int value);	//타일의 X좌표를 파라미터만큼 추가
	void moveTileY(int value);	//타일의 Y좌표를 파라미터만큼 추가
	void miniMapRender();

	int getTileObjX(int tileNum) {	return _tiles[tileNum].objFrameX;	}	//타일의 오브젝트 X 종류 반환
	int getTileObjY(int tileNum) {	return _tiles[tileNum].objFrameY;	}	//타일의 오브젝트 Y 종류 반환

	tagTile* getTiles() { return _tiles; }									//타일맵의 정보를 반환합니다. (모든정보)

	tileMap();
	virtual ~tileMap();
};