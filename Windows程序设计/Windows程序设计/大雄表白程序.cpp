#include <windows.h>
#define ID_TIMER 1

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	static TCHAR	szAppName[] = TEXT("p281在状态报告上使用计时器");
	HWND			hwnd;
	int				cxWindow = 0, cyWindow = 0;
	MSG				msg;
	WNDCLASS		wndclass;

	wndclass.cbClsExtra		= 0;
	wndclass.cbWndExtra		= 0;
	wndclass.hbrBackground		= (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.hCursor			= LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon				= LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hInstance			= hInstance;
	wndclass.lpfnWndProc		= WndProc;
	wndclass.lpszClassName		= szAppName;
	wndclass.lpszMenuName		= NULL;
	wndclass.style				= CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("This program requires Windows NT!"), szAppName, MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(szAppName, szAppName, 
						WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_BORDER/*固定大小的窗口*/,
						0, 0, cxWindow, cyWindow,
						NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

void DrawILoveU(HWND, const POINT *);

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HDC			hdcScreen;
	HDC					hdc;
	PAINTSTRUCT			ps;
	RECT				rc;
	static POINT		ILU[] = {30, 200, 130, 200, 230, 200, 30, 500, 130, 500, 230, 500, // I 6points
						400, 200, 400, 500, 550, 500,  // L 3points
						850, 200, 950, 500, 1050, 200,  // V 3points
						1100, 200, 1300, 200, 1100, 350, 1300, 350, 1100, 500, 1300, 500
	};	

	switch (message)
	{
	case WM_CREATE:
		hdcScreen = CreateDC(TEXT("DISPLAY"), NULL, NULL, NULL);  // 为整个视频显示创建一个设备环境
		InvalidateRect(NULL, NULL, TRUE);
		SetTimer(hwnd, ID_TIMER, 100, NULL);

		return 0;

	case WM_TIMER:

		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		GetClientRect(hwnd, &rc);

		DrawILoveU(hwnd, ILU);

		EndPaint(hwnd, &ps);
		return 0;

	case WM_DESTROY:
		DeleteDC(hdcScreen);
		KillTimer(hwnd, ID_TIMER);
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

void DrawWord(HDC, const POINT *, const int *, int num);
void DrawILoveU(HWND hwnd, const POINT * pt)
{
	HDC		hdc		= CreateDC(TEXT("DISPLAY"), NULL, NULL, NULL);  // 为整个视频显示创建一个设备环境
	HPEN	hpen	= CreatePen(PS_SOLID, 30, 0x0000ff);
	SelectObject(hdc, hpen);

		// 画 I

	int wordI[] = {0, 2, 1, 4, 3, 5};
	DrawWord(hdc, pt, wordI, 6);

		// 画 L

	int wordL[] = {0, 1, 1, 2};
	DrawWord(hdc, &pt[6], wordL, 4);

		// 画 O

	Ellipse(hdc, 600, 200, 800, 500);
	//RECT rc = {600, 200, 800, 500};
	//OffsetRect(&rc, 30, 230);
	//SetBkMode(hdc, TRANSPARENT);
	//RoundRect(hdc, rc.left, rc.top, rc.right, rc.bottom, 20, 20);

		// 画 V

	int wordV[] = {0, 1, 1, 2};
	DrawWord(hdc, &pt[9], wordV, 4);

		// 画 E

	int wordE[] = {0, 1, 2, 3, 4, 5, 0, 4};
	DrawWord(hdc, &pt[12], wordE, 8);

	ReleaseDC(hwnd, hdc);
	DeleteObject(hpen);
}

void DrawWord(HDC hdc, const POINT * pt, const int * iAr, int num)
{
	int flag = 0;
	for (int i = 0; i < num; i ++)
	{
		if (flag ^= 1)
			MoveToEx(hdc, pt[iAr[i]].x, pt[iAr[i]].y, NULL);
		else
			LineTo(hdc, pt[iAr[i]].x, pt[iAr[i]].y);
	}
}