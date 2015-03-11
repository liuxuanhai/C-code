#define SZAPPNAME "p193八种不同键盘消息"
#include "DX_WinMain.cpp"

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int cxClient, cyClient, cxClientMax, cyClientMax, cxChar, cyChar;
	static int cLinesMax, cLines;
	static PMSG pmsg;  
	static RECT rectScroll;
	static TCHAR szTop[] = TEXT("Message        Key       Char     Repeat Scan Ext ALT Prev Tran");
	static TCHAR szUnd[] = TEXT("_______        ___       ____     ______ ____ ___ ___ ____ ____");
	static TCHAR * szFormat[2] = {
		TEXT("%-13s %3d %-15s%c%6u %4d %3s %3s %4s %4s"),
		TEXT("%-13s            0x%04X%1s%c %6u %4d %3s %3s %4s %4s")};
	static TCHAR * szYes    = TEXT("Yes");
	static TCHAR * szNo     = TEXT("No");
	static TCHAR * szDown   = TEXT("Down");
	static TCHAR * szUp     = TEXT("Up");

	static TCHAR * szMessage[] = {
		TEXT("WM_KEYDOWN"), TEXT("WM_KEYUP"),
		TEXT("WM_CHAR"), TEXT("WM_DEADCHAR"),
		TEXT("WM_SYSKEYDOWN"), TEXT("WM_SYSKEYUP"),
		TEXT("WM_SYSCHAR"), TEXT("WM_SYSDEADCHAR")};
	HDC			hdc;
	int			i, iType;
	PAINTSTRUCT ps;
	TCHAR		szBuffer[128], szKeyName[32];
	TEXTMETRIC  tm;

	switch (message)
	{
	case WM_CREATE:
	case WM_DISPLAYCHANGE:  // 如果用户在程序运行的时候调整视频显示的大小, 程序会收到一个WM_DISPLAYCHANGE消息
		
			// Get maximum size of client area

		cxClientMax = GetSystemMetrics(SM_CXMAXIMIZED);
		cyClientMax = GetSystemMetrics(SM_CYMAXIMIZED);

			// Get character size for fixed-pitch font     // pitch 倾斜

		hdc = GetDC(hwnd);

		SelectObject(hdc, GetStockObject(SYSTEM_FIXED_FONT));  // 等宽字体
		GetTextMetrics(hdc, &tm);
		cxChar = tm.tmAveCharWidth;
		cyChar = tm.tmHeight;
		
		ReleaseDC(hwnd, hdc);

			// Allocate memory for display lines

		if (pmsg)
			free(pmsg);

		cLinesMax = cyClientMax / cyChar;
		pmsg = (PMSG)malloc(cLinesMax * sizeof(MSG)); // 将每一条消息储存在MSG结构数组中 数组的大小基于最大化窗口的大小和等宽的系统字体.
		cLines = 0;

		return 0;

			// fall through

	case WM_SIZE:
		if (message == WM_SIZE)
		{
			cxClient = LOWORD(lParam);
			cyClient = HIWORD(lParam);
		}

			// Calculate scrolling rectangle

		rectScroll.left   = 0;
		rectScroll.right  = cxClient;
		rectScroll.top    = cyChar;
		rectScroll.bottom = cyChar * (cyClient / cyChar);

		InvalidateRect(hwnd, NULL, TRUE);
		return 0;

	case WM_KEYDOWN:
	case WM_KEYUP:
	case WM_CHAR:
	case WM_DEADCHAR:
	case WM_SYSKEYDOWN:
	case WM_SYSKEYUP:
	case WM_SYSCHAR:
	case WM_SYSDEADCHAR:
			
			// Rearrange storage array

		for (i = cLinesMax - 1; i > 0; i--)
		{
			pmsg[i] = pmsg[i - 1];
		}

			// Store new message

		pmsg[0].hwnd       = hwnd;
		pmsg[0].message    = message;
		pmsg[0].wParam     = wParam;
		pmsg[0].lParam     = lParam;

		cLines = min(cLines + 1, cLinesMax);

				// Scroll up the display

		ScrollWindow(hwnd, 0, -cyChar, &rectScroll, &rectScroll);

		break;  // i.e., call DefWindowProc so Sys message work

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		SelectObject(hdc, GetStockObject(SYSTEM_FIXED_FONT));
		SetBkMode(hdc, TRANSPARENT);  // 如果选择的是OPAQUE的话那么下面的第一个TextOut显示的内容就没了???????  因为这两个TextOut在一行显示, 所以如果不透明的话后面的会把前面的挡住
		TextOut(hdc, 0, 0, szTop, lstrlen(szTop));
		TextOut(hdc, 0, 0, szUnd, lstrlen(szUnd));

		for (i = 0; i < min(cLines, cyClient / cyChar - 1); i++)
		{
			iType = pmsg[i].message == WM_CHAR ||
					 pmsg[i].message == WM_SYSCHAR ||
					 pmsg[i].message == WM_DEADCHAR ||
					 pmsg[i].message == WM_SYSDEADCHAR;
			GetKeyNameText(pmsg[i].lParam, szKeyName, sizeof(szKeyName) / sizeof(TCHAR));  // 虚拟键代码和键名称

			TextOut(hdc, 0, (cyClient / cyChar - 1 - i) * cyChar, szBuffer, 
				wsprintf(szBuffer, szFormat[iType], szMessage[pmsg[i].message - WM_KEYFIRST],
				pmsg[i].wParam, (PTSTR)(iType ? TEXT(" ") : szKeyName), (TCHAR)(iType ? pmsg[i].wParam : ' '),
				LOWORD(pmsg[i].lParam), HIWORD(pmsg[i].lParam) & 0xFF,
				0x01000000 & pmsg[i].lParam ? szYes : szNo,
				0x20000000 & pmsg[i].lParam ? szYes : szNo,
				0x40000000 & pmsg[i].lParam ? szDown : szUp,
				0x80000000 & pmsg[i].lParam ? szUp : szDown));
		}

		EndPaint(hwnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}