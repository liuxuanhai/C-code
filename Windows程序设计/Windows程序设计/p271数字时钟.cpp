#define SZAPPNAME	"p271数字时钟"
#define ID_TIMER	1
#include			"DX_WinMain.cpp"

void DisplayDigit(HDC hdc, int iNumber)
{
	static BOOL	fSevenSegment[10][7] ={
				1, 1, 1, 0, 1, 1, 1,  // 0
				0, 0, 1, 0, 0, 1, 0,  // 1
				1, 0, 1, 1, 1, 0, 1,  // 2
				1, 0, 1, 1, 0, 1, 1,  // 3
				0, 1, 1, 1, 0, 1, 0,  // 4
				1, 1, 0, 1, 0, 1, 1,  // 5
				1, 1, 0, 1, 1, 1, 1,  // 6
				1, 0, 1, 0, 0, 1, 0,  // 7
				1, 1, 1, 1, 1, 1, 1,  // 8
				1, 1, 1, 1, 0, 1, 1	};// 9
	static POINT ptSegment[7][6] = {
		7, 6, 11, 2, 31, 2, 35, 6, 31, 10, 11, 10,
		6, 7, 10, 11, 10, 31, 6, 35, 2, 31, 2, 11,
		36, 7, 40, 11, 40, 31, 36, 35, 32, 31, 32, 11,
		7, 36, 11, 32, 31, 32, 35, 36, 31, 40, 11, 40,
		6, 37, 10, 41, 10, 61, 6, 65, 2, 61, 2, 41,
		36, 37, 40, 41, 40, 61, 36, 65, 32, 61, 32, 41,
		7, 66, 11, 62, 31, 62, 35, 66, 31, 70, 11, 70 };
	int iSeg;	
	for (iSeg = 0; iSeg < 7; iSeg++)
		if (fSevenSegment[iNumber][iSeg])
			Polygon(hdc, ptSegment[iSeg], 6);
}

void DisplayTwoDigits(HDC hdc, int iNumber, BOOL fSuppress)  // 画两个数字
{
	if (!fSuppress || (iNumber / 10 != 0))
		DisplayDigit(hdc, iNumber / 10);
	OffsetWindowOrgEx(hdc, -42, 0, NULL);  // 原点最初是最左边的数字的左上角, OffsetWindowOrgEx函数吧窗口的原点向右移动42个单位, 这样, 函数就能使用同样的坐标来画数字和冒号, 不管该图形在窗口的实际位置怎样;
	DisplayDigit(hdc, iNumber % 10);
	OffsetWindowOrgEx(hdc, -42, 0, NULL);
}

void DisplayColon(HDC hdc)  // 画冒号
{
	POINT ptColon[2][4] = {2, 21, 6, 17, 10, 21, 6, 25,
							2, 51, 6, 47, 10, 51, 6, 55};

	Polygon(hdc, ptColon[0], 4);
	Polygon(hdc, ptColon[1], 4);

	OffsetWindowOrgEx(hdc, -12, 0, NULL);
}

void DisplayTime(HDC hdc, BOOL f24Hour, BOOL fSuppress)
{
	SYSTEMTIME	st;

	GetLocalTime(&st);  // GetLocalTime获取本地时间, GetSystemTime给出世界时间(格林威治标准时间);

	if (f24Hour)
		DisplayTwoDigits(hdc, st.wHour, fSuppress);
	else
		DisplayTwoDigits(hdc, (st.wHour %= 12) ? st.wHour : 12, fSuppress);

	DisplayColon(hdc);
	DisplayTwoDigits(hdc, st.wMinute, FALSE);
	DisplayColon(hdc);
	DisplayTwoDigits(hdc, st.wSecond, FALSE);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static BOOL		f24Hour, fSuppress;
	static HBRUSH	hBrushRed;
	static int		cxClient, cyClient;
	HDC				hdc;
	PAINTSTRUCT		ps;
	TCHAR			szBuffer[2];  // szBuffer[1]用于保存'\0'

	switch (message)
	{
	case WM_CREATE:
		hBrushRed = CreateSolidBrush(RGB(255, 0, 0));
		SetTimer(hwnd, ID_TIMER, 1000, NULL);

												// fall through

	case WM_SETTINGCHANGE:  // 用户改变了任何系统设置

		// GetLocalInfo以字符串的形式返回所有信息
		GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_ITIME, szBuffer, 2);  // 确定是12小时或24小时格式
		f24Hour = (szBuffer[0] == '1');

		GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_ITLZERO, szBuffer, 2);  // 去掉小时开头为0的情况
		fSuppress = (szBuffer[0] == '0');

		InvalidateRect(hwnd, NULL, TRUE);
		return 0;

	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		return 0;

	case WM_TIMER:
		InvalidateRect(hwnd, NULL, TRUE);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		SetMapMode(hdc, MM_ISOTROPIC);  // 将映射模式改成MM_ISOTROPIC, 这样可以使用任意刻度的坐标轴, 该坐标轴在水平方向和垂直方向的刻度是相等的(刻度由SetWindowExtEx设置);
		// 调用SetWIndowExtEx函数时, 把参数设定为期望得到的逻辑窗口的逻辑大小;
		// 调用SetViewportExtEx函数, 把参数设定为实际的高度和宽度;
		SetWindowExtEx(hdc, 276, 72, NULL);	// 设置刻度, 水平276个单位, 垂直72个单位(由时钟数字的尺寸和间距决定);
												// 数字是42个单位宽, 冒号是12个单位宽, 6 * 42 + 12 * 2 = 276
		SetViewportExtEx(hdc, cxClient, cyClient, NULL);

		SetWindowOrgEx(hdc, 138, 36, NULL);  // 将窗口原点设置在(138, 36)处, 这是窗口区域的中心;
		SetViewportOrgEx(hdc, cxClient / 2, cyClient / 2, NULL);  // 设置视口原点为cxClient/2, cyClient/2, 这意味着时钟会显示在客户区的中央;
		SelectObject(hdc, hBrushRed);

		DisplayTime(hdc, f24Hour, fSuppress);

		EndPaint(hwnd, &ps);
		return 0;

	case WM_DESTROY:
		KillTimer(hwnd, ID_TIMER);
		DeleteObject(hBrushRed);
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}