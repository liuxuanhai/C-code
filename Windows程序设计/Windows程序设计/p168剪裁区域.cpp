#include <math.h>
#define SZAPPNAME "p168裁剪区域"
#define TWO_PI (2.0 * 3.1415926)
#include "DX_WinMain.cpp"

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	static HRGN hRgnClib;
	static int  cxClient, cyClient;
	double      fAngle/*角度*/, fRadius/*半径 从中心到客户区角落的距离*/;
	HCURSOR     hCursor;
	HDC         hdc;
	HRGN        hRgnTemp[6];
	int         i;
	PAINTSTRUCT ps;

	switch (iMsg)
	{
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);

		hCursor = SetCursor(LoadCursor(NULL, IDC_WAIT));
		ShowCursor(TRUE);

		if (hRgnClib)
			DeleteObject(hRgnClib);

		// 创建四个团员区域, 三个空区域
		hRgnTemp[0] = CreateEllipticRgn(0, cyClient / 3, cxClient / 2, 2 * cyClient / 3);  // 左 上 右 下
		hRgnTemp[1] = CreateEllipticRgn(cxClient / 2, cyClient / 3, cxClient, 2 * cyClient / 3);
		hRgnTemp[2] = CreateEllipticRgn(cxClient / 3, 0, 2 * cxClient / 3, cyClient / 2);
		hRgnTemp[3] = CreateEllipticRgn(cxClient / 3, cyClient / 2, 2 * cxClient / 3, cyClient);
		hRgnTemp[4] = CreateRectRgn(0, 0, 1, 1);
		hRgnTemp[5] = CreateRectRgn(0, 0, 1, 1);
		hRgnClib    = CreateRectRgn(0, 0, 1, 1);

		CombineRgn(hRgnTemp[4], hRgnTemp[0], hRgnTemp[1], RGN_OR);  // 客户区的左边和右边的两个椭圆合并 
		CombineRgn(hRgnTemp[5], hRgnTemp[2], hRgnTemp[3], RGN_OR);  // 上下 RGN_OR 全部合并
		CombineRgn(hRgnClib,    hRgnTemp[4], hRgnTemp[5], RGN_XOR); // RGN_XOR 除去公共部分的全部合并 排除重叠

		for (i = 0; i < 6; i++)
			DeleteObject(hRgnTemp[i]);
		SetCursor(hCursor);
		ShowCursor(FALSE);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		SetViewportOrgEx(hdc, cxClient / 2, cyClient / 2, NULL);  // 将视口原点设置在客户区中心(这样使得画直线更容易)
		SelectClipRgn(hdc, hRgnClib);  // 创建的区域被选入设备环境作为剪裁区域

		fRadius = _hypot(cxClient / 2.0, cyClient / 2.0);

		for (fAngle = 0.0; fAngle < TWO_PI; fAngle += TWO_PI / 360)  // 一共画360条, 每一度画一条
		{
			MoveToEx(hdc, 0, 0, NULL);
			LineTo(hdc, (int)(fRadius * cos(fAngle) + 0.5), (int)(-fRadius * sin(fAngle) + 0.5));
		}

		EndPaint(hwnd, &ps);
		return 0;

	case WM_DESTROY:
		DeleteObject(hRgnClib);
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}