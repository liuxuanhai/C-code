#include <math.h>
#define SZAPPNAME "p120 绘制正弦波"
#include "DX_WinMain.cpp"
#define POLYLINE  // POLYLINE 或 LINETO
#define NUM 1000
#define TWOPI (2 * 3.14159)

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int cxClient, cyClient;
	int i;
	HDC hdc;
	PAINTSTRUCT ps;
	POINT apt[NUM];
	
	switch (message)
	{
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		MoveToEx(hdc, 0, cyClient / 2, NULL);
		LineTo(hdc, cxClient, cyClient / 2);
		MoveToEx(hdc, 0, cyClient / 2, NULL);
		for (i = 0; i < NUM; i++)
		{
			apt[i].x = i * cxClient / NUM;
			apt[i].y =(int)((1 - sin((double)i/*如果这里不加上double的话i/num是小数但是类型转换成整形的话就是0了*/ / NUM * TWOPI)) * cyClient / 2);
#if defined LINETO
			LineTo(hdc, apt[i].x, apt[i].y);
		}
#elif defined POLYLINE
		}
		Polyline(hdc, apt, NUM);  // 因为Polyline函数是在设备驱动程序的层次上实现的, 所以这比调用1000次LineTo函数要快;
#endif
		EndPaint(hwnd, &ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}