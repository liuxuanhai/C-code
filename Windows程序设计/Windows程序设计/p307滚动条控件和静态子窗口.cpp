// 1. 了解滚动条和静态子窗口的使用
// 2. 深入探索着色原理

#include <windows.h>

LRESULT CALLBACK WndProc		(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ScrollProc	(HWND, UINT, WPARAM, LPARAM);

int		idFocus;
WNDPROC	OldScroll[3];

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("p307滚动条空间和静态子窗口");
	HWND hwnd;
	MSG  msg;
	WNDCLASS wndclass;

	wndclass.cbClsExtra    = 0;
	wndclass.cbWndExtra    = 0;
	wndclass.hbrBackground = CreateSolidBrush(0);
	wndclass.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hInstance     = hInstance;
	wndclass.lpfnWndProc   = WndProc;
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName  = NULL;
	wndclass.style         = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wndclass);

	hwnd = CreateWindow(szAppName, szAppName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
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
	static COLORREF		crPrim[3] = {RGB(255, 0, 0), RGB(0, 255, 0), RGB(0, 0, 255)};
	static HBRUSH		hBrush[3], hBrushStatic;
	static HWND			hwndScroll[3], hwndLabel[3], hwndValue[3], hwndRect;
	static int			color[3], cyChar;
	static RECT			rcColor;
	static TCHAR *		szColorLabel[] = {TEXT("Red"), TEXT("Green"), TEXT("Blue")};
	HINSTANCE			hInstance;
	int					i, cxClient, cyClient;
	TCHAR				szBuffer[10];

	switch (message)
	{
	case WM_CREATE:
		hInstance = (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE);

			// 创建白色静态ID为9的子窗口, 三个滚动条控件将会在这个子窗口上边;

		hwndRect = CreateWindow(TEXT("static"), NULL, WS_CHILD | WS_VISIBLE | SS_WHITERECT/*静态填充白色矩形*/,
			0, 0, 0, 0,// 子窗口的位置和大小是根据客户区决定的, 而且这个时候客户区大小和位置是未知的, 所以用MoveWindow函数设置最好了
			hwnd, (HMENU)9, hInstance, NULL);

			// 创建三个滚动条控件, 设置滚动条控件ID, 滚动条范围
			// 创建三个静态控件, 用于显示滚动态的颜色, 设置静态控件ID, 设置控件文本
			// 创建三个静态控件, 用于显示滚动条的数值, 设置静态控件ID, 设置控件初始值
			// 改变滚动条控件的窗口过程;

		for (i = 0; i < 3; i++)
		{

			// 三个滚动条ID位0 - 2, 范围为 0 - 255

			hwndScroll[i] = CreateWindow(TEXT("scrollbar"), NULL,
				WS_CHILD | WS_VISIBLE | WS_TABSTOP | SBS_VERT, // SBS_VERT不同于SB_VERT, 这个是滚动条控件而不是窗口滚动条
				0, 0, 0, 0,
				hwnd, (HMENU)i, hInstance, NULL);

			SetScrollRange(hwndScroll[i], SB_CTL, 0, 255, FALSE);
			SetScrollPos(hwndScroll[i], SB_CTL, 0, FALSE);

				// 三个滚动条颜色标签静态控件ID为 3, 4, 5, 文本为 "Red", "Green", "Blue";

			hwndLabel[i] = CreateWindow(TEXT("static"), szColorLabel[i], 
				WS_CHILD | WS_VISIBLE | SS_CENTER,  // SS_CENTER 创建居中对齐的文本
				0, 0, 0, 0,
				hwnd, (HMENU)(i + 3), hInstance, NULL);

				// 三个滚动条数值大小静态控件ID为6, 7, 8, 初始数值为"0"

			hwndValue[i] = CreateWindow(TEXT("static"), TEXT("0"),
				WS_CHILD | WS_VISIBLE | SS_CENTER,
				0, 0, 0, 0,
				hwnd, (HMENU)(i + 6), hInstance, NULL);

				// 设置新的滚动条窗口过程的地址, 同时获得现有滚动条窗口过程的地址;

			OldScroll[i] = (WNDPROC)SetWindowLong(hwndScroll[i], GWL_WNDPROC, (LONG)ScrollProc);  
					// 滚动条控件的窗口过程在windows内部, 可以通过调用GetWindowLong来获取这个窗口过程的地址
					// 还可以通过调用SetWindowLong为滚动条设置一个新的窗口过程, 这种技术成为"窗口子类"
					// 新的窗口过程通过CallWindowProc来调用就得滚动条窗口过程;

				// 画刷设置成滚动条的三原色名称对应的颜色
			
			hBrush[i] = CreateSolidBrush(crPrim[i]);
		}

		hBrushStatic = CreateSolidBrush(GetSysColor(COLOR_BTNHIGHLIGHT));

		cyChar = HIWORD(GetDialogBaseUnits());
		return 0;

		// 设置所有控件的位置

	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		SetRect(&rcColor, cxClient / 2, 0, cxClient, cyClient);  // 整个客户区的右半部分

			// 将静态子窗口控件设置为整个客户区的左半部分

		MoveWindow(hwndRect, 0, 0, cxClient / 2, cyClient, TRUE);

			// 设置其他九个控件的位置

		for (i = 0; i < 3; i++)
		{
			MoveWindow(hwndScroll[i], (2 * i + 1) * cxClient / 14, 2 * cyChar, cxClient / 14, cyClient - 4 * cyChar, TRUE);
			MoveWindow(hwndLabel[i] , (4 * i + 1) * cxClient / 28, cyChar / 2, cxClient / 7 , cyChar, TRUE);
			MoveWindow(hwndValue[i] , (4 * i + 1) * cxClient / 28, cyClient - 3 * cyChar / 2, cxClient / 7, cyChar, TRUE);
		}

			// 产生WM_SETFOCUS消息

		SetFocus(hwnd);
		return 0;

	case WM_SETFOCUS:
		SetFocus(hwndScroll[idFocus]);
		return 0;

		// 三个滚动条产生颜色的逻辑, 滑块位置逻辑, 颜色数值更新

	case WM_VSCROLL:
		i = GetWindowLong((HWND)lParam, GWL_ID);

		switch (LOWORD(wParam))
		{
		case SB_PAGEDOWN:
			color[i] += 15;
								// fall through

		case SB_LINEDOWN:
			color[i] = min(255, color[i] + 1);
			break;

		case SB_PAGEUP:
			color[i] -= 15;
							// fall through

		case SB_LINEUP:
			color[i] = max(0, color[i] - 1);
			break;

		case SB_TOP:
			color[i] = 0;
			break;

		case SB_BOTTOM:
			color[i] = 255;
			break;

		case SB_THUMBPOSITION:
		case SB_THUMBTRACK:
			color[i] = HIWORD(wParam);
			break;
		}

			// 设置滑块位置

		SetScrollPos(hwndScroll[i], SB_CTL, color[i], TRUE);

			// 更新颜色数值的大小

		wsprintf(szBuffer, TEXT("%i"), color[i]);
		SetWindowText(hwndValue[i], szBuffer);

			// 将滚动条窗口控件原来的画刷删除, 并加进去新的滚动条生成颜色的画刷

		DeleteObject((HBRUSH)
			SetClassLong(hwnd, GCL_HBRBACKGROUND, (LONG) // SetClassLong: 正如SetWindowLong可以设置窗口过程一样, SetClassLong可以设置窗口类结构
				CreateSolidBrush(RGB(color[0], color[1], color[2]))));

			// 使得整个客户区右半部分无效

		InvalidateRect(hwnd, &rcColor, TRUE);
		return 0;

		// 滚动条控件颜色的设置

	case WM_CTLCOLORSCROLLBAR:
		i = GetWindowLong((HWND)lParam, GWL_ID);
		return (LRESULT)hBrush[i];  // 通过在这个消息下返回一个画刷来修改原来的颜色;

		// 静态控件文本颜色的设置

	case WM_CTLCOLORSTATIC:
		i = GetWindowLong((HWND)lParam, GWL_ID);

		if (i >= 3 && i <= 8)  // 如果是静态文本控件的话
		{
			SetTextColor((HDC)wParam, crPrim[i % 3]);  // 设置文本颜色
			SetBkColor((HDC)wParam, GetSysColor(COLOR_BTNHIGHLIGHT));  // 设置文本的背景颜色 ! 这里设置的是文本的背景而不是整个静态控件的背景, 这里是通过窗口过程返回COLOR_BTNHIGHLIGHT颜色的画刷句柄实现的;
			return (LRESULT)hBrushStatic;
		}
		break;

	case WM_SYSCOLORCHANGE:  // 防止COLOR_BTNHIGHLIGHT颜色在程序运行过程中被改变了引起的影响;
		DeleteObject(hBrushStatic);
		hBrushStatic = CreateSolidBrush(GetSysColor(COLOR_BTNHIGHLIGHT));
		return 0;

	case WM_DESTROY:
		DeleteObject((HBRUSH)
			SetClassLong(hwnd, GCL_HBRBACKGROUND, (LONG)
			GetStockObject(WHITE_BRUSH)));

		for (i = 0; i < 3; i++)
			DeleteObject(hBrush[i]);

		DeleteObject(hBrushStatic);
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

LRESULT CALLBACK ScrollProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int id = GetWindowLong(hwnd, GWL_ID);

	switch (message)
	{
	case WM_KEYDOWN:
		if (wParam == VK_TAB)
			SetFocus(GetDlgItem(GetParent(hwnd), (id + (GetKeyState(VK_SHIFT) < 0 ? 2 : 1)) % 3));
		break;
	
	case WM_SETFOCUS:
		idFocus = id;
		break;
	}
	return CallWindowProc(OldScroll[id], hwnd, message, wParam, lParam);
}