// version 1.0 bugs:
//     1. 初始化的时候必须将Scroll范围放在WM_CREATE外边, 因为cyClient还不知道;
//     2. 初始化的时候必须将Scroll的位置初始化放在WM_CREATE里面, 跟范围初始化一起放在WM_SIZE中会导致拖动放大窗口的时候滑块回到最上边;
//     3. 滑块划到最下边显示最后一行, 但是拖大窗口会显示空白, 此时滑块还是最后一行;
#include <Windows.h>
#include "p075TextOut格式化绘制文字.h"
#define version 1  // 1    2

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("p077TextOut格式化绘制文字");
	HWND hwnd;
	MSG  msg;
	WNDCLASS wndclass;

	wndclass.cbClsExtra    = 0;
	wndclass.cbWndExtra    = 0;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hInstance     = hInstance;
	wndclass.lpfnWndProc   = WndProc;
	wndclass.lpszClassName = TEXT("wndclass");
	wndclass.lpszMenuName  = NULL;
	wndclass.style         = CS_VREDRAW | CS_HREDRAW;

	RegisterClass(&wndclass);

	hwnd = CreateWindow(TEXT("wndclass"), TEXT("Caption Bar"), WS_OVERLAPPEDWINDOW | WS_VSCROLL, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
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
	static int cxChar, cxCaps, cyChar, cxClient, cyClient, iVertPos = 0;
	HDC hdc;
	int i;
	PAINTSTRUCT ps;
	TCHAR szBuffer[10];
	TEXTMETRIC tm;

	switch (message)
	{
	case WM_CREATE:
		hdc = GetDC(hwnd);

		// 文本格式初始化
		GetTextMetrics(hdc, &tm);
		cxChar = tm.tmAveCharWidth;
		cxCaps = (tm.tmPitchAndFamily & 1 ? 3 : 2) / 2 * cxChar;
		cyChar = tm.tmHeight + tm.tmExternalLeading;

#if version == 2
		
		SetScrollRange(hwnd, SB_VERT, 0, NUMLINES - 1, FALSE);

#endif

		SetScrollPos(hwnd, SB_VERT, 0, TRUE);
		ReleaseDC(hwnd, hdc);
		return 0;

	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		
#if version == 1
		// 滚动条范围位置初始化
		SetScrollRange(hwnd, SB_VERT, 0, NUMLINES - cyClient / cyChar, FALSE);
		
#endif
		//SendMessage(hwnd, WM_VSCROLL, SB_LINEDOWN, 1);  // 防止显示最后一行的时候拖大客户区显示出空白;
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

#if version == 1
		int j;
		for (i = iVertPos, j = 0; i < NUMLINES; i++, j++)
		{
			TextOut(ps.hdc, 0, cyChar * j, sysmetrics[i].szLabel, lstrlen(sysmetrics[i].szLabel));
			TextOut(ps.hdc, 22 * cxCaps, cyChar * j, sysmetrics[i].szDesc, lstrlen(sysmetrics[i].szDesc));
			SetTextAlign(hdc, TA_RIGHT | TA_TOP);
			TextOut(ps.hdc, 22 * cxCaps + 40 * cxChar, cyChar * j, szBuffer, wsprintf(szBuffer, TEXT("%5d"), GetSystemMetrics(sysmetrics[i].Index)));
			SetTextAlign(hdc, TA_LEFT | TA_TOP);
		}
#elif version == 2
		int y;
		for (i = 0; i < NUMLINES; i++)
		{
			y = (i - iVertPos) * cyChar;
			TextOut(ps.hdc, 0, y, sysmetrics[i].szLabel, lstrlen(sysmetrics[i].szLabel));
			TextOut(ps.hdc, 22 * cxCaps, y, sysmetrics[i].szDesc, lstrlen(sysmetrics[i].szDesc));
			SetTextAlign(hdc, TA_RIGHT | TA_TOP);
			TextOut(ps.hdc, 22 * cxCaps + 40 * cxChar, y, szBuffer, wsprintf(szBuffer, TEXT("%5d"), GetSystemMetrics(sysmetrics[i].Index)));
			SetTextAlign(hdc, TA_LEFT | TA_TOP);
		}
#endif

		EndPaint(hwnd, &ps);
		return 0;

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

		case SB_THUMBTRACK:
			iVertPos = HIWORD(wParam);
			break;
		}

#if version == 1
		iVertPos = max(min(iVertPos, NUMLINES - cyClient / cyChar), 0);
#elif version == 2
		iVertPos = max(min(iVertPos, NUMLINES - 1), 0);
#endif

		if (iVertPos != GetScrollPos(hwnd, SB_VERT))
		{
			SetScrollPos(hwnd, SB_VERT, iVertPos, TRUE);
			InvalidateRect(hwnd, NULL, TRUE);  // 使整个窗口无效 此函数会生成WM_PAINT消息
		}
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}