// SGA 1608 ������ 1�� ��Ʈ������.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "SGA 1608 ������ 1�� ��Ʈ������.h"
#include "gameStudy.h"
#include "timeManager.h"

#define MAX_LOADSTRING 100

// ���� ����:
HINSTANCE	_hInstance;								// ���� �ν��Ͻ��Դϴ�.
HWND		_hWnd;
TCHAR szTitle[MAX_LOADSTRING];					// ���� ǥ���� �ؽ�Ʈ�Դϴ�.
TCHAR szWindowClass[MAX_LOADSTRING];			// �⺻ â Ŭ���� �̸��Դϴ�.

POINT _ptMouse = { 0, 0 };
gameStudy _gs;
BOOL	_leftButtonDown = false;
int		_saveCount = -1;

// �� �ڵ� ��⿡ ��� �ִ� �Լ��� ������ �����Դϴ�.
ATOM				MyRegisterClass(HINSTANCE hInstance);	//â Ŭ������ ����մϴ�.
BOOL				InitInstance(HINSTANCE, int);			//â�� ����ϴ�.
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);	//â�� �޽����� ó���մϴ�.
void setWindowSize(int x, int y, int width, int height);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{

	// TODO: ���⿡ �ڵ带 �Է��մϴ�.
	MSG msg;				//������ �޽����� ���� ����ü
	HACCEL hAccelTable;

	// ���� ���ڿ��� �ʱ�ȭ�մϴ�.
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_SGA16081, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ���� ���α׷� �ʱ�ȭ�� �����մϴ�.
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SGA16081));

	//���� ���͵� �ʱ�ȭ
	if (FAILED(_gs.init()))
	{
		//���н� �ٷ� �����Ѵ�
		return 0;
	}

	// �⺻ �޽��� �����Դϴ�.

	//���ӿ�
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
			TIMEMANAGER->update(60); //�ʴ� 60���������� ����
			_gs.update();
			_gs.render();
		}
	}


	////�Ϲ� ���α׷���
	//while (GetMessage(&msg, NULL, 0, 0))
	//{
	//	if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
	//	{
	//		TranslateMessage(&msg); //Ű���� �Է� �޽��� ó�� ���
	//		DispatchMessage(&msg);	//������ ������� �޽��� ó��
	//	}
	//}

	return (int)msg.wParam;

}



//
//  �Լ�: MyRegisterClass()
//
//  ����: â Ŭ������ ����մϴ�.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;									//������ ��Ÿ��
	wcex.lpfnWndProc = WndProc;													//���ν��� �Լ�(�޽��� ó�� �Լ�)
	wcex.cbClsExtra = 0;														//Ŭ���� ������ �޸�
	wcex.cbWndExtra = 0;														//������ ������ �޸�
	wcex.hInstance = hInstance;												//������ �ν��Ͻ�
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SGA16081));	//������
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);								//Ŀ��
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);									//��׶���
	wcex.lpszMenuName = NULL;						//Ŭ���� �޴�
	wcex.lpszClassName = WINNAME;											//Ŭ���� �̸�
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	//������ ������ ���
	return RegisterClassEx(&wcex);
}

//
//   �Լ�: InitInstance(HINSTANCE, int)
//
//   ����: �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
//
//   ����:
//
//        �� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ�
//        �� ���α׷� â�� ���� ���� ǥ���մϴ�.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	_hInstance = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

	_hWnd = CreateWindow(
		WINNAME,		//������ Ŭ���� �̸�
		WINNAME,			//������ Ÿ��Ʋ�ٿ� �̸�
		WINSTYLE,	//������ ��Ÿ��
		WINSTARTX,				//������ â ���� x��ǥ
		WINSTARTY,					//������ â ���� y��ǥ
		WINSIZEX,					//������ â ����ũ��
		WINSIZEY,					//������ â ����ũ��
		NULL,				//�θ� ������ ����
		NULL,				//�޴� �ڵ�
		hInstance,			//�ν��Ͻ� ������ ����
		NULL
	);

	if (!_hWnd)
	{
		return FALSE;
	}

	//������ ������ �����۾�
	setWindowSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);

	//ȭ�鿡 ������ �����ش�
	ShowWindow(_hWnd, nCmdShow);
	//UpdateWindow(_hWnd);

	return TRUE;
}

//
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����:  �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND	- ���� ���α׷� �޴��� ó���մϴ�.
//  WM_PAINT	- �� â�� �׸��ϴ�.
//  WM_DESTROY	- ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
//
//
//hWnd : ��� �����쿡�� �߻��� �޽������� �����Ѵ�
//message : �޽��� ���� ��ȣ
//wParam : unsigned int�� ���콺 ��ư ����, Ű����Ű �Ǵ� ����Ű ���¸� �����Ѵ�
//lParam : ���콺 Ŭ�� ��ǥ ����
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

	//false�� �޴� �ִ��� �������� ���� Ȯ��
	AdjustWindowRect(&rc, WINSTYLE, false);
	SetWindowPos(_hWnd, NULL, x, y, rc.right - rc.left, rc.bottom - rc.top,
		SWP_NOZORDER | SWP_NOMOVE);
}



