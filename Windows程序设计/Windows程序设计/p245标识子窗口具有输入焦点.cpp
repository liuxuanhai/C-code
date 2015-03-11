// 注意: 单击子窗口时候, 获得输入焦点的是父窗口, 而不是子窗口;

#include <windows.h>
#define	 DIVSIONS 5

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ChildWndProc(HWND, UINT, WPARAM, LPARAM);

int		idFocus = 0;
TCHAR	szChildClass[] = TEXT("p245标识子窗口具有输入焦点_子窗口");

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	static TCHAR	szAppName[] = TEXT("p245标识子窗口具有输入焦点");
	HWND			hwnd;
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

	RegisterClass(&wndclass);

	wndclass.cbWndExtra			= sizeof(long);
	wndclass.hIcon				= LoadIcon(NULL, NULL);
	wndclass.lpfnWndProc		= ChildWndProc;
	wndclass.lpszClassName		= szChildClass;

	RegisterClass(&wndclass);

	hwnd = CreateWindow(szAppName, szAppName,
						WS_OVERLAPPEDWINDOW, 
						CW_USEDEFAULT, CW_USEDEFAULT, 
						CW_USEDEFAULT, CW_USEDEFAULT,
						NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND hwndChild[DIVSIONS][DIVSIONS];
	int			cxBlock, cyBlock, x, y;

	switch (message)
	{
	case WM_CREATE:
		for (x = 0; x < DIVSIONS; x++)
			for (y = 0; y < DIVSIONS; y++)
				hwndChild[x][y] = CreateWindow(szChildClass, NULL,
												WS_CHILDWINDOW | WS_VISIBLE,
												0, 0, 0, 0,
												hwnd, (HMENU)(y << 8 | x),
												(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
												NULL);
		return 0;

	case WM_SIZE:
		cxBlock = LOWORD(lParam) / DIVSIONS;
		cyBlock = HIWORD(lParam) / DIVSIONS;

		for (x = 0; x < DIVSIONS; x++)
			for (y = 0; y < DIVSIONS; y++)
				MoveWindow(hwndChild[x][y],
							x * cxBlock, y * cyBlock,
							cxBlock, cyBlock, TRUE);

		return 0;

	case WM_LBUTTONDOWN:
		MessageBeep(0);
		return 0;

	case WM_SETFOCUS:
		SetFocus(GetDlgItem(hwnd, idFocus));  // idFocus用于保存当前具有输入焦点的窗口的子ID数值;
		// 在子窗口上单击鼠标时, 子窗口不能自动获得输入焦点, 所以这里使用这个函数处理WM_SETFOCUS消息, 从而给其中的一个子窗口设置输入焦点;
		return 0;

	case WM_KEYDOWN:
		x = idFocus & 0xff;  // 保存idFocus低八位的数据
		y = idFocus >> 8;

		switch (wParam)
		{
		case VK_UP:		y--;				break;
		case VK_DOWN:	y++;				break;
		case VK_LEFT:	x--;				break;
		case VK_RIGHT:	x++;				break;
		case VK_HOME:	x = y = 0;			break;
		case VK_END:	x = y = DIVSIONS;	break;
		default:							return 0;
		}

		x = (x + DIVSIONS) % DIVSIONS;
		y = (y + DIVSIONS) % DIVSIONS;

		idFocus = y << 8 | x;

		SetFocus(GetDlgItem(hwnd, idFocus));
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

LRESULT CALLBACK ChildWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT		ps;
	HDC				hdc;
	RECT			rect;

	switch (message)
	{
	case WM_CREATE:
		SetWindowLong(hwnd, 0, 0);  // on / off flag
		return 0;

	case WM_KEYDOWN:
		if (wParam != VK_RETURN && wParam != VK_SPACE)  // 除了空格和回车, 其他都交还给父窗口处理
		{
			SendMessage(GetParent(hwnd), message, wParam, lParam);
			return 0;
		}
	case WM_LBUTTONDOWN:
		SetWindowLong(hwnd, 0, 1 ^ GetWindowLong(hwnd, 0));
		SetFocus(hwnd);
		InvalidateRect(hwnd, NULL, FALSE);
		return 0;

	case WM_SETFOCUS:  // 处理WM_SETFOCUS消息时, 它将接收输入焦点的子窗口ID保存在全局变量idFocus中;
		idFocus = GetWindowLong(hwnd, GWL_ID);
	case WM_KILLFOCUS:
		InvalidateRect(hwnd, NULL, TRUE);  // 对于这两条消息, 程序都将使窗口无效, 并产生WM_PAINT消息, 如果WM_PAINT消息所绘制的子窗口具有输入焦点, 程序就画一个虚线矩形, 否则把原来的虚线矩形去掉;
							// 值得注意的是这里是一个小小的子窗口的WM_PAINT, 相对于用区域控制的来说效率高多了;
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		GetClientRect(hwnd, &rect);
		Rectangle(hdc, 0, 0, rect.right, rect.bottom);

			// Draw the "x" mark

		if (GetWindowLong(hwnd, 0))
		{
			MoveToEx(hdc, 0, 0, NULL);
			LineTo(hdc, rect.right, rect.bottom);
			MoveToEx(hdc, 0, rect.bottom, NULL);
			LineTo(hdc, rect.right, 0);
		}

			// Draw the "focus" rectangle

		if (hwnd == GetFocus())
		{
			rect.left	+= rect.right / 10;
			rect.right	-= rect.left;  // 这里的hwnd是子窗口, 所以rect.left初始值为0, 然后...
			rect.top	+= rect.bottom / 10;
			rect.bottom	-= rect.top;

			SelectObject(hdc, GetStockObject(NULL_BRUSH));
			SelectObject(hdc, CreatePen(PS_DASH, 0, 0));
			Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
			DeleteObject(SelectObject(hdc, GetStockObject(BLACK_PEN)));
		}

		EndPaint(hwnd, &ps);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}