#include <windows.h>
#define  DIVISIONS 5

LRESULT CALLBACK WndProc		(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ChildWndProc	(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

TCHAR	szChildName[]	= TEXT("szChildName");
int		idFocus			= 0;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	HWND			hwnd;
	WNDCLASS		wndclass;
	static TCHAR	szAppName[] = TEXT("p245 标识子窗口具有输入焦点");

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
	
	wndclass.cbWndExtra		= sizeof(long);
	wndclass.hIcon				= NULL;
	wndclass.lpfnWndProc		= ChildWndProc;
	wndclass.lpszClassName		= szChildName;

	RegisterClass(&wndclass);  // 在注册子窗口之前不能CreateWIndow父窗口

	hwnd = CreateWindow(szAppName, szAppName, 
						WS_OVERLAPPEDWINDOW, 
						CW_USEDEFAULT, CW_USEDEFAULT, 
						CW_USEDEFAULT, CW_USEDEFAULT,
						NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	MSG		msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND		hChildWindow[DIVISIONS][DIVISIONS];
	static int		cxBlock, cyBlock, cxClient, cyClient;

	switch (message)
	{
	case WM_CREATE:
		//MessageBox(NULL, TEXT("父: WM_CREATE"), NULL, 0);
		for (int x = 0; x < DIVISIONS; x++)
			for (int y = 0; y < DIVISIONS; y++)
				hChildWindow[x][y] = CreateWindow(szChildName, NULL, 
													WS_CHILDWINDOW | WS_VISIBLE,
													0, 0, 0, 0,
													hwnd,
													(HMENU)(y << 8 | x),
													(HINSTANCE)GetWindowLong(hwnd, GWLP_HINSTANCE), 
													NULL);
		return 0;

	case WM_SIZE:
		//MessageBox(NULL, TEXT("父: WM_SIZE"), NULL, 0);
		cxClient	= LOWORD(lParam);
		cyClient	= HIWORD(lParam);
		cxBlock		= cxClient / DIVISIONS;
		cyBlock		= cyClient / DIVISIONS;

		for (int x = 0; x < DIVISIONS; x++)
			for (int y = 0; y < DIVISIONS; y++)
				MoveWindow(hChildWindow[x][y], x * cxBlock, y * cyBlock, cxBlock, cyBlock, TRUE);
		return 0;

	case WM_LBUTTONDOWN:
		MessageBeep(0);
		//MessageBox(NULL, TEXT("父: WM_LBUTTONDOWN"), NULL, 0);
		return 0;

	case WM_SETFOCUS:
		//MessageBox(NULL, TEXT("父: WM_SETFOCUS"), NULL, 0);
		SetFocus(GetDlgItem(hwnd, idFocus));
		return 0;

	case WM_KEYDOWN:
		//MessageBox(NULL, TEXT("父: WM_KEYDOWN"), NULL, 0);
		int x, y;
		x = idFocus & 0xff;
		y = idFocus >> 8;

		switch (wParam)
		{
		case VK_UP:		y--;				break;
		case VK_DOWN:	y++;				break;
		case VK_LEFT:	x--;				break;
		case VK_RIGHT:	x++;				break;
		case VK_HOME:	x = y = 0;			break;
		case VK_END:	x = y = DIVISIONS;	break;
		default:							return 0;
		}

		x = (x + DIVISIONS) % DIVISIONS;
		y = (y + DIVISIONS) % DIVISIONS;

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
	HDC			hdc;
	PAINTSTRUCT	ps;
	RECT		rect;
	switch (message)
	{
	case WM_CREATE:
		//MessageBox(NULL, TEXT("子: WM_CREATE"), NULL, 0);
		SetWindowLong(hwnd, 0, 0);  // on / off flag
		return 0;

	case WM_KEYDOWN:
		//MessageBox(NULL, TEXT("子: WM_KEYDOWN"), NULL, 0);
		if (wParam != VK_RETURN && wParam != VK_SPACE)
		{
			SendMessage(GetParent(hwnd), message, wParam, lParam);
			return 0;
		}
	case WM_LBUTTONDOWN:
		TCHAR szBuffer[100];
		wsprintf(szBuffer, TEXT("子(%d, %d): WM_LBUTTONDOWN"), GetWindowLong(hwnd, GWL_ID) & 0xff, GetWindowLong(hwnd, GWL_ID) >> 8);
		MessageBox(NULL, szBuffer, NULL, 0);
		SetWindowLong(hwnd, 0, 1 ^ GetWindowLong(hwnd, 0));
		SetFocus(hwnd);
		InvalidateRect(hwnd, NULL, FALSE);
		return 0;

	case WM_SETFOCUS:
		//MessageBox(NULL, TEXT("子: WM_SETFOCUS"), NULL, 0);
		idFocus = GetWindowLong(hwnd, GWL_ID);
	case WM_KILLFOCUS:
		//MessageBox(NULL, TEXT("子: WM_KILLFOCUS"), NULL, 0);
		InvalidateRect(hwnd, NULL, TRUE);
		return 0;

	case WM_PAINT:
		//MessageBox(NULL, TEXT("子: WM_PAINT"), NULL, 0);
		hdc = BeginPaint(hwnd, &ps);

		GetClientRect(hwnd, &rect);
		Rectangle(hdc, 0, 0, rect.right, rect.bottom);

		if (GetWindowLong(hwnd, 0))
		{
			MoveToEx(hdc, 0, 0, NULL);
			LineTo(hdc, rect.right, rect.bottom);
			MoveToEx(hdc, 0, rect.bottom, NULL);
			LineTo(hdc, rect.right, 0);
		}

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