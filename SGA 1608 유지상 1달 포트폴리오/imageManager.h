#pragma once

#include "singletonbase.h"
#include "image.h"

class imageManager : public singletonBase<imageManager>
{
public:
	typedef map<string, image*> mapImageList;
	typedef map<string, image*>::iterator mapImageIter;

private:
	mapImageList _mImageList;

public:
	HRESULT init();
	void release();

	//Ű�� + �̹���
	image* addImage(string strKey, int width, int height);
	image* addImage(string strKey, const char* fileName, int width, int height, BOOL trans = false, COLORREF transColor = RGB(0, 0, 0));
	image* addImage(string strKey, const char* fileName, float x, float y, int width, int height, BOOL trans = false, COLORREF transColor = RGB(0, 0, 0));

	//Ű�� + �̹��� + ������
	image* addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL trans = false, COLORREF transColor = RGB(0, 0, 0));

	image* addFrameImage(string strKey, const char* fileName,
		int width, int height, int frameX, int frameY, BOOL trans = false, COLORREF transColor = RGB(0, 0, 0));

	//�̹��� ã�´�
	image* findImage(string strKey);

	//�̹��� ����
	BOOL deleteImage(string strKey);

	//��ü �̹��� ����
	BOOL deleteAll();

	//������
	void render(string strKey, HDC hdc);
	void render(string strKey, HDC hdc, int destX, int destY);
	void render(string strKey, HDC hdc, int sourX, int sourY, int sourWidth, int sourHeight);
	void render(string strKey, HDC hdc, int destX, int destY,
		int sourX, int sourY, int width, int height);

	//������ ����
	void frameRender(string strKey, HDC hdc, int destX, int destY);
	void frameRender(string strKey, HDC hdc, int destX, int destY, int frameX, int frameY);

	void loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);


	imageManager();
	~imageManager();
};

