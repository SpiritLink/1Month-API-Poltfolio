#include "stdafx.h"
#include "image.h"
#include "animation.h"

#pragma comment (lib, "msimg32.lib")
//GDI(그래픽 디바이스 인터페이스)의 컴포넌트 (GDI란 선, 상자, 텍스트 등 유저 인터페이스의 기본이 되는 윈도우 툴)


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

//빈 비트맵을 만든다
HRESULT image::init(int width, int height)
{
	//재초기화 대비...
	if (_imageInfo != NULL) release();

	//DC얻어온다
	HDC hdc = GetDC(_hWnd);

	//CreateCompatibleDC
	//비트맵 이미지를 출력하기 위해서 메모리 DC를 만들어준다.

	//CreateCompatibleBitmap
	//원본 DC와 호환되는 비트맵 생성해준다.

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY; //로드타입(빈 이미지)
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	_fileName = NULL;

	//알파블렌드 옵션
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	//알파 블렌드 사용을 위한 이미지 설정
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = width;
	_blendImage->height = height;

	//얻어온 DC해제한다
	ReleaseDC(_hWnd, hdc);

	//투명컬러 셋팅한다
	_trans = FALSE;
	_transColor = RGB(0, 0, 0);

	//리소스 이미지를 얻는데 실패하면
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;


}

//파일로부터 이미지를 읽어온다
HRESULT image::init(const char* fileName, int width, int height, BOOL trans,
	COLORREF transColor)
{
	//파일 경로가 잘못 되었으면
	if (fileName == NULL) return E_FAIL;

	//재초기화 대비...
	if (_imageInfo != NULL) release();

	//DC얻어온다
	HDC hdc = GetDC(_hWnd);

	//CreateCompatibleDC
	//비트맵 이미지를 출력하기 위해서 메모리 DC를 만들어준다.

	//CreateCompatibleBitmap
	//원본 DC와 호환되는 비트맵 생성해준다.

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE; //로드타입(빈 이미지)
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName,
		IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//파일 경로 이름 복사한다
	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy(_fileName, fileName);

	//알파블렌드 옵션
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	//알파 블렌드 사용을 위한 이미지 설정
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = width;
	_blendImage->height = height;

	//얻어온 DC해제한다
	ReleaseDC(_hWnd, hdc);

	//투명컬러 셋팅한다
	_trans = trans;
	_transColor = transColor;

	//리소스 이미지를 얻는데 실패하면
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}

//파일로부터 이미지를 읽어온다
HRESULT image::init(const char* fileName, float x, float y, int width, int height, BOOL trans,
	COLORREF transColor)
{
	//파일 경로가 잘못 되었으면
	if (fileName == NULL) return E_FAIL;

	//재초기화 대비...
	if (_imageInfo != NULL) release();

	//DC얻어온다
	HDC hdc = GetDC(_hWnd);

	//CreateCompatibleDC
	//비트맵 이미지를 출력하기 위해서 메모리 DC를 만들어준다.

	//CreateCompatibleBitmap
	//원본 DC와 호환되는 비트맵 생성해준다.

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE; //로드타입(빈 이미지)
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName,
		IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x - (width / 2);
	_imageInfo->y = y - (height / 2);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//파일 경로 이름 복사한다
	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy(_fileName, fileName);

	//알파블렌드 옵션
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	//알파 블렌드 사용을 위한 이미지 설정
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = width;
	_blendImage->height = height;

	//얻어온 DC해제한다
	ReleaseDC(_hWnd, hdc);

	//투명컬러 셋팅한다
	_trans = trans;
	_transColor = transColor;

	//리소스 이미지를 얻는데 실패하면
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}

//이미지 + 프레임 파일 초기화
HRESULT image::init(const char* fileName, float x, float y, int width, int height,
	int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	//파일 경로가 잘못 되었으면
	if (fileName == NULL) return E_FAIL;

	//재초기화 대비...
	if (_imageInfo != NULL) release();

	//DC얻어온다
	HDC hdc = GetDC(_hWnd);

	//CreateCompatibleDC
	//비트맵 이미지를 출력하기 위해서 메모리 DC를 만들어준다.

	//CreateCompatibleBitmap
	//원본 DC와 호환되는 비트맵 생성해준다.

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE; //로드타입(빈 이미지)
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

	//파일 경로 이름 복사한다
	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy(_fileName, fileName);

	//알파블렌드 옵션
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	//알파 블렌드 사용을 위한 이미지 설정
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = width;
	_blendImage->height = height;

	//얻어온 DC해제한다
	ReleaseDC(_hWnd, hdc);

	//투명컬러 셋팅한다
	_trans = trans;
	_transColor = transColor;

	//리소스 이미지를 얻는데 실패하면
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
	//파일 경로가 잘못 되었으면
	if (fileName == NULL) return E_FAIL;

	//재초기화 대비...
	if (_imageInfo != NULL) release();

	//DC얻어온다
	HDC hdc = GetDC(_hWnd);

	//CreateCompatibleDC
	//비트맵 이미지를 출력하기 위해서 메모리 DC를 만들어준다.

	//CreateCompatibleBitmap
	//원본 DC와 호환되는 비트맵 생성해준다.

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE; //로드타입(빈 이미지)
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

	//파일 경로 이름 복사한다
	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy(_fileName, fileName);

	//알파블렌드 옵션
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	//알파 블렌드 사용을 위한 이미지 설정
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = width;
	_blendImage->height = height;

	//얻어온 DC해제한다
	ReleaseDC(_hWnd, hdc);

	//투명컬러 셋팅한다
	_trans = trans;
	_transColor = transColor;

	//리소스 이미지를 얻는데 실패하면
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}

//삭제한다
void image::release()
{
	if (_imageInfo)
	{
		//이미지 삭제
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		//알파 블렌드 사용 이미지 삭제
		SelectObject(_blendImage->hMemDC, _blendImage->hOBit);
		DeleteObject(_blendImage->hBit);
		DeleteDC(_blendImage->hMemDC);

		//포인터 삭제
		SAFE_DELETE(_imageInfo);
		SAFE_DELETE(_fileName);

		//투명컬러값 초기화
		_trans = FALSE;
		_transColor = RGB(0, 0, 0);
	}
}

//투명키 셋팅한다
void image::setTransColor(BOOL trans, COLORREF transColor)
{
	_trans = trans;
	_transColor = transColor;
}


//렌더링 (화면 출력!!)
void image::render(HDC hdc)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,					//복사할 장소의 DC
			(int)_imageInfo->x,					//복사될 좌표 시작점 x
			(int)_imageInfo->y,					//복사될 좌표 시작점 y
			_imageInfo->width,		//복사될 넓이
			_imageInfo->height,		//복사될 높이
			_imageInfo->hMemDC,		//복사대상의 DC
			0,						//복사 시작지점 x
			0,						//복사 시작지점 y
			_imageInfo->width,		//복사할 영역의 넓이
			_imageInfo->height,		//복사할 영역의 높이
			_transColor);			//복사에서 제외 될 색상 값
	}
	else
	{
		//BitBlt는 DC간의 영역끼리 서로 고속복사를
		//해 주는 함수이다.
		//(CreateCompatibleDC함수로 만든 메모리 DC에 있는
		//비트맵을 화면 DC로 복사해줄때 사용.....)
		//같은 기능으로 StrechBlt가 있는데 이 함수는 
		//비트맵의 확대 및 축소가 가능하다.
		BitBlt(hdc, (int)_imageInfo->x, (int)_imageInfo->y, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void image::render(HDC hdc, int destX, int destY)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,					//복사할 장소의 DC
			destX,					//복사될 좌표 시작점 x
			destY,					//복사될 좌표 시작점 y
			_imageInfo->width,		//복사될 넓이
			_imageInfo->height,		//복사될 높이
			_imageInfo->hMemDC,		//복사대상의 DC
			0,						//복사 시작지점 x
			0,						//복사 시작지점 y
			_imageInfo->width,		//복사할 영역의 넓이
			_imageInfo->height,		//복사할 영역의 높이
			_transColor);			//복사에서 제외 될 색상 값
	}
	else
	{
		//BitBlt는 DC간의 영역끼리 서로 고속복사를
		//해 주는 함수이다.
		//(CreateCompatibleDC함수로 만든 메모리 DC에 있는
		//비트맵을 화면 DC로 복사해줄때 사용.....)
		//같은 기능으로 StrechBlt가 있는데 이 함수는 
		//비트맵의 확대 및 축소가 가능하다.
		BitBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int width, int height)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,					//복사할 장소의 DC
			destX,					//복사될 좌표 시작점 x
			destY,					//복사될 좌표 시작점 y
			width,		//복사될 넓이
			height,		//복사될 높이
			_imageInfo->hMemDC,		//복사대상의 DC
			sourX,						//복사 시작지점 x
			sourY,						//복사 시작지점 y
			width,		//복사할 영역의 넓이
			height,		//복사할 영역의 높이
			_transColor);			//복사에서 제외 될 색상 값
	}
	else
	{
		//BitBlt는 DC간의 영역끼리 서로 고속복사를
		//해 주는 함수이다.
		//(CreateCompatibleDC함수로 만든 메모리 DC에 있는
		//비트맵을 화면 DC로 복사해줄때 사용.....)
		//같은 기능으로 StrechBlt가 있는데 이 함수는 
		//비트맵의 확대 및 축소가 가능하다.
		BitBlt(hdc, destX, destY, width, height,
			_imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}
}

void image::render(HDC hdc, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,					//복사할 장소의 DC
			_imageInfo->x,					//복사될 좌표 시작점 x
			_imageInfo->y,					//복사될 좌표 시작점 y
			sourWidth,		//복사될 넓이
			sourHeight,		//복사될 높이
			_imageInfo->hMemDC,		//복사대상의 DC
			sourX,						//복사 시작지점 x
			sourY,						//복사 시작지점 y
			sourWidth,		//복사할 영역의 넓이
			sourHeight,		//복사할 영역의 높이
			_transColor);			//복사에서 제외 될 색상 값
	}
	else
	{
		//BitBlt는 DC간의 영역끼리 서로 고속복사를
		//해 주는 함수이다.
		//(CreateCompatibleDC함수로 만든 메모리 DC에 있는
		//비트맵을 화면 DC로 복사해줄때 사용.....)
		//같은 기능으로 StrechBlt가 있는데 이 함수는 
		//비트맵의 확대 및 축소가 가능하다.
		BitBlt(hdc, _imageInfo->x, _imageInfo->y, sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}
}

//루프 렌더
void image::loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	//옵셋값이 음수인 경우에는 보정을 해준다
	if (offsetX < 0) offsetX = _imageInfo->width + (offsetX%_imageInfo->width);
	if (offsetY < 0) offsetY = _imageInfo->height + (offsetY%_imageInfo->height);

	//원본 영역
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	//그려지는 영역의 DC
	RECT rcDest;

	//그려야 할 전체 영역
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		//소스 영역 높이를 계산한다
		rcSour.top = (y + offsetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		if (y + sourHeight > drawAreaH)
		{
			//넘어간 만큼 바텀 값을 올려준다
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		//그려지는 영역임
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			//소스 영역 넓이를 계산한다
			rcSour.left = (x + offsetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			if (x + sourWidth > drawAreaW)
			{
				//넘어간 만큼 라이트 값을 올려준다
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			//그려지는 영역임
			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			//그려준다
			render(hdc, rcDest.left, rcDest.top,
				rcSour.left, rcSour.top, rcSour.right - rcSour.left, rcSour.bottom - rcSour.top);
		}
	}
}

//프레임 렌더
void image::frameRender(HDC hdc, int destX, int destY)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,					//복사할 장소의 DC
			destX,					//복사될 좌표 시작점 x
			destY,					//복사될 좌표 시작점 y
			_imageInfo->frameWidth,		//복사될 넓이
			_imageInfo->frameHeight,		//복사될 높이
			_imageInfo->hMemDC,		//복사대상의 DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,						//복사 시작지점 x
			_imageInfo->currentFrameY * _imageInfo->frameHeight,						//복사 시작지점 y
			_imageInfo->frameWidth,		//복사할 영역의 넓이
			_imageInfo->frameHeight,		//복사할 영역의 높이
			_transColor);			//복사에서 제외 될 색상 값
	}
	else
	{
		//BitBlt는 DC간의 영역끼리 서로 고속복사를
		//해 주는 함수이다.
		//(CreateCompatibleDC함수로 만든 메모리 DC에 있는
		//비트맵을 화면 DC로 복사해줄때 사용.....)
		//같은 기능으로 StrechBlt가 있는데 이 함수는 
		//비트맵의 확대 및 축소가 가능하다.
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
			hdc,					//복사할 장소의 DC
			destX,					//복사될 좌표 시작점 x
			destY,					//복사될 좌표 시작점 y
			_imageInfo->frameWidth,		//복사될 넓이
			_imageInfo->frameHeight,		//복사될 높이
			_imageInfo->hMemDC,		//복사대상의 DC
			currentFrameX * _imageInfo->frameWidth,						//복사 시작지점 x
			currentFrameY * _imageInfo->frameHeight,						//복사 시작지점 y
			_imageInfo->frameWidth,		//복사할 영역의 넓이
			_imageInfo->frameHeight,		//복사할 영역의 높이
			_transColor);			//복사에서 제외 될 색상 값
	}
	else
	{
		//BitBlt는 DC간의 영역끼리 서로 고속복사를
		//해 주는 함수이다.
		//(CreateCompatibleDC함수로 만든 메모리 DC에 있는
		//비트맵을 화면 DC로 복사해줄때 사용.....)
		//같은 기능으로 StrechBlt가 있는데 이 함수는 
		//비트맵의 확대 및 축소가 가능하다.
		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC,
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight, SRCCOPY);
	}
}

//애니 렌더
void image::aniRender(HDC hdc, int destX, int destY, animation* ani)
{
	render(hdc, destX, destY, ani->getFramePos().x, ani->getFramePos().y,
		ani->getFrameWidth(), ani->getFrameHeight());
}

//알파 렌더
void image::alphaRender(HDC hdc, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		//출력해야 될 DC에 그려져 있는 내용을 blend에 그린다
		BitBlt(_blendImage->hMemDC, 0, 0, (int)_imageInfo->width,
			(int)_imageInfo->height, hdc, _imageInfo->x, _imageInfo->y, SRCCOPY);

		//출력해야 될 이미지를 blend에 그린다
		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, (int)_imageInfo->width,
			(int)_imageInfo->height, _imageInfo->hMemDC, 0, 0, (int)_imageInfo->width,
			(int)_imageInfo->height, _transColor);

		//blendDC를 출력해야 할 DC에 그린다
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
		//출력해야 될 DC에 그려져 있는 내용을 blend에 그린다
		BitBlt(_blendImage->hMemDC, 0, 0, (int)_imageInfo->width,
			(int)_imageInfo->height, hdc, destX, destY, SRCCOPY);

		//출력해야 될 이미지를 blend에 그린다
		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, (int)_imageInfo->width,
			(int)_imageInfo->height, _imageInfo->hMemDC, 0, 0, (int)_imageInfo->width,
			(int)_imageInfo->height, _transColor);

		//blendDC를 출력해야 할 DC에 그린다
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