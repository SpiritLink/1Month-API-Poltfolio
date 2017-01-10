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

	//키값 + 이미지
	image* addImage(string strKey, int width, int height);
	image* addImage(string strKey, const char* fileName, int width, int height, BOOL trans = false, COLORREF transColor = RGB(0, 0, 0));
	image* addImage(string strKey, const char* fileName, float x, float y, int width, int height, BOOL trans = false, COLORREF transColor = RGB(0, 0, 0));

	//키값 + 이미지 + 프레임
	image* addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL trans = false, COLORREF transColor = RGB(0, 0, 0));

	image* addFrameImage(string strKey, const char* fileName,
		int width, int height, int frameX, int frameY, BOOL trans = false, COLORREF transColor = RGB(0, 0, 0));

	//이미지 찾는다
	image* findImage(string strKey);

	//이미지 삭제
	BOOL deleteImage(string strKey);

	//전체 이미지 삭제
	BOOL deleteAll();

	//렌더링
	void render(string strKey, HDC hdc);
	void render(string strKey, HDC hdc, int destX, int destY);
	void render(string strKey, HDC hdc, int sourX, int sourY, int sourWidth, int sourHeight);
	void render(string strKey, HDC hdc, int destX, int destY,
		int sourX, int sourY, int width, int height);

	//프레임 렌더
	void frameRender(string strKey, HDC hdc, int destX, int destY);
	void frameRender(string strKey, HDC hdc, int destX, int destY, int frameX, int frameY);

	void loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);


	imageManager();
	~imageManager();
};

