#define SZAPPNAME	"p146 逻辑点位于中心的正弦曲线"
#include "DX_WinMain.cpp"
#include <cmath>
#define	TWO_PI		(3.1415926 * 2)
#define NUM			500

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	static	int		cxClient, cyClient;
	HDC				hdc;
	PAINTSTRUCT		ps;


	switch (iMsg)
	{
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		// 设置逻辑原点
		SetWindowOrgEx(hdc, -cxClient / 2, -cyClient / 2, NULL);
		MoveToEx(hdc, 0, 0, NULL);
		int i;
		for (i = 0; i < NUM; i++)
			LineTo(hdc, cxClient * i / 2 / NUM, (int)(sin(TWO_PI * i / NUM) * cyClient / 2));

		EndPaint(hwnd, &ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}