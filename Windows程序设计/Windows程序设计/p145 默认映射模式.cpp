// ?????????????????????????????未完成?????????????????????????

// 默认映射模式 映射模式的设置 映射模式的查看
// 默认映射模式是MM_TEXT, 这种映射模式下, 逻辑单位和物理单位相同, 这允许我们直接以像素为单位操作;
#define SZAPPNAME "p145 默认映射模式.cpp"
#include "DX_WinMain.cpp"
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC         hdc;
	int         iMapMode;
	TCHAR       szBuffer[100];
	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		// 默认的WM_TEXT映射模式下, 逻辑单位是pixel;
		TextOut(hdc, 96, 96, TEXT("MM_TEXT: 96px, 96px"), lstrlen(TEXT("MM_TEXT: 96px, 96px")));

		// MM_LOENGLISH 低精度英制映射模式下, 逻辑单位是0.01in.;
		iMapMode = GetMapMode(hdc);
		SetMapMode(hdc, MM_LOENGLISH);
		TextOut(hdc, 100, -100, TEXT("MM_LOENGLISH: 100in., -100in."), lstrlen(TEXT("MM_LOENGLISH: 100in., -100in.")));
		SetMapMode(hdc, iMapMode);
		TextOut(hdc, 0, 0, szBuffer, wsprintf(szBuffer, TEXT("%d"), GetDeviceCaps(hdc, HORZRES) / GetDeviceCaps(hdc, HORZSIZE)));
		EndPaint(hwnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}