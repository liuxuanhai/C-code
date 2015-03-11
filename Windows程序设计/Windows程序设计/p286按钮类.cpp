#include <windows.h>

struct
{
	int		iStyle;
	TCHAR *	szText;
}
button[] =
{
	BS_PUSHBUTTON,			TEXT("PUSHBUTTON"),
	BS_DEFPUSHBUTTON,		TEXT("DEFPUSHBUTTON"),
	BS_CHECKBOX,			TEXT("CHECKBOX"),
	BS_AUTOCHECKBOX,		TEXT("AUTOCHECKBOX"),
	BS_RADIOBUTTON,			TEXT("RADIOBUTTON"),
	BS_3STATE,				TEXT("3STATE"),
	BS_AUTO3STATE,			TEXT("AUTO3STATE"),
	BS_GROUPBOX,			TEXT("GROUPBOX"),
	BS_AUTORADIOBUTTON,		TEXT("AUTORADIOBUTTON"),
	BS_OWNERDRAW,			TEXT("OWNERDRAW")
};

#define NUM (sizeof button / sizeof button[0])

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	static TCHAR	szAppName[] = TEXT("p286按钮类");
	HWND			hwnd;
	MSG				msg;
	WNDCLASS		wndclass;

	wndclass.style				= CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc		= WndProc;
	wndclass.cbClsExtra		= 0;
	wndclass.cbWndExtra		= 0;
	wndclass.hInstance			= hInstance;
	wndclass.hIcon				= LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor			= LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground		= (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName		= NULL;
	wndclass.lpszClassName		= szAppName;

	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("windows 7 need!"), szAppName, MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(szAppName, szAppName, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL);
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
	static HWND		hwndButton[NUM];
	static RECT		rect;
	static TCHAR	szTop[]		= TEXT("message			wParam			lParam"),
					szUnd[]		= TEXT("_______			______			______"),
					szFormat[]	= TEXT("%-16s%04x-%04x %04x-%04x"),
					szBuffer[50];
	static int		cxChar, cyChar;
	HDC				hdc;
	PAINTSTRUCT		ps;
	int				i;

	switch (message)
	{
	case WM_CREATE:
		cxChar = LOWORD(GetDialogBaseUnits());
		cyChar = HIWORD(GetDialogBaseUnits());

		for (i = 0;i < NUM; i++)
			hwndButton[i] = CreateWindow(TEXT("button"), // 类名
			button[i].szText, // 窗口文本 要和没个按钮一起显示的文本, 对于普通窗口, 这个参数表示显示在标题栏中得文本, 这里用来标识按钮样式
			WS_CHILD | WS_VISIBLE/*如果在创建子窗口时在窗口类中没有包括WS_VISIBLE, 子窗口将不会显示, 除非调用ShowWindow, 如果调用了WS_VISIBLE, 就无需调用ShowWindow, 不过, 可以调用ShowWindow(hwndChild, SW_HIDE)来隐藏这个窗口*/ | button[i].iStyle, // 窗口样式  禁用子窗口: EnableWindow(hwndChild, FALSE), 这样窗口会变成灰色的
			cxChar, cyChar * (1 + 2 * i), // 窗口坐标
			20 * cxChar, 7 * cyChar / 4, // 窗口宽高
			hwnd, // 父窗口句柄
			(HMENU)i, // 子窗口ID 此ID帮助窗口过程确认WM_COMMAND消息是从哪个子窗口发来的;
			((LPCREATESTRUCT)lParam)->hInstance,  // 案例句柄  在WM_CREATE消息里lParam实际上是一个指向CREATESTRUCT结构的指针, hInstance则是这个结构的一个成员;
			// 这里也可以使用GetWindowLong(hwnd, GWL_HINSTANCE);
			NULL);  // 额外参数
		return 0;

	case WM_SIZE:
		rect.left		= 24 * cxChar;
		rect.top		= 2  * cyChar;
		rect.right		= LOWORD(lParam);
		rect.bottom		= HIWORD(lParam);
		return 0;

	case WM_PAINT:
		InvalidateRect(hwnd, &rect, TRUE);

		hdc = BeginPaint(hwnd, &ps);
		SelectObject(hdc, GetStockObject(SYSTEM_FIXED_FONT));
		SetBkMode(hdc, TRANSPARENT);

		TextOut(hdc, 24 * cxChar, cyChar, szTop, lstrlen(szTop));
		TextOut(hdc, 24 * cxChar, cyChar, szUnd, lstrlen(szUnd));

		EndPaint(hwnd, &ps);
		return 0;

	case WM_DRAWITEM:
	case WM_COMMAND:  // LOWORD(wParam)  子窗口ID    HIWORD(wParam)  通知码    lParam  子窗口句柄
		ScrollWindow(hwnd, 0, -cyChar, &rect, &rect);

		hdc = GetDC(hwnd);
		SelectObject(hdc, GetStockObject(SYSTEM_FIXED_FONT));

		TextOut(hdc, 24 * cxChar, cyChar * (rect.bottom / cyChar - 1), 
				szBuffer, 
				wsprintf(szBuffer, szFormat, 
						 message == WM_DRAWITEM ? TEXT("WM_DRAWITEM") : 
												 TEXT("WM_COMMAND"), 
						HIWORD(wParam), LOWORD(wParam),
						HIWORD(lParam), LOWORD(lParam)));

		ReleaseDC(hwnd, hdc);
		ValidateRect(hwnd, &rect);
		break;
		
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}