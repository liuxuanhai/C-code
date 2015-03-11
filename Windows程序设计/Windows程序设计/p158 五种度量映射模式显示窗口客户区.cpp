#define SZAPPNAME "p158 五种度量模式显示窗口客户区.cpp"
#include "DX_WinMain.cpp"

void Show(HWND hwnd, HDC hdc, int xText, int yText, int iMapMode, TCHAR * szMapMode)
{
	TCHAR szBuffer[60];
	RECT  rect;

	SaveDC(hdc);  // idSaved = SavedDC(hdc);  保存设备环境
	SetMapMode(hdc, iMapMode);
	// 映射模式是设备环境属性的一部分, 所以只有使用以设备环境句柄作为参数的GDI函数才会使得映射模式生效
	GetClientRect(hwnd, &rect);  // 这里没有使用hdc, 所以他将继续以设备单位(像素)的形式执行;
	// rect.right是客户区的宽度, rect.bottom是客户区的高度;
	DPtoLP(hdc, (PPOINT)&rect, 2);  // 将设备单位转换成逻辑单位 待转换的点的个数是2 这里的2指的是有两个点即两对x, y
	RestoreDC(hdc, -1);  // RestoreDC(hdc, idSaved);  还原设备环境 -1使得设备环境还原到最近一次使用SaveDC函数保存的状态;

	TextOut(hdc, xText, yText, szBuffer, wsprintf(szBuffer, TEXT("%-20s %7d %7d %7d %7d"), szMapMode, rect.left, rect.right, rect.top, rect.bottom));
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static TCHAR szHeading[] = TEXT("        Mapping Mode      Left   Right    Top Bottom");
	static TCHAR szUndLine[] = TEXT("------------------------- --- ----------- --- ------");
	static int   cxChar, cyChar;
	HDC          hdc;
	PAINTSTRUCT  ps;
	TEXTMETRIC   tm;

	switch (message)
	{
	case WM_CREATE:
		hdc = GetDC(hwnd);

		SelectObject(hdc, GetStockObject(SYSTEM_FIXED_FONT));  // 使用等宽字体, windows3.0之前系统等宽字体是默认字体
		GetTextMetrics(hdc, &tm);
		cxChar = tm.tmAveCharWidth;
		cyChar = tm.tmHeight + tm.tmExternalLeading;

		ReleaseDC(hwnd, hdc);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		SelectObject(hdc, GetStockObject(SYSTEM_FIXED_FONT));
		// 只有MM_ISOTROPIC(各向同性)和MM_ANISOTROPIC(各向异性)两种模式允许改变视口和窗口范围;
		SetMapMode(hdc, MM_ANISOTROPIC);  // MM_ANISOTROPIC映射模式将轴上的逻辑单位设置为字号;
		SetWindowExtEx(hdc, 1, 1, NULL);
		SetViewportExtEx(hdc, cxChar, cyChar, NULL);

		TextOut(hdc, 1, 1, szHeading, lstrlen(szHeading));
		TextOut(hdc, 1, 2, szUndLine, lstrlen(szUndLine));

		Show(hwnd, hdc, 1, 3, MM_TEXT, TEXT("TEXT(pixes)"));
		Show(hwnd, hdc, 1, 4, MM_LOMETRIC, TEXT("LOMETRIC(.1 mm)"));
		Show(hwnd, hdc, 1, 5, MM_HIMETRIC, TEXT("HIMETRIC(.01 mm)"));
		Show(hwnd, hdc, 1, 6, MM_LOENGLISH, TEXT("LOENGLISH(.01 in)"));
		Show(hwnd, hdc, 1, 7, MM_HIENGLISH, TEXT("HIENGLISH(.001 in)"));
		Show(hwnd, hdc, 1, 8, MM_TWIPS, TEXT("TWIPS(1/1440 in)"));

		EndPaint(hwnd, &ps);

		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}