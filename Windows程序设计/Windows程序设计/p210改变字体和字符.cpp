#define		SZAPPNAME	"p210改变字体和字符"
#include	"DX_WinMain.cpp"

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static	DWORD	dwCharSet		=	DEFAULT_CHARSET;
	static	int		cxClientMax, cyClientMax, cxClient, cyClient, cxChar, cyChar;
	static	int		cLinesMax, cLines;
	static	PMSG	pmsg;
	static	RECT	rectScroll;
	static	TCHAR	szTop[] = TEXT("Message        Key       Char     Repeat Scan Ext ALT Prev Tran");
	static	TCHAR	szUnd[] = TEXT("_______        ___       ____     ______ ____ ___ ___ ____ ____");
	static	TCHAR * szFormat[2] = {
		TEXT("%-13s %3d %-15s%c%6u %4d %3s %3s %4s %4s"),
		TEXT("%-13s            0x%04X%1s%c %6u %4d %3s %3s %4s %4s")};
	static	TCHAR * szYes    = TEXT("Yes");
	static	TCHAR * szNo     = TEXT("No");
	static	TCHAR * szDown   = TEXT("Down");
	static	TCHAR * szUp     = TEXT("Up");

	static	TCHAR * szMessage[] = {
		TEXT("WM_KEYDOWN"), TEXT("WM_KEYUP"),
		TEXT("WM_CHAR"), TEXT("WM_DEADCHAR"),
		TEXT("WM_SYSKEYDOWN"), TEXT("WM_SYSKEYUP"),
		TEXT("WM_SYSCHAR"), TEXT("WM_SYSDEADCHAR")};
	HDC				hdc;
	int				i, iType;
	PAINTSTRUCT		ps;
	TCHAR			szBuffer[128], szKeyName[32];
	TEXTMETRIC		tm;
	switch (message)
	{
	case WM_INPUTLANGCHANGE:  // 只要使用桌面通知区域的弹出菜单改变了键盘布局, windows就会吧WM_INPUTLANCHANGE消息传递给你的窗口过程, 相应的wParam消息参数是新建盘布局的字符集ID;
		dwCharSet	=	wParam;

	case WM_CREATE:
	case WM_DISPLAYCHANGE:

								// 获取屏幕大小

		cxClientMax = GetSystemMetrics(SM_CXMAXIMIZED);
		cyClientMax = GetSystemMetrics(SM_CYMAXIMIZED);

								// 获取等宽字体大小

		hdc = GetDC(hwnd);
		SelectObject(hdc, CreateFont(0, 0, 0, 0, 0, 0, 0, 0,  // 第九个参数设置使用的字符集 p209CreateFont中使用的字符集.jpg
									dwCharSet, 0, 0, 0, FIXED_PITCH, NULL));  // 第十三个参数设置了等宽字体

		GetTextMetrics(hdc, &tm);
		cxChar = tm.tmAveCharWidth;
		cyChar = tm.tmHeight;

		DeleteObject(SelectObject(hdc, GetStockObject(SYSTEM_FONT)));
		ReleaseDC(hwnd, hdc);

								// 为输出每行的信息分配内存空间

		if (pmsg)
			free(pmsg);

		cLinesMax	= cyClientMax / cyChar;  // 最多输出多少行
		pmsg		= (MSG *)malloc(cLinesMax * sizeof(MSG));
		cLines		= 0;

	case WM_SIZE:
		if (message == WM_SIZE)
		{
			cxClient = LOWORD(lParam);
			cyClient = HIWORD(lParam);
		}

								// 计算滚动矩形

		rectScroll.left	= 0;
		rectScroll.right	= cxClient;
		rectScroll.top		= cyChar;
		rectScroll.bottom	= cyChar * (cyClient / cyChar);

		InvalidateRect(hwnd, NULL, TRUE);

		if (message == WM_INPUTLANGCHANGE)
			return TRUE;

		return 0;

	case WM_KEYDOWN:
	case WM_KEYUP:
	case WM_CHAR:
	case WM_DEADCHAR:
	case WM_SYSKEYDOWN:
	case WM_SYSKEYUP:
	case WM_SYSCHAR:
	case WM_SYSDEADCHAR:

								// 信息数组移位添加新信息

		for (i = cLinesMax - 1; i > 0; i--)
			pmsg[i]		= pmsg[i - 1];
		pmsg[0].hwnd	= hwnd;
		pmsg[0].message = message;
		pmsg[0].wParam	= wParam;
		pmsg[0].lParam	= lParam;

		cLines = min(cLines + 1, cLinesMax);

								// 滚动输出

		ScrollWindow(hwnd, 0, -cyChar, &rectScroll, &rectScroll);
		break;	// 仍然需要DefWindowsProc, 这样Sys message才能正常工作;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		SelectObject(hdc, CreateFont(0, 0, 0, 0, 0, 0, 0, 0,
			dwCharSet, 0, 0, 0, FIXED_PITCH, NULL));

		SetBkMode(hdc, TRANSPARENT);
		TextOut(hdc, 0, 0, szTop, lstrlen(szTop));
		TextOut(hdc, 0, 0, szUnd, lstrlen(szUnd));

		for (i = 0; i < min(cLines, cyClient / cyChar - 1); i++)
		{
			iType	=	pmsg[i].message == WM_CHAR		||
						pmsg[i].message == WM_SYSCHAR	||
						pmsg[i].message == WM_DEADCHAR	||
						pmsg[i].message == WM_SYSDEADCHAR;

			GetKeyNameText(pmsg[i].lParam, szKeyName, sizeof szKeyName / sizeof(TCHAR));
			TextOut(hdc, 0, (cyClient / cyChar - 1 - i) * cyChar, szBuffer,
				wsprintf(szBuffer, szFormat[iType], szMessage[pmsg[i].message - WM_KEYFIRST], 
				pmsg[i].wParam, 
				(PTSTR)(iType ? TEXT("") : szKeyName),
				(TCHAR)(iType ? pmsg[i].wParam : ' '),
				LOWORD(pmsg[i].lParam),
				HIWORD(pmsg[i].lParam) & 0xFF,
				0x01000000 & pmsg[i].lParam ? szYes	: szNo,
				0x20000000 & pmsg[i].lParam ? szYes	: szNo,
				0x40000000 & pmsg[i].lParam ? szDown	: szUp,
				0x80000000 & pmsg[i].lParam ? szUp		: szDown));
		}
		DeleteObject(SelectObject(hdc, GetStockObject(SYSTEM_FONT)));
		EndPaint(hwnd, &ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}