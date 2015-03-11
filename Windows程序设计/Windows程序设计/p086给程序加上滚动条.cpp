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
	static int cxChar, cxCaps, cyChar, cyClient, iVscrollPos/*用来表示滑块的当前位置*/;
	HDC         hdc;
	int         i, y;
	PAINTSTRUCT ps;
	TCHAR       szBuffer[10];
	TEXTMETRIC  tm;

	switch (message)
	{
	case WM_CREATE:
		hdc = GetDC(hwnd);

		GetTextMetrics(hdc, &tm);
		cxChar = tm.tmAveCharWidth;
		cxCaps = (tm.tmPitchAndFamily & 1 ? 3 : 2) * cxChar / 2;
		cyChar = tm.tmHeight + tm.tmExternalLeading;

		ReleaseDC(hwnd, hdc);

		// 设定滚动条的范围
		SetScrollRange(hwnd, SB_VERT, 0, NUMLINES - 1/*有NUMLINES行文字, 所以滚动条的范围为0~NUMLINES-1*/,  // 如果滚动条的位置是0, 则第一行文字显示在客户区, 如果是其他值则其他行会显示在顶部. 如果是NUMLINES-1, 则最后一行显示在顶部
			FALSE);  // 如果需要windows根据范围来重绘滚动条, 这里为TRUE. 如果调用这个SetScrollRange()之后还将调用其它函数来调整滚动条的显示, 则最好将这里设置成false以避免过多重绘  
		SetScrollPos(hwnd, SB_VERT, iVscrollPos, TRUE);  // 设定滚动条的位置
		return 0;
	
	// 当窗口大小发生变化的时候, windows会向窗口过程发送一条WM_SIZE消息.
	// lParam变量的低位字是客户区的宽度, 高位字是高度.
	case WM_SIZE:
		cyClient = HIWORD(lParam);  // 这里取到了lParam的高四位, 即客户区的高度
		// 可以通过用GetClientRect()来获取客户区的大小, 但是如果每次需要时都要调用这个函数显然没有效率, 所以没有采取这种措施
		return 0;

	case WM_VSCROLL:
		// 当滚动条是窗口的一部分的时候, 可以忽略lParam参数, 它只用于滚动条是子窗口时, 通常是在对话框中
		// wParam的低位字代表鼠标在滚动条上的动作, 这个值称为"通知吗".
		// 当通知码为SB_THUMBTRACK的时候为鼠标点着滑块拖动, 此时wParam的高位字为用户拖动滑块的当前位置
		// 当通知码为SB_THUMBPOSTION的时候, wParam是用户松开鼠标的最终位置
		// 对于其他的滚动条动作, wParam的高位应该被忽略
		switch (LOWORD(wParam))
		{
		case SB_LINEUP:
			iVscrollPos -= 1;
			break;
		case SB_LINEDOWN:
			iVscrollPos += 1;
			break;
		case SB_PAGEUP:
			iVscrollPos -= cyClient / cyChar;
			break;
		case SB_PAGEDOWN:
			iVscrollPos += cyClient / cyChar;
			break;

		////////////////////////////////////////////////////////////
		// 这个情况是自己加上的, 他实现了鼠标拖动和屏幕移动的同步
		case SB_THUMBTRACK:
			iVscrollPos = HIWORD(wParam);
			break;
		////////////////////////////////////////////////////////////
			
		case SB_THUMBPOSITION:
			iVscrollPos = HIWORD(wParam);
			break;
		default:
			break;
		}
		iVscrollPos = max(0, min(iVscrollPos, NUMLINES - 1));  // 确保iVscrollPos在范围内

		if (iVscrollPos != GetScrollPos(hwnd, SB_VERT))  // 如果当前位置iVscrollPos与先前位置GetScrollPos()不相等
		{
			SetScrollPos(hwnd, SB_VERT, iVscrollPos, TRUE);  // 更新当前位置
			InvalidateRect(hwnd, NULL, TRUE);  // 使整个窗口无效 此函数会生成WM_PAINT消息
			// Invalidate()返回的WM_PAINT消息被放到了消息队列中, windows将WM_PAINT当做低优先级的消息处理, 此时可能出现的情况: 例如关闭窗口后屏幕变成白的, 这是在等待绘制.
			// 如果想要立即更新无效区域, 则可以在调用InvalidateRect()后立即调用UpdateWindow(), 如果客户区有任何一部分是无效的, UpdateWindow()将会是窗口过程立即收到一条WM_PAINT消息. (如果整个客户区是有效的, UpdateWindow将不会调用窗口过程.)这时, WM_PAINT消息将会越过消息队列, 直接由Windows调用窗口过程, 当窗口过程完成绘制后, UpdateWIndow函数将控制权返回给调用它的代码.
		}
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		for (i = 0; i < NUMLINES; i++)
		{
			y = cyChar * (i - iVscrollPos);
			TextOut(hdc, 0, y, sysmetrics[i].szLabel, lstrlen(sysmetrics[i].szLabel));
			TextOut(hdc, 22 * cxCaps, y, sysmetrics[i].szDesc, lstrlen(sysmetrics[i].szDesc));
			SetTextAlign(hdc, TA_RIGHT | TA_TOP);
			TextOut(hdc, 22 * cxCaps + 40 * cxChar, y, szBuffer, wsprintf(szBuffer, TEXT("%5d"), GetSystemMetrics(sysmetrics[i].Index)));
			SetTextAlign(hdc, TA_LEFT | TA_TOP);
		}
		EndPaint(hwnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}