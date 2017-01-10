#pragma once

class animation;

class image
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0,	//리소스로부터 이미지 로딩
		LOAD_FILE,			//파일로부터 이미지 로딩
		LOAD_EMPTY,			//아무것도 없는 이미지 생성
		LOAD_END
	};

	typedef struct tagImageInfo
	{
		DWORD	resID;
		HDC		hMemDC;
		HBITMAP hBit;
		HBITMAP hOBit;
		float	x;
		float	y;
		int		width;
		int		height;
		int		currentFrameX;
		int		currentFrameY;
		int		maxFrameX;
		int		maxFrameY;
		int		frameWidth;
		int		frameHeight;
		BYTE	loadType;

		tagImageInfo()
		{
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			x = 0;
			y = 0;
			width = 0;
			height = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			loadType = LOAD_RESOURCE;
		}
	} IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO	_imageInfo;		//이미지 정보
	CHAR*			_fileName;		//이미지 파일 경로 명

	BOOL			_trans;			//투명 배경 있냐?
	COLORREF		_transColor;	//투명 컬러키

	BLENDFUNCTION	_blendFunc;		//알파블렌드 정보
	LPIMAGE_INFO	_blendImage;	//알파블렌드를 사용하기 위한 이미지

public:
	//빈 비트맵을 만든다
	HRESULT init(int width, int height);

	//파일로부터 이미지를 읽어온다
	HRESULT init(const char* fileName, int width, int height, BOOL trans = FALSE,
		COLORREF transColor = RGB(0, 0, 0));

	HRESULT init(const char* fileName, float x, float y, int width, int height, BOOL trans = FALSE,
		COLORREF transColor = RGB(0, 0, 0));

	//이미지 + 프레임 파일 초기화
	HRESULT init(const char* fileName, float x, float y, int width, int height,
		int frameX, int frameY, BOOL trans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	HRESULT init(const char* fileName, int width, int height, int frameX, int frameY,
		BOOL trans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	//삭제한다
	void release();

	//투명키 셋팅한다
	void setTransColor(BOOL trans, COLORREF transColor);

	//렌더링 (화면 출력!!)
	void render(HDC hdc);
	void render(HDC hdc, int destX, int destY);
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int width, int height);
	void render(HDC hdc, int sourX, int sourY, int sourWidth, int sourHeight);

	//루프 렌더
	void loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);

	//프레임 렌더
	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	//애니 렌더
	void aniRender(HDC hdc, int destX, int destY, animation* ani);

	//알파 렌더
	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);


	//메모리 DC얻어온다
	inline HDC getMemDC() { return _imageInfo->hMemDC; }

	//좌표x
	inline void setX(float x) { _imageInfo->x = x; }
	inline float getX() { return _imageInfo->x; }

	//좌표y
	inline void setY(float y) { _imageInfo->y = y; }
	inline float getY() { return _imageInfo->y; }

	//가로 해상도
	inline int getWidth() { return _imageInfo->width; }

	//세로 해상도
	inline int getHeight() { return _imageInfo->height; }

	inline void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX)
		{
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}
	}

	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY)
		{
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}
	}

	inline int getFrameX() { return _imageInfo->currentFrameX; }
	inline int getFrameY() { return _imageInfo->currentFrameY; }

	inline int getMaxFrameX() { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY() { return _imageInfo->maxFrameY; }

	inline int getFrameWidth() { return _imageInfo->frameWidth; }
	inline int getFrameHeight() { return _imageInfo->frameHeight; }


	image();
	~image();
};

