// SGA 1608 유지상 1달 포트폴리오.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "SGA 1608 유지상 1달 포트폴리오.h"
#include "gameStudy.h"
#include "timeManager.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE	_hInstance;								// 현재 인스턴스입니다.
HWND		_hWnd;
TCHAR szTitle[MAX_LOADSTRING];					// 제목 표시줄 텍스트입니다.
TCHAR szWindowClass[MAX_LOADSTRING];			// 기본 창 클래스 이름입니다.

POINT _ptMouse = { 0, 0 };
gameStudy _gs;
BOOL	_leftButtonDown = false;
int		_saveCount = -1;

// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM				MyRegisterClass(HINSTANCE hInstance);	//창 클래스를 등록합니다.
BOOL				InitInstance(HINSTANCE, int);			//창을 만듭니다.
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);	//창의 메시지를 처리합니다.
void setWindowSize(int x, int y, int width, int height);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{

	// TODO: 여기에 코드를 입력합니다.
	MSG msg;				//윈도우 메시지를 받을 구조체
	HACCEL hAccelTable;

	// 전역 문자열을 초기화합니다.
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_SGA16081, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 응용 프로그램 초기화를 수행합니다.
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SGA16081));

	//게임 스터디 초기화
	if (FAILED(_gs.init()))
	{
		//실패시 바로 종료한다
		return 0;
	}

	// 기본 메시지 루프입니다.

	//게임용
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			TIMEMANAGER->update(60); //초당 60프레임으로 고정
			_gs.update();
			_gs.render();
		}
	}


	////일반 프로그램용
	//while (GetMessage(&msg, NULL, 0, 0))
	//{
	//	if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
	//	{
	//		TranslateMessage(&msg); //키보드 입력 메시지 처리 담당
	//		DispatchMessage(&msg);	//실제로 윈도우로 메시지 처리
	//	}
	//}

	return (int)msg.wParam;

}



//
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;									//윈도우 스타일
	wcex.lpfnWndProc = WndProc;													//프로시져 함수(메시지 처리 함수)
	wcex.cbClsExtra = 0;														//클래스 여분의 메모리
	wcex.cbWndExtra = 0;														//윈도우 여분의 메모리
	wcex.hInstance = hInstance;												//윈도우 인스턴스
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SGA16081));	//아이콘
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);								//커서
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);									//백그라운드
	wcex.lpszMenuName = NULL;						//클래스 메뉴
	wcex.lpszClassName = WINNAME;											//클래스 이름
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	//윈도우 정보를 등록
	return RegisterClassEx(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	_hInstance = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	_hWnd = CreateWindow(
		WINNAME,		//윈도우 클래스 이름
		WINNAME,			//윈도우 타이틀바에 이름
		WINSTYLE,	//윈도우 스타일
		WINSTARTX,				//윈도우 창 시작 x좌표
		WINSTARTY,					//윈도우 창 시작 y좌표
		WINSIZEX,					//윈도우 창 가로크기
		WINSIZEY,					//윈도우 창 세로크기
		NULL,				//부모 윈도우 유무
		NULL,				//메뉴 핸들
		hInstance,			//인스턴스 윈도우 지정
		NULL
	);

	if (!_hWnd)
	{
		return FALSE;
	}

	//윈도우 사이즈 보정작업
	setWindowSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);

	//화면에 윈도우 보여준다
	ShowWindow(_hWnd, nCmdShow);
	//UpdateWindow(_hWnd);

	return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적:  주 창의 메시지를 처리합니다.
//
//  WM_COMMAND	- 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT	- 주 창을 그립니다.
//  WM_DESTROY	- 종료 메시지를 게시하고 반환합니다.
//
//
//hWnd : 어느 윈도우에서 발생한 메시지인지 구분한다
//message : 메시지 구분 번호
//wParam : unsigned int형 마우스 버튼 상태, 키보드키 또는 조합키 상태를 전달한다
//lParam : 마우스 클릭 좌표 전달
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return _gs.MainProc(hWnd, message, wParam, lParam);

}

void setWindowSize(int x, int y, int width, int height)
{
	RECT rc;
	rc.left = 0;
	rc.top = 0;
	rc.right = width;
	rc.bottom = height;

	//false는 메뉴 있는지 없는지의 여부 확인
	AdjustWindowRect(&rc, WINSTYLE, false);
	SetWindowPos(_hWnd, NULL, x, y, rc.right - rc.left, rc.bottom - rc.top,
		SWP_NOZORDER | SWP_NOMOVE);
}



