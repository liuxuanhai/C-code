#include <windows.h>
#include "p075TextOut格式化绘制文字.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("AppName");
	HWND hwnd;
	MSG  msg;
	WNDCLASS wndclass;

	wndclass.cbClsExtra     = 0;
	wndclass.cbWndExtra     = 0;
	wndclass.hbrBackground  = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.hCursor        = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon          = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hInstance      = hInstance;
	wndclass.lpfnWndProc    = WndProc;
	wndclass.lpszClassName  = szAppName;
	wndclass.lpszMenuName   = NULL;
	wndclass.style          = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wndclass);

	hwnd = CreateWindow(szAppName, szAppName, WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int cxChar, cxCaps, cyChar, cxClient, cyClient, iMaxWidth;
	HDC hdc;
	int i, x, y, iVertPos, iHorzPos, iPaintBeg, iPaintEnd;
	PAINTSTRUCT ps;
	SCROLLINFO  si;
	TCHAR       szBuffer[10];
	TEXTMETRIC  tm;

	switch (message)
	{
	case WM_CREATE:
		hdc = GetDC(hwnd);

		GetTextMetrics(hdc, &tm);
		cxChar = tm.tmAveCharWidth;
		cxCaps = (tm.tmPitchAndFamily & 1 ? 3 : 2) / 2 * cxChar;
		cyChar = tm.tmHeight + tm.tmExternalLeading;
		iMaxWidth = 40 * cxChar + 22 * cxCaps;

		ReleaseDC(hwnd, hdc);
		return 0;

	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);

		si.cbSize = sizeof(si);
		si.fMask  = SIF_RANGE | SIF_PAGE;
		si.nMin   = 0;
		si.nMax   = NUMLINES - 1;
		si.nPage  = cyClient / cyChar;
		SetScrollInfo(hwnd, SB_VERT, &si, TRUE);

		si.cbSize = sizeof(si);
		si.fMask  = SIF_RANGE | SIF_PAGE | SIF_DISABLENOSCROLL;
		si.nMin   = 0;
		si.nMax   = 2 + iMaxWidth / cyChar;
		si.nPage  = cxClient / cxChar;
		SetScrollInfo(hwnd, SB_HORZ, &si, TRUE);

		return  0;

	case WM_VSCROLL:
		si.cbSize = sizeof(si);
		si.fMask  = SIF_ALL;
		GetScrollInfo(hwnd, SB_VERT, &si);
		iVertPos = si.nPos;

		switch (LOWORD(wParam))
		{
		case SB_TOP:
			si.nPos = si.nMin;
			break;

		case SB_BOTTOM:
			si.nPos = si.nMax;
			break;

		case SB_LINEDOWN:
			si.nPos += 1;
			break;

		case SB_LINEUP:
			si.nPos -= 1;
			break;

		case SB_PAGEUP:
			si.nPos -= si.nPage;
			break;

		case SB_PAGEDOWN:
			si.nPos += si.nPage;

		case SB_THUMBTRACK:
			si.nPos = si.nTrackPos;
			break;
		}
		si.fMask = SIF_POS;
		SetScrollInfo(hwnd, SB_VERT, &si, TRUE);
		GetScrollInfo(hwnd, SB_VERT, &si);
		if (si.nPos != iVertPos)
		{
			ScrollWindow(hwnd, 0,  // 客户区水平滚动多少像素
				cyChar * (iVertPos - si.nPos),  // 客户区垂直滚动多少像素
				NULL, NULL);  // 最后两个参数设置成NULL表示需要 滚动整个客户区
			// windows自动将新滚动出现的地方无效化, 从而产生一条WM_PAINT消息, 这里并不需要调用InvalidateRect函数, 需要注意的是ScrollWindow并不是GDI函数, 因为他并不需要要设备环境句柄作为参数;
			UpdateWindow(hwnd);
		}
		return 0;

	case WM_HSCROLL:
		si.cbSize = sizeof(si);
		si.fMask  = SIF_ALL;
		GetScrollInfo(hwnd, SB_HORZ, &si);
		iHorzPos = si.nPos;

		switch (LOWORD(wParam))
		{
		case SB_LEFT:
			si.nPos = si.nMin;
			break;

		case SB_RIGHT:
			si.nPos = si.nMax;
			break;

		case SB_PAGERIGHT:
			si.nPos += si.nPage;
			break;

		case SB_PAGELEFT:
			si.nPos -= si.nPage;
			break;

		case SB_LINELEFT:
			si.nPos -= 1;
			break;

		case SB_LINERIGHT:
			si.nPos += 1;
			break;

		case SB_THUMBPOSITION:
			si.nPos = si.nTrackPos;
			break;
		}
		si.fMask = SIF_POS;
		SetScrollInfo(hwnd, SB_HORZ, &si, TRUE);
		GetScrollInfo(hwnd, SB_HORZ, &si);

		if (si.nPos != iHorzPos)
		{
			ScrollWindow(hwnd, cxChar * (iHorzPos - si.nPos), 0, NULL, NULL);
		}
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		si.cbSize = sizeof(si);
		si.fMask  = SIF_POS;

		GetScrollInfo(hwnd, SB_VERT, &si);
		iVertPos = si.nPos;

		GetScrollInfo(hwnd, SB_HORZ, &si);
		iHorzPos = si.nPos;

		iPaintBeg = max(0, iVertPos + ps.rcPaint.top / cyChar);
		iPaintEnd = min(NUMLINES - 1, iVertPos + ps.rcPaint.bottom / cyChar);

		// 程序确定了那些行落在了无效矩形中, 并且只重绘那些行;
		for (i = iPaintBeg; i <= iPaintEnd; i++)
		{
			x = cxChar * (1 - iHorzPos);
			y = cyChar * (i - iVertPos);

			TextOut(hdc, x, y, sysmetrics[i].szLabel, lstrlen(sysmetrics[i].szLabel));
			TextOut(hdc, x + 22 * cxCaps, y, sysmetrics[i].szDesc, lstrlen(sysmetrics[i].szDesc));
			SetTextAlign(hdc, TA_TOP | TA_RIGHT);
			TextOut(hdc, x + 22 * cxCaps + 40 * cxChar, y, szBuffer, wsprintf(szBuffer, TEXT("%5d"), GetSystemMetrics(sysmetrics[i].Index)));
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