#include "stdafx.h"
#include "imageManager.h"


imageManager::imageManager()
{
}


imageManager::~imageManager()
{
}

HRESULT imageManager::init()
{


	return S_OK;
}

void imageManager::release()
{
	deleteAll();
}

//키값 + 이미지
image* imageManager::addImage(string strKey, int width, int height)
{
	//추가하려는 키 값의 이미지가 존재하는지 확인한다.
	image* img = findImage(strKey);

	//추가하려는 이미지가 있으면 기존의 이미지를 리턴한다.
	if (img) return img;

	//이미지 생성한다.
	img = new image;

	//이미지 초기화하고 제대로 셋팅되지 않았으면 NULL리턴
	if (FAILED(img->init(width, height)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//생성된 이미지 map리스트에 추가한다.
	_mImageList.insert(make_pair(strKey, img));

	//생성된 이미지 리턴
	return img;

}

image* imageManager::addImage(string strKey, const char* fileName, int width, int height, BOOL trans, COLORREF transColor)
{
	//추가하려는 키 값의 이미지가 존재하는지 확인한다.
	image* img = findImage(strKey);

	//추가하려는 이미지가 있으면 기존의 이미지를 리턴한다.
	if (img) return img;

	//이미지 생성한다.
	img = new image;

	//이미지 초기화하고 제대로 셋팅되지 않았으면 NULL리턴
	if (FAILED(img->init(fileName, width, height, trans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//생성된 이미지 map리스트에 추가한다.
	_mImageList.insert(make_pair(strKey, img));

	//생성된 이미지 리턴
	return img;
}
image* imageManager::addImage(string strKey, const char* fileName, float x, float y, int width, int height, BOOL trans, COLORREF transColor)
{
	//추가하려는 키 값의 이미지가 존재하는지 확인한다.
	image* img = findImage(strKey);

	//추가하려는 이미지가 있으면 기존의 이미지를 리턴한다.
	if (img) return img;

	//이미지 생성한다.
	img = new image;

	//이미지 초기화하고 제대로 셋팅되지 않았으면 NULL리턴
	if (FAILED(img->init(fileName, x, y, width, height, trans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//생성된 이미지 map리스트에 추가한다.
	_mImageList.insert(make_pair(strKey, img));

	//생성된 이미지 리턴
	return img;
}

//키값 + 이미지 + 프레임
image* imageManager::addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	//추가하려는 키 값의 이미지가 존재하는지 확인한다.
	image* img = findImage(strKey);

	//추가하려는 이미지가 있으면 기존의 이미지를 리턴한다.
	if (img) return img;

	//이미지 생성한다.
	img = new image;

	//이미지 초기화하고 제대로 셋팅되지 않았으면 NULL리턴
	if (FAILED(img->init(fileName, x, y, width, height, frameX, frameY, trans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//생성된 이미지 map리스트에 추가한다.
	_mImageList.insert(make_pair(strKey, img));

	//생성된 이미지 리턴
	return img;
}

image* imageManager::addFrameImage(string strKey, const char* fileName,
	int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	//추가하려는 키 값의 이미지가 존재하는지 확인한다.
	image* img = findImage(strKey);

	//추가하려는 이미지가 있으면 기존의 이미지를 리턴한다.
	if (img) return img;

	//이미지 생성한다.
	img = new image;

	//이미지 초기화하고 제대로 셋팅되지 않았으면 NULL리턴
	if (FAILED(img->init(fileName, width, height, frameX, frameY, trans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//생성된 이미지 map리스트에 추가한다.
	_mImageList.insert(make_pair(strKey, img));

	//생성된 이미지 리턴
	return img;
}

//이미지 찾는다
image* imageManager::findImage(string strKey)
{
	//해당 키를 검색한다
	mapImageIter key = _mImageList.find(strKey);

	//해당 키를 찾았으면
	if (key != _mImageList.end())
	{
		return key->second;
	}

	return NULL;
}

//이미지 삭제
BOOL imageManager::deleteImage(string strKey)
{
	//해당 키를 검색한다
	mapImageIter key = _mImageList.find(strKey);

	//해당 키를 찾았으면
	if (key != _mImageList.end())
	{
		//이미지 릴리즈
		key->second->release();

		//메모리 해제
		SAFE_DELETE(key->second);

		_mImageList.erase(key);

		return true;
	}

	return false;
}

//전체 이미지 삭제
BOOL imageManager::deleteAll()
{
	mapImageIter iter = _mImageList.begin();

	while (iter != _mImageList.end())
	{
		if (iter->second != NULL)
		{
			iter->second->release();
			SAFE_DELETE(iter->second);
			iter = _mImageList.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	_mImageList.clear();

	return true;
}

//렌더링
void imageManager::render(string strKey, HDC hdc)
{
	image* img = findImage(strKey);
	if (img) img->render(hdc);
}

void imageManager::render(string strKey, HDC hdc, int destX, int destY)
{
	image* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY);
}

void imageManager::render(string strKey, HDC hdc, int sourX, int sourY, int sourWidth, int sourHeight)
{
	image* img = findImage(strKey);
	if (img) img->render(hdc, sourX, sourY, sourWidth, sourHeight);
}

void imageManager::render(string strKey, HDC hdc, int destX, int destY,
	int sourX, int sourY, int width, int height)
{
	image* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY, sourX, sourY, width, height);
}

void imageManager::alphaRender(string strKey, HDC hdc, BYTE alpha)
{
	image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, alpha);
}

//프레임 렌더
void imageManager::frameRender(string strKey, HDC hdc, int destX, int destY)
{
	image* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY);
}

void imageManager::frameRender(string strKey, HDC hdc, int destX, int destY, int frameX, int frameY)
{
	image* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY, frameX, frameY);
}

void imageManager::alphaFrameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
{
	image* img = findImage(strKey);
	if (img) img->alphaFrameRender(hdc, destX, destY, currentFrameX, currentFrameY, alpha);
}

void imageManager::loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	image* img = findImage(strKey);
	if (img) img->loopRender(hdc, drawArea, offsetX, offsetY);
}
