#include <windows.h>
#include <stdlib.h>
#define PEEKMESSAGE
#define SZAPPNAME "p165PeekMessage.cpp"
#include "DX_WinMain.cpp"

HWND hwnd_DrawRectangle;
void DrawRectangle(HWND);
 
int cxClient, cyClient;

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)
	{
	case WM_CREATE:
		hwnd_DrawRectangle = hwnd;
		return 0;
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}

void PeekMessageInsertCode(void)
{
	DrawRectangle(hwnd_DrawRectangle);
}

void DrawRectangle(HWND hwnd)
{
	HBRUSH hBrush;
	HDC    hdc;
	RECT   rect;

	if (cxClient == 0 || cyClient == 0)
		return;

	SetRect(&rect, rand() % cxClient, rand() % cyClient, rand() % cxClient, rand() % cyClient);
	hBrush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
	hdc = GetDC(hwnd);

	FillRect(hdc, &rect, hBrush);
	ReleaseDC(hwnd, hdc);
	DeleteObject(hBrush);
}