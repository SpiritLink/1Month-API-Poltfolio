#pragma once

inline POINT PointMake(int x, int y)
{
	POINT pt = { x, y };
	return pt;
}

inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x, y, x + width, y + height };
	return rc;
}

inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2) };
	return rc;
}

//그림그리는데 필요한 함수
inline void LineMake(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
}

inline void LinesMake(HDC hdc, vector<POINT> vPt)
{
	vector<POINT>::iterator viPoint;

	int i = 0;

	for (viPoint = vPt.begin(); viPoint != vPt.end(); ++viPoint)
	{
		if (i == 0) MoveToEx(hdc, viPoint->x, viPoint->y, NULL);
		else LineTo(hdc, viPoint->x, viPoint->y);
	}

	vPt.clear();
}

inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

inline void RectangleMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));
}

inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));
}

//충돌영역리사이징
inline RECT CollisionAreaResizing(RECT &rcDest, int width, int height)
{
	RECT rc = { (rcDest.left + rcDest.right) / 2 - width / 2,
		(rcDest.top + rcDest.bottom) / 2 - height / 2,
		(rcDest.left + rcDest.right) / 2 + width / 2,
		(rcDest.top + rcDest.bottom) / 2 + height / 2 };
	return rc;
}