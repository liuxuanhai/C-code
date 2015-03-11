#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
				   PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("p128 贝塞尔样条曲线");
	HWND         hwnd;
	MSG			 msg;
	WNDCLASS     wndclass;

	wndclass.hbrBackground  = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.cbClsExtra     = 0;
	wndclass.cbWndExtra     = 0;
	wndclass.hCursor        = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon          = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hInstance      = hInstance;
	wndclass.lpfnWndProc    = WndProc;
	wndclass.lpszClassName  = szAppName;
	wndclass.lpszMenuName   = NULL;
	wndclass.style          = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("Windows 7 is needed!"),
					TEXT("Error"), MB_OK | MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(szAppName, TEXT("Bezier Splines"),
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

	return msg.wParam;
}

void DrawBezier(HDC hdc, POINT apt[])
{
	PolyBezier(hdc, apt, 4);

	MoveToEx(hdc, apt[0].x,apt[0].y, NULL);
	LineTo(hdc, apt[1].x, apt[1].y);

	MoveToEx(hdc, apt[2].x, apt[2].y, NULL);
	LineTo(hdc, apt[3].x, apt[3].y);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static POINT apt[4];
	HDC          hdc;
	int          cxClient, cyClient;
	PAINTSTRUCT  ps;

	switch (message)
	{
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);

		apt[0].x  = cxClient / 4;  // 起点
		apt[0].y  = cyClient / 2;

		apt[1].x = cxClient / 2;  // 第一个控点的起始位置
		apt[1].y = cyClient / 4;

		apt[2].x = cxClient / 2;  // 第二个控点的起始位置
		apt[2].y = 3 * cyClient / 4;

		apt[3].x = 3 * cxClient / 4;
		apt[3].y = cyClient / 2;  // 终点

		return 0;

	// 对于鼠标消息, wParam是鼠标动作, lParam是鼠标位置;
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_MOUSEMOVE:  // 此消息确保 拖动控点 的实现
		if (wParam & MK_LBUTTON || wParam & MK_RBUTTON)
		{
			hdc = GetDC(hwnd);

			// 确保轨迹不会被绘制(白线重描原来位置)
			SelectObject(hdc, GetStockObject(WHITE_PEN));  // GetStockObject(WHITE_PEN) 返回画笔的句柄 SelectObject(hdc, hPen) 将画笔选入设备环境 它返回先前选入设备环境的画笔的句柄
			DrawBezier(hdc, apt);  // 这里照着原来的线又重新绘制了一遍, 只不过这一次用的是白线, 所以好像擦除了原来的线似的;

			if (wParam & MK_LBUTTON)
			{
				apt[1].x = LOWORD(lParam);  // 将鼠标位置保存下来
				apt[1].y = HIWORD(lParam);
			}

			if (wParam & MK_RBUTTON)
			{
				apt[2].x = LOWORD(lParam);
				apt[2].y = HIWORD(lParam);
			}

			// 黑线绘制新位置
			SelectObject(hdc, GetStockObject(BLACK_PEN));
			DrawBezier(hdc, apt);

			ReleaseDC(hwnd, hdc);
		}
		return 0;

	case WM_PAINT:
		InvalidateRect(hwnd, NULL, TRUE);  // 这个指令是干什么用的啊????
		hdc = BeginPaint(hwnd, &ps);
		
		DrawBezier(hdc, apt);

		EndPaint(hwnd, &ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}