// . 填充函数使用设备环境句柄中的当前画刷来填充区域, 但是至于内部是怎么填充的, 要取决于多边形的填充模式, 可以调用SetPolyFillMode(hdc, iMode)来设置;
// . 默认情况下, 多边形的填充模式是ALTERNATE(交替), 但是也可以设定为WINDING(螺旋).
// . ALTERNATE: 从一个封闭区域中的一个点向无穷远处画一条射线, 只有该射线穿越奇数条边框线的时候, 封闭区域才会被填充.
// . WINDING:   从一个封闭区域中的一个点向无穷远处画一条射线, 只有该射线穿越奇数条边框线的时候, 封闭区域才会被填充. 而穿越偶数个边框的时候, 如果不同方向的边框线条数不相同, 则区域会被填充, 如果相同, 则不会被填充.
#define SZAPPNAME "p140绘制填充区域"
#include "DX_WinMain.cpp"

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static POINT aptFigure[10] = {10, 70, 50, 70, 50, 10, 90, 10, 90, 50, 30, 50, 30, 90, 70, 90, 70, 30, 10, 30};
	static int cxClient, cyClient;
	HDC  hdc;
	int  i;
	PAINTSTRUCT ps;
	POINT apt[10];

	switch (message)
	{
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		SelectObject(hdc, GetStockObject(GRAY_BRUSH));  // 设置灰色画刷

		for (i = 0; i < 10; i++)
		{
			apt[i].x = cxClient * aptFigure[i].x / 200;
			apt[i].y = cyClient * aptFigure[i].y / 100;
		}

		SetPolyFillMode(hdc, ALTERNATE);
		Polygon(hdc, apt, 10);

		for (i = 0; i < 10; i++)
		{
			apt[i].x += cxClient / 2;
		}
		SetPolyFillMode(hdc, WINDING);
		Polygon(hdc, apt, 10);

		EndPaint(hwnd, &ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}