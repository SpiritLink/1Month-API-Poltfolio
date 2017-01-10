#include "stdafx.h"
#include "image.h"
#include "animation.h"

#pragma comment (lib, "msimg32.lib")
//GDI(�׷��� ����̽� �������̽�)�� ������Ʈ (GDI�� ��, ����, �ؽ�Ʈ �� ���� �������̽��� �⺻�� �Ǵ� ������ ��)


image::image()
	:_imageInfo(NULL)
	, _fileName(NULL)
	, _trans(FALSE)
	, _transColor(RGB(0, 0, 0))
{
}


image::~image()
{
}

//�� ��Ʈ���� �����
HRESULT image::init(int width, int height)
{
	//���ʱ�ȭ ���...
	if (_imageInfo != NULL) release();

	//DC���´�
	HDC hdc = GetDC(_hWnd);

	//CreateCompatibleDC
	//��Ʈ�� �̹����� ����ϱ� ���ؼ� �޸� DC�� ������ش�.

	//CreateCompatibleBitmap
	//���� DC�� ȣȯ�Ǵ� ��Ʈ�� �������ش�.

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY; //�ε�Ÿ��(�� �̹���)
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	_fileName = NULL;

	//���ĺ��� �ɼ�
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	//���� ���� ����� ���� �̹��� ����
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = width;
	_blendImage->height = height;

	//���� DC�����Ѵ�
	ReleaseDC(_hWnd, hdc);

	//�����÷� �����Ѵ�
	_trans = FALSE;
	_transColor = RGB(0, 0, 0);

	//���ҽ� �̹����� ��µ� �����ϸ�
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;


}

//���Ϸκ��� �̹����� �о�´�
HRESULT image::init(const char* fileName, int width, int height, BOOL trans,
	COLORREF transColor)
{
	//���� ��ΰ� �߸� �Ǿ�����
	if (fileName == NULL) return E_FAIL;

	//���ʱ�ȭ ���...
	if (_imageInfo != NULL) release();

	//DC���´�
	HDC hdc = GetDC(_hWnd);

	//CreateCompatibleDC
	//��Ʈ�� �̹����� ����ϱ� ���ؼ� �޸� DC�� ������ش�.

	//CreateCompatibleBitmap
	//���� DC�� ȣȯ�Ǵ� ��Ʈ�� �������ش�.

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE; //�ε�Ÿ��(�� �̹���)
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName,
		IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//���� ��� �̸� �����Ѵ�
	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy(_fileName, fileName);

	//���ĺ��� �ɼ�
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	//���� ���� ����� ���� �̹��� ����
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = width;
	_blendImage->height = height;

	//���� DC�����Ѵ�
	ReleaseDC(_hWnd, hdc);

	//�����÷� �����Ѵ�
	_trans = trans;
	_transColor = transColor;

	//���ҽ� �̹����� ��µ� �����ϸ�
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}

//���Ϸκ��� �̹����� �о�´�
HRESULT image::init(const char* fileName, float x, float y, int width, int height, BOOL trans,
	COLORREF transColor)
{
	//���� ��ΰ� �߸� �Ǿ�����
	if (fileName == NULL) return E_FAIL;

	//���ʱ�ȭ ���...
	if (_imageInfo != NULL) release();

	//DC���´�
	HDC hdc = GetDC(_hWnd);

	//CreateCompatibleDC
	//��Ʈ�� �̹����� ����ϱ� ���ؼ� �޸� DC�� ������ش�.

	//CreateCompatibleBitmap
	//���� DC�� ȣȯ�Ǵ� ��Ʈ�� �������ش�.

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE; //�ε�Ÿ��(�� �̹���)
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName,
		IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x - (width / 2);
	_imageInfo->y = y - (height / 2);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//���� ��� �̸� �����Ѵ�
	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy(_fileName, fileName);

	//���ĺ��� �ɼ�
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	//���� ���� ����� ���� �̹��� ����
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = width;
	_blendImage->height = height;

	//���� DC�����Ѵ�
	ReleaseDC(_hWnd, hdc);

	//�����÷� �����Ѵ�
	_trans = trans;
	_transColor = transColor;

	//���ҽ� �̹����� ��µ� �����ϸ�
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}

//�̹��� + ������ ���� �ʱ�ȭ
HRESULT image::init(const char* fileName, float x, float y, int width, int height,
	int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	//���� ��ΰ� �߸� �Ǿ�����
	if (fileName == NULL) return E_FAIL;

	//���ʱ�ȭ ���...
	if (_imageInfo != NULL) release();

	//DC���´�
	HDC hdc = GetDC(_hWnd);

	//CreateCompatibleDC
	//��Ʈ�� �̹����� ����ϱ� ���ؼ� �޸� DC�� ������ش�.

	//CreateCompatibleBitmap
	//���� DC�� ȣȯ�Ǵ� ��Ʈ�� �������ش�.

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE; //�ε�Ÿ��(�� �̹���)
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName,
		IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x - (width / 2);
	_imageInfo->y = y - (height / 2);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;

	//���� ��� �̸� �����Ѵ�
	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy(_fileName, fileName);

	//���ĺ��� �ɼ�
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	//���� ���� ����� ���� �̹��� ����
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = width;
	_blendImage->height = height;

	//���� DC�����Ѵ�
	ReleaseDC(_hWnd, hdc);

	//�����÷� �����Ѵ�
	_trans = trans;
	_transColor = transColor;

	//���ҽ� �̹����� ��µ� �����ϸ�
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}

HRESULT image::init(const char* fileName, int width, int height, int frameX, int frameY,
	BOOL trans, COLORREF transColor)
{
	//���� ��ΰ� �߸� �Ǿ�����
	if (fileName == NULL) return E_FAIL;

	//���ʱ�ȭ ���...
	if (_imageInfo != NULL) release();

	//DC���´�
	HDC hdc = GetDC(_hWnd);

	//CreateCompatibleDC
	//��Ʈ�� �̹����� ����ϱ� ���ؼ� �޸� DC�� ������ش�.

	//CreateCompatibleBitmap
	//���� DC�� ȣȯ�Ǵ� ��Ʈ�� �������ش�.

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE; //�ε�Ÿ��(�� �̹���)
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName,
		IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = 0;
	_imageInfo->y = 0;
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;

	//���� ��� �̸� �����Ѵ�
	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy(_fileName, fileName);

	//���ĺ��� �ɼ�
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	//���� ���� ����� ���� �̹��� ����
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = width;
	_blendImage->height = height;

	//���� DC�����Ѵ�
	ReleaseDC(_hWnd, hdc);

	//�����÷� �����Ѵ�
	_trans = trans;
	_transColor = transColor;

	//���ҽ� �̹����� ��µ� �����ϸ�
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}

//�����Ѵ�
void image::release()
{
	if (_imageInfo)
	{
		//�̹��� ����
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		//���� ���� ��� �̹��� ����
		SelectObject(_blendImage->hMemDC, _blendImage->hOBit);
		DeleteObject(_blendImage->hBit);
		DeleteDC(_blendImage->hMemDC);

		//������ ����
		SAFE_DELETE(_imageInfo);
		SAFE_DELETE(_fileName);

		//�����÷��� �ʱ�ȭ
		_trans = FALSE;
		_transColor = RGB(0, 0, 0);
	}
}

//����Ű �����Ѵ�
void image::setTransColor(BOOL trans, COLORREF transColor)
{
	_trans = trans;
	_transColor = transColor;
}


//������ (ȭ�� ���!!)
void image::render(HDC hdc)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,					//������ ����� DC
			(int)_imageInfo->x,					//����� ��ǥ ������ x
			(int)_imageInfo->y,					//����� ��ǥ ������ y
			_imageInfo->width,		//����� ����
			_imageInfo->height,		//����� ����
			_imageInfo->hMemDC,		//�������� DC
			0,						//���� �������� x
			0,						//���� �������� y
			_imageInfo->width,		//������ ������ ����
			_imageInfo->height,		//������ ������ ����
			_transColor);			//���翡�� ���� �� ���� ��
	}
	else
	{
		//BitBlt�� DC���� �������� ���� ��Ӻ��縦
		//�� �ִ� �Լ��̴�.
		//(CreateCompatibleDC�Լ��� ���� �޸� DC�� �ִ�
		//��Ʈ���� ȭ�� DC�� �������ٶ� ���.....)
		//���� ������� StrechBlt�� �ִµ� �� �Լ��� 
		//��Ʈ���� Ȯ�� �� ��Ұ� �����ϴ�.
		BitBlt(hdc, (int)_imageInfo->x, (int)_imageInfo->y, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void image::render(HDC hdc, int destX, int destY)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,					//������ ����� DC
			destX,					//����� ��ǥ ������ x
			destY,					//����� ��ǥ ������ y
			_imageInfo->width,		//����� ����
			_imageInfo->height,		//����� ����
			_imageInfo->hMemDC,		//�������� DC
			0,						//���� �������� x
			0,						//���� �������� y
			_imageInfo->width,		//������ ������ ����
			_imageInfo->height,		//������ ������ ����
			_transColor);			//���翡�� ���� �� ���� ��
	}
	else
	{
		//BitBlt�� DC���� �������� ���� ��Ӻ��縦
		//�� �ִ� �Լ��̴�.
		//(CreateCompatibleDC�Լ��� ���� �޸� DC�� �ִ�
		//��Ʈ���� ȭ�� DC�� �������ٶ� ���.....)
		//���� ������� StrechBlt�� �ִµ� �� �Լ��� 
		//��Ʈ���� Ȯ�� �� ��Ұ� �����ϴ�.
		BitBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int width, int height)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,					//������ ����� DC
			destX,					//����� ��ǥ ������ x
			destY,					//����� ��ǥ ������ y
			width,		//����� ����
			height,		//����� ����
			_imageInfo->hMemDC,		//�������� DC
			sourX,						//���� �������� x
			sourY,						//���� �������� y
			width,		//������ ������ ����
			height,		//������ ������ ����
			_transColor);			//���翡�� ���� �� ���� ��
	}
	else
	{
		//BitBlt�� DC���� �������� ���� ��Ӻ��縦
		//�� �ִ� �Լ��̴�.
		//(CreateCompatibleDC�Լ��� ���� �޸� DC�� �ִ�
		//��Ʈ���� ȭ�� DC�� �������ٶ� ���.....)
		//���� ������� StrechBlt�� �ִµ� �� �Լ��� 
		//��Ʈ���� Ȯ�� �� ��Ұ� �����ϴ�.
		BitBlt(hdc, destX, destY, width, height,
			_imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}
}

void image::render(HDC hdc, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,					//������ ����� DC
			_imageInfo->x,					//����� ��ǥ ������ x
			_imageInfo->y,					//����� ��ǥ ������ y
			sourWidth,		//����� ����
			sourHeight,		//����� ����
			_imageInfo->hMemDC,		//�������� DC
			sourX,						//���� �������� x
			sourY,						//���� �������� y
			sourWidth,		//������ ������ ����
			sourHeight,		//������ ������ ����
			_transColor);			//���翡�� ���� �� ���� ��
	}
	else
	{
		//BitBlt�� DC���� �������� ���� ��Ӻ��縦
		//�� �ִ� �Լ��̴�.
		//(CreateCompatibleDC�Լ��� ���� �޸� DC�� �ִ�
		//��Ʈ���� ȭ�� DC�� �������ٶ� ���.....)
		//���� ������� StrechBlt�� �ִµ� �� �Լ��� 
		//��Ʈ���� Ȯ�� �� ��Ұ� �����ϴ�.
		BitBlt(hdc, _imageInfo->x, _imageInfo->y, sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}
}

//���� ����
void image::loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	//�ɼ°��� ������ ��쿡�� ������ ���ش�
	if (offsetX < 0) offsetX = _imageInfo->width + (offsetX%_imageInfo->width);
	if (offsetY < 0) offsetY = _imageInfo->height + (offsetY%_imageInfo->height);

	//���� ����
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	//�׷����� ������ DC
	RECT rcDest;

	//�׷��� �� ��ü ����
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		//�ҽ� ���� ���̸� ����Ѵ�
		rcSour.top = (y + offsetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		if (y + sourHeight > drawAreaH)
		{
			//�Ѿ ��ŭ ���� ���� �÷��ش�
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		//�׷����� ������
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			//�ҽ� ���� ���̸� ����Ѵ�
			rcSour.left = (x + offsetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			if (x + sourWidth > drawAreaW)
			{
				//�Ѿ ��ŭ ����Ʈ ���� �÷��ش�
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			//�׷����� ������
			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			//�׷��ش�
			render(hdc, rcDest.left, rcDest.top,
				rcSour.left, rcSour.top, rcSour.right - rcSour.left, rcSour.bottom - rcSour.top);
		}
	}
}

//������ ����
void image::frameRender(HDC hdc, int destX, int destY)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,					//������ ����� DC
			destX,					//����� ��ǥ ������ x
			destY,					//����� ��ǥ ������ y
			_imageInfo->frameWidth,		//����� ����
			_imageInfo->frameHeight,		//����� ����
			_imageInfo->hMemDC,		//�������� DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,						//���� �������� x
			_imageInfo->currentFrameY * _imageInfo->frameHeight,						//���� �������� y
			_imageInfo->frameWidth,		//������ ������ ����
			_imageInfo->frameHeight,		//������ ������ ����
			_transColor);			//���翡�� ���� �� ���� ��
	}
	else
	{
		//BitBlt�� DC���� �������� ���� ��Ӻ��縦
		//�� �ִ� �Լ��̴�.
		//(CreateCompatibleDC�Լ��� ���� �޸� DC�� �ִ�
		//��Ʈ���� ȭ�� DC�� �������ٶ� ���.....)
		//���� ������� StrechBlt�� �ִµ� �� �Լ��� 
		//��Ʈ���� Ȯ�� �� ��Ұ� �����ϴ�.
		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC, _imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
	}
}

void image::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,					//������ ����� DC
			destX,					//����� ��ǥ ������ x
			destY,					//����� ��ǥ ������ y
			_imageInfo->frameWidth,		//����� ����
			_imageInfo->frameHeight,		//����� ����
			_imageInfo->hMemDC,		//�������� DC
			currentFrameX * _imageInfo->frameWidth,						//���� �������� x
			currentFrameY * _imageInfo->frameHeight,						//���� �������� y
			_imageInfo->frameWidth,		//������ ������ ����
			_imageInfo->frameHeight,		//������ ������ ����
			_transColor);			//���翡�� ���� �� ���� ��
	}
	else
	{
		//BitBlt�� DC���� �������� ���� ��Ӻ��縦
		//�� �ִ� �Լ��̴�.
		//(CreateCompatibleDC�Լ��� ���� �޸� DC�� �ִ�
		//��Ʈ���� ȭ�� DC�� �������ٶ� ���.....)
		//���� ������� StrechBlt�� �ִµ� �� �Լ��� 
		//��Ʈ���� Ȯ�� �� ��Ұ� �����ϴ�.
		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC,
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight, SRCCOPY);
	}
}

//�ִ� ����
void image::aniRender(HDC hdc, int destX, int destY, animation* ani)
{
	render(hdc, destX, destY, ani->getFramePos().x, ani->getFramePos().y,
		ani->getFrameWidth(), ani->getFrameHeight());
}

//���� ����
void image::alphaRender(HDC hdc, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		//����ؾ� �� DC�� �׷��� �ִ� ������ blend�� �׸���
		BitBlt(_blendImage->hMemDC, 0, 0, (int)_imageInfo->width,
			(int)_imageInfo->height, hdc, _imageInfo->x, _imageInfo->y, SRCCOPY);

		//����ؾ� �� �̹����� blend�� �׸���
		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, (int)_imageInfo->width,
			(int)_imageInfo->height, _imageInfo->hMemDC, 0, 0, (int)_imageInfo->width,
			(int)_imageInfo->height, _transColor);

		//blendDC�� ����ؾ� �� DC�� �׸���
		AlphaBlend(hdc, (int)_imageInfo->x, (int)_imageInfo->y,
			_imageInfo->width, _imageInfo->height, _blendImage->hMemDC, 0, 0,
			_imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else
	{


		AlphaBlend(hdc, (int)_imageInfo->x, (int)_imageInfo->y,
			_imageInfo->width, _imageInfo->height, _blendImage->hMemDC, 0, 0,
			_imageInfo->width, _imageInfo->height, _blendFunc);

	}
}

void image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		//����ؾ� �� DC�� �׷��� �ִ� ������ blend�� �׸���
		BitBlt(_blendImage->hMemDC, 0, 0, (int)_imageInfo->width,
			(int)_imageInfo->height, hdc, destX, destY, SRCCOPY);

		//����ؾ� �� �̹����� blend�� �׸���
		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, (int)_imageInfo->width,
			(int)_imageInfo->height, _imageInfo->hMemDC, 0, 0, (int)_imageInfo->width,
			(int)_imageInfo->height, _transColor);

		//blendDC�� ����ؾ� �� DC�� �׸���
		AlphaBlend(hdc, destX, destY,
			_imageInfo->width, _imageInfo->height, _blendImage->hMemDC, 0, 0,
			_imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else
	{



		AlphaBlend(hdc, destX, destY,
			_imageInfo->width, _imageInfo->height, _blendImage->hMemDC, 0, 0,
			_imageInfo->width, _imageInfo->height, _blendFunc);

	}
}