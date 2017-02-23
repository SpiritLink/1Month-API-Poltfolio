#pragma once

#include "item.h"
#include "tileMap.h"

class objectManager : public gameNode
{
private:
	vector<item*> _vItem;				//�������� ������ ����
	vector<item*>::iterator _viItem;	//�������� ã�� ���ͷ�����
	tileMap* _tileMap;					//Ÿ�ϸ� (��ǥ�� �ش� �������� ��ġ�ϱ� ���� �ʿ��մϴ�)
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setTileMapMemoryAddress(tileMap* TM) { _tileMap = TM; }	//Ÿ�ϸ��� �޸� �ּҸ� �����մϴ�.
	void setHeart(float x, float y);								//ü�� ȸ���������� ��ġ�մϴ�.
	void setShuriken(float x, float y);								//������ ������ ��ġ
	void setSavebell(int tileNum);									//���� ��� ��ġ

	void addItemX(int value);										//��� �������� X��ǥ �߰�
	void addItemY(int value);										//��� �������� Y��ǥ �߰�

	vector<item*> getItemVector() { return _vItem; }				//������ ���͸� ��ȯ�ϴ� �Լ�

	objectManager();
	~objectManager();
};

