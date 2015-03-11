#define SZAPPNAME "p125 ªÊ÷∆Õº–Œ"
#include "DX_WinMain.cpp"
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int cxClient, cyClient;
	HDC    hdc;
	PAINTSTRUCT ps;

	switch (message)
	{
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		Rectangle(
hdc, cxClient / 8, cyClient / 8, cxClient * 7 / 8, cyClient * 7 / 8);
		MoveToEx(hdc, 0, 0, NULL);
		LineTo(hdc, cxClient, cyClient);
		Ellipse(hdc, cxClient / 8, cyClient / 8, cxClient * 7 / 8, cyClient * 7 / 8);
		RoundRect(hdc, cxClient / 4, cyClient / 4, cxClient * 3 / 4, cyClient * 3 / 4, cxClient / 4, cyClient / 4);

		MoveToEx(hdc, cxClient, 0, NULL);
		LineTo(hdc, 0, cyClient);

		EndPaint(hwnd, &ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}