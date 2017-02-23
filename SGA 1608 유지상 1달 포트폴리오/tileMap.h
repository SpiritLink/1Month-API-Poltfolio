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

	int playerYTileNumber;		//���� �÷��̾��� YŸ�� ��ġ�� ����, ����� y�࿡ ��ȭ�� �ݴϴ�.
	int beforePlayerYTileNumber;//��� �������� ���Ÿ� ���� ����
	int valueX;					//����� �����̱� ���� �ʿ��� ����
	int valueY;					//����� �����̱� ���� �ʿ��� ����
	int skyX;					//�ϴ��� �����̱� ���� �ʿ��� ���� (�÷��̾ �������� �ʾƵ� ����� �������� �Ѵ�.)
	int correctionY;			//ī�޶� �����ӽ� Y�� ������ �ֱ����� ����
public:
	virtual HRESULT init(const char* fileName);
	virtual void release();
	virtual void update();
	virtual void render();

	void moveTileX(int value);	//Ÿ���� X��ǥ�� �Ķ���͸�ŭ �߰�
	void moveTileY(int value);	//Ÿ���� Y��ǥ�� �Ķ���͸�ŭ �߰�
	void miniMapRender();

	int getTileObjX(int tileNum) {	return _tiles[tileNum].objFrameX;	}	//Ÿ���� ������Ʈ X ���� ��ȯ
	int getTileObjY(int tileNum) {	return _tiles[tileNum].objFrameY;	}	//Ÿ���� ������Ʈ Y ���� ��ȯ

	tagTile* getTiles() { return _tiles; }									//Ÿ�ϸ��� ������ ��ȯ�մϴ�. (�������)

	tileMap();
	virtual ~tileMap();
};