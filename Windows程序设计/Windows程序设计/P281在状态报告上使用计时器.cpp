#include <windows.h>
#define  ID_TIMER	1

void FindWindowSize(int *, int *);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	static TCHAR	szAppName[] = TEXT("p281在状态报告上使用计时器");
	HWND			hwnd;
	int				cxWindow, cyWindow;
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

	FindWindowSize(&cxWindow, &cyWindow);

	hwnd = CreateWindow(szAppName, szAppName, 
						WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_BORDER/*固定大小的窗口*/,
						CW_USEDEFAULT, CW_USEDEFAULT, cxWindow, cyWindow,
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

void FindWindowSize(int * pcxWindow, int * pcyWindow)
{
	HDC			hdcScreen;
	TEXTMETRIC	tm;

	hdcScreen = CreateIC(TEXT("DISPLAY"), NULL, NULL, NULL);  // 从视频显示设备获取一个信息设备环境
	GetTextMetrics(hdcScreen, &tm);  // 获取文本的大小
	DeleteDC(hdcScreen);

	*pcxWindow = 2 * GetSystemMetrics(SM_CXBORDER)/*获取左右边框的宽度的像素数*/ + 12 * tm.tmAveCharWidth;
	*pcyWindow = 2 * GetSystemMetrics(SM_CYBORDER)/*获取上下边框的厚度的像素数*/ + GetSystemMetrics(SM_CYCAPTION)/*获取标题栏厚度*/ + 2 * tm.tmHeight;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static COLORREF		cr, crLast;
	static HDC			hdcScreen;
	HDC					hdc;
	PAINTSTRUCT			ps;
	POINT				pt;
	RECT				rc;
	TCHAR				szBuffer[16];

	switch (message)
	{
	case WM_CREATE:
		hdcScreen = CreateDC(TEXT("DISPLAY"), NULL, NULL, NULL);  // 为整个视频显示创建一个设备环境
		
		SetTimer(hwnd, ID_TIMER, 100, NULL);
		return 0;

	case WM_TIMER:
		GetCursorPos(&pt);  // 获取鼠标当前位置
		cr = GetPixel(hdcScreen, pt.x, pt.y);  // 获得当前鼠标位置的像素颜色
		//TextOut(hdcScreen, 100, 100, TEXT("daxionggege"), lstrlen(TEXT("daxionggege")));

		//SetPixel(hdcScreen, pt.x, pt.y, 0);  // 画一个点  你说贱不贱, 刚刚得到这个点的颜色, 他立马给你涂黑, 真贱

		if (cr != crLast)
		{
			crLast = cr;
			InvalidateRect(hwnd, NULL, FALSE);  // 这里虽然写的是FALSE, 但是由于绘图模式是不透明的, 所以文本中的白色会把原来的字给覆盖掉
		}

		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		GetClientRect(hwnd, &rc);

		wsprintf(szBuffer, TEXT("  %02X %02X %02X   "), GetRValue(cr), GetGValue(cr), GetBValue(cr));
		DrawText(hdc, szBuffer, -1, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

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