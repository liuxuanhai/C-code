#include <windows.h>
#include <math.h>

// 功能选择
#define 画正弦波
//#define 画网格
//#define 画一个矩形1
//#define 画一个矩形2

#define NUM 1000
#define TWOPI (2 * 3.14159)

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("p120绘制正弦波");
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
	static int  cxClient,cyClient;
	int         i;
	HDC         hdc;
	PAINTSTRUCT ps;
	POINT       apt[NUM];
	POINT arpt[5] = {100, 100, 200, 100, 200, 200, 100, 200, 100, 100};

	switch (message)
	{
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		return 0;

	// 画正弦波
	// 通过绘制几百条极短的线条来绘制一条复杂的正弦波, 如果线条足够短, 足够多, 那么把它们连接在一起看起来就像是一条曲线.
#ifdef 画正弦波
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		MoveToEx(hdc, 0, cyClient / 2, NULL);  // 设定当前位置, NULL参数表示不保存之前的当前位置
		// 系统默认的是BLACK_PEN画笔
		LineTo(hdc, cxClient, cyClient / 2);   // 从当前位置(不包括)画直线移动到一个位置(包括)

		for (i = 0; i < NUM; i++)
		{
			apt[i].x = i * cxClient / NUM;  // i * (cxClient / NUM); 为了保证精度应该先乘后除
			apt[i].y =(int)((1 - sin((double)i/*如果这里不加上double的话i/num是小数但是类型转换成整形的话就是0了*/ / NUM * TWOPI)) * cyClient / 2);
			//apt[i].y = (int)(cyClient / 2 * (1 - sin(TWOPI * i / NUM))); 
		}

		Polyline(hdc, apt, NUM);

		EndPaint(hwnd, &ps);
		return 0;
#endif

	// 画网格
#ifdef 画网格
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		for (i = 0; i < cxClient; i += 100)
		{
			MoveToEx(hdc, i, 0, NULL);
			LineTo(hdc, i, cyClient);
		}
		for (i = 0; i < cyClient; i += 100)
		{
			MoveToEx(hdc, 0, i, NULL);
			LineTo(hdc, cxClient, i);  // 从当前位置(不包括当前位置)指定位置(包括指定位置)
		}
		EndPaint(hwnd, &ps);
		return 0;
#endif

	// 画一个矩形1
#ifdef 画一个矩形1
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		
		MoveToEx(hdc, arpt[0].x, arpt[0].y, NULL);
		for (i = 1; i < 5; i++)
			LineTo(hdc, arpt[i].x, arpt[i].y);

		EndPaint(hwnd, &ps);
		return 0;
#endif

	// 画一个矩形2
#ifdef 画一个矩形2
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		Polyline(hdc, arpt, 5);  // Polyline()函数并不使用和改变当前位置. 而PolylineTo()则使用和改变当前位置, 画完线后, 会将当前位置设置为最后一根线的终点.

		EndPaint(hwnd, &ps);
		return 0;
#endif

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}