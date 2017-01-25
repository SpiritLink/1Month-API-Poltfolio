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

//Ű�� + �̹���
image* imageManager::addImage(string strKey, int width, int height)
{
	//�߰��Ϸ��� Ű ���� �̹����� �����ϴ��� Ȯ���Ѵ�.
	image* img = findImage(strKey);

	//�߰��Ϸ��� �̹����� ������ ������ �̹����� �����Ѵ�.
	if (img) return img;

	//�̹��� �����Ѵ�.
	img = new image;

	//�̹��� �ʱ�ȭ�ϰ� ����� ���õ��� �ʾ����� NULL����
	if (FAILED(img->init(width, height)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//������ �̹��� map����Ʈ�� �߰��Ѵ�.
	_mImageList.insert(make_pair(strKey, img));

	//������ �̹��� ����
	return img;

}

image* imageManager::addImage(string strKey, const char* fileName, int width, int height, BOOL trans, COLORREF transColor)
{
	//�߰��Ϸ��� Ű ���� �̹����� �����ϴ��� Ȯ���Ѵ�.
	image* img = findImage(strKey);

	//�߰��Ϸ��� �̹����� ������ ������ �̹����� �����Ѵ�.
	if (img) return img;

	//�̹��� �����Ѵ�.
	img = new image;

	//�̹��� �ʱ�ȭ�ϰ� ����� ���õ��� �ʾ����� NULL����
	if (FAILED(img->init(fileName, width, height, trans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//������ �̹��� map����Ʈ�� �߰��Ѵ�.
	_mImageList.insert(make_pair(strKey, img));

	//������ �̹��� ����
	return img;
}
image* imageManager::addImage(string strKey, const char* fileName, float x, float y, int width, int height, BOOL trans, COLORREF transColor)
{
	//�߰��Ϸ��� Ű ���� �̹����� �����ϴ��� Ȯ���Ѵ�.
	image* img = findImage(strKey);

	//�߰��Ϸ��� �̹����� ������ ������ �̹����� �����Ѵ�.
	if (img) return img;

	//�̹��� �����Ѵ�.
	img = new image;

	//�̹��� �ʱ�ȭ�ϰ� ����� ���õ��� �ʾ����� NULL����
	if (FAILED(img->init(fileName, x, y, width, height, trans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//������ �̹��� map����Ʈ�� �߰��Ѵ�.
	_mImageList.insert(make_pair(strKey, img));

	//������ �̹��� ����
	return img;
}

//Ű�� + �̹��� + ������
image* imageManager::addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	//�߰��Ϸ��� Ű ���� �̹����� �����ϴ��� Ȯ���Ѵ�.
	image* img = findImage(strKey);

	//�߰��Ϸ��� �̹����� ������ ������ �̹����� �����Ѵ�.
	if (img) return img;

	//�̹��� �����Ѵ�.
	img = new image;

	//�̹��� �ʱ�ȭ�ϰ� ����� ���õ��� �ʾ����� NULL����
	if (FAILED(img->init(fileName, x, y, width, height, frameX, frameY, trans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//������ �̹��� map����Ʈ�� �߰��Ѵ�.
	_mImageList.insert(make_pair(strKey, img));

	//������ �̹��� ����
	return img;
}

image* imageManager::addFrameImage(string strKey, const char* fileName,
	int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	//�߰��Ϸ��� Ű ���� �̹����� �����ϴ��� Ȯ���Ѵ�.
	image* img = findImage(strKey);

	//�߰��Ϸ��� �̹����� ������ ������ �̹����� �����Ѵ�.
	if (img) return img;

	//�̹��� �����Ѵ�.
	img = new image;

	//�̹��� �ʱ�ȭ�ϰ� ����� ���õ��� �ʾ����� NULL����
	if (FAILED(img->init(fileName, width, height, frameX, frameY, trans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//������ �̹��� map����Ʈ�� �߰��Ѵ�.
	_mImageList.insert(make_pair(strKey, img));

	//������ �̹��� ����
	return img;
}

//�̹��� ã�´�
image* imageManager::findImage(string strKey)
{
	//�ش� Ű�� �˻��Ѵ�
	mapImageIter key = _mImageList.find(strKey);

	//�ش� Ű�� ã������
	if (key != _mImageList.end())
	{
		return key->second;
	}

	return NULL;
}

//�̹��� ����
BOOL imageManager::deleteImage(string strKey)
{
	//�ش� Ű�� �˻��Ѵ�
	mapImageIter key = _mImageList.find(strKey);

	//�ش� Ű�� ã������
	if (key != _mImageList.end())
	{
		//�̹��� ������
		key->second->release();

		//�޸� ����
		SAFE_DELETE(key->second);

		_mImageList.erase(key);

		return true;
	}

	return false;
}

//��ü �̹��� ����
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

//������
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

//������ ����
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
