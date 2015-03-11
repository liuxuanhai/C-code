#include <windows.h>
#include "p075TextOut格式化绘制文字.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("加入了滚动条的程序");
	HWND hwnd;
	MSG  msg;
	WNDCLASS wndclass;
	
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wndclass);
													//  第三个参数是窗口风格标示符
	hwnd = CreateWindow(szAppName, TEXT("多了滚动条"), WS_OVERLAPPEDWINDOW | WS_VSCROLL/*在这里设置的滚动条*/, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
	ShowWindow(hwnd, iCmdShow);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	switch (message)
	{
	case WM_CREATE:	
		hdc = GetDC(hwnd);

		// 给字体绘制设置数据
		TEXTMETRIC tm;
		GetTextMetrics(hdc, &tm);
		static int cxChar, cxCaps, cyChar;
		cxChar = tm.tmAveCharWidth;
		cxCaps = (tm.tmPitchAndFamily & 1 ? 3 : 2) * cxChar / 2;
		cyChar = tm.tmHeight + tm.tmExternalLeading;

		// 给滚动条加上范围, 设置初始位置
		static int iVertPos;
		SetScrollRange(hwnd, SB_VERT, 0, NUMLINES-1, FALSE);
		SetScrollPos(hwnd, SB_VERT, iVertPos, TRUE);

		ReleaseDC(hwnd, hdc);
		return 0;

	case WM_SIZE:
		static int cyClient;
		cyClient = HIWORD(lParam);
		break;

	case WM_VSCROLL:
		switch (LOWORD(wParam))
		{
		case SB_LINEUP:
			iVertPos -= 1;
			break;
			
		case SB_LINEDOWN:
			iVertPos += 1;
			break;

		case SB_PAGEUP:
			iVertPos -= cyClient / cyChar;
			break;
		
		case SB_PAGEDOWN:
			iVertPos += cyClient / cyChar;
			break;
		case SB_THUMBPOSITION:
			iVertPos = HIWORD(wParam);
			break;
		}

		iVertPos = max(0, min(iVertPos, NUMLINES-1));

		if (iVertPos != GetScrollPos(hwnd, SB_VERT))
		{
			SetScrollPos(hwnd, SB_VERT, iVertPos, TRUE);
			InvalidateRect(hwnd, NULL, TRUE);
		}

	case WM_PAINT:
		PAINTSTRUCT ps;
		hdc = BeginPaint(hwnd, &ps);

		int y;
		for (int i = 0; i < NUMLINES - 1; i++)
		{
			y = cyChar * (i - iVertPos); 
			TextOut(hdc, 0, y, sysmetrics[i].szLabel, lstrlen(sysmetrics[i].szLabel));
			TextOut(hdc, 22 * cxCaps, y, sysmetrics[i].szDesc, lstrlen(sysmetrics[i].szDesc));
			SetTextAlign(hdc, TA_TOP | TA_RIGHT);
			TCHAR szBuffer[10];
			TextOut(hdc, 22 * cxCaps + 40 * cxChar, y, szBuffer, wsprintf(szBuffer, TEXT("%5d"), GetSystemMetrics(sysmetrics[i].Index)));
			SetTextAlign(hdc, TA_TOP | TA_LEFT);
		}

		EndPaint(hwnd, &ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}