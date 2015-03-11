#define SZAPPNAME		"p215 文本编辑器的雏形"
#define BUFFER(x, y)	*(pBuffer + y * cxBuffer + x)
#include				"DX_WinMain.cpp"

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static DWORD	dwCharSet	= DEFAULT_CHARSET;
	static int		cxChar, cyChar, cxClient, cyClient, cxBuffer, cyBuffer, xCaret, yCaret;
	static TCHAR *	pBuffer		= NULL;

	HDC				hdc;
	int				x, y, i;
	PAINTSTRUCT		ps;
	TEXTMETRIC		tm;

	switch (message)
	{
	case WM_INPUTLANGCHANGE:  // 只要你使用桌面通知区域的弹出菜单改变了键盘布局, windows就会把WM_INPUTLANGCHANGE消息传递给你的窗口过程
		dwCharSet = wParam;
		
	case WM_CREATE:
		hdc = GetDC(hwnd);

		SelectObject(hdc, CreateFont(0, 0, 0, 0, 0, 0, 0, 0, 
			dwCharSet, 0, 0, 0, FIXED_PITCH, NULL));

		GetTextMetrics(hdc, &tm);
		cxChar = tm.tmAveCharWidth;
		cyChar = tm.tmHeight;

		DeleteObject(SelectObject(hdc, GetStockObject(SYSTEM_FONT)));
		ReleaseDC(hwnd, hdc);

	case WM_SIZE:

								// 获取屏幕像素大小

		if (message == WM_SIZE)
		{
			cxClient = LOWORD(lParam);
			cyClient = HIWORD(lParam);
		}

		cxBuffer = max(1, cxClient / cxChar);  // 客户区可以保存的等宽字体列数
		cyBuffer = max(1, cyClient / cyChar);  // 客户区可以保存的等宽字体行数

								// 给Buffer数组分配内存

		if (pBuffer != NULL)
			free(pBuffer);

		pBuffer = (TCHAR *)malloc(cxBuffer * cyBuffer * sizeof(TCHAR));

		for (y = 0; y < cyBuffer; y++)
			for (x = 0; x < cxBuffer; x++)
				BUFFER(x, y) = '_';

								// 设置插入符号

		xCaret = 0;
		yCaret = 0;

		if (hwnd == GetFocus())  // 获取输入焦点窗口
			SetCaretPos(xCaret * cxChar, cyChar * yCaret);  // 设置插入符号位置

		InvalidateRect(hwnd, NULL, TRUE);
		return 0;

	case WM_SETFOCUS:
								// 创建和显示插入符号

		CreateCaret(hwnd, NULL, cxChar, cyChar);
		SetCaretPos(xCaret * cxChar, yCaret * cyChar);
		ShowCaret(hwnd);

		return 0;

	case WM_KILLFOCUS:
								// 隐藏和销毁插入符号

		HideCaret(hwnd);
		DestroyCaret();
		return 0;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_HOME:
			xCaret = 0;
			break;

		case VK_END:
			xCaret = cxBuffer - 1;
			break;

		case VK_PRIOR:
			yCaret = 0;
			break;

		case VK_NEXT:
			yCaret = cyBuffer - 1;
			break;

		case VK_LEFT:
			xCaret = max(xCaret - 1, 0);
			break;

		case VK_RIGHT:
			xCaret = min(xCaret + 1, cxBuffer - 1);
			break;

		case VK_UP:
			yCaret = max(yCaret - 1, 0);
			break;

		case VK_DOWN:
			yCaret = max(yCaret + 1, cyBuffer - 1);
			break;

		case VK_DELETE:
			for (x = xCaret; x < cxBuffer - 1; x++)
				BUFFER(x, yCaret) = BUFFER(x + 1, yCaret);

			BUFFER(cxBuffer - 1, yCaret) = 'L';
			
			HideCaret(hwnd);
			hdc = GetDC(hwnd);

			SelectObject(hdc, CreateFont(0, 0, 0, 0, 0, 0, 0, 0,
				dwCharSet, 0, 0, 0, FIXED_PITCH, NULL));
			TextOut(hdc, xCaret * cxChar, yCaret * cyChar, &BUFFER(xCaret, yCaret), cxBuffer - xCaret);
			
			DeleteObject(SelectObject(hdc, GetStockObject(SYSTEM_FONT)));
			ReleaseDC(hwnd, hdc);
			ShowCaret(hwnd);
			break;
		}
		SetCaretPos(xCaret * cxChar, yCaret * cyChar);
		return 0;

	case WM_CHAR:
		for (i = 0; i < (int)LOWORD(lParam); i++)
		{
			switch (wParam)
			{
			case '\b':
				if (xCaret > 0)
				{
					xCaret--;
					SendMessage(hwnd, WM_KEYDOWN, VK_DELETE, 1);
				}
				break;

			case '\t':
				do
				{
					SendMessage(hwnd, WM_CHAR, ' ', 1);
				}while (xCaret % 8 != 0);

			case '\n':
				if (++yCaret == cyBuffer)
					yCaret = 0;
				break;
				
			case '\r':
				xCaret = 0;
				if (++yCaret == cyBuffer)
					yCaret = 0;
				break;

			case '\x1B':  // escape
				for (y = 0; y < cyBuffer; y++)
					for (x = 0; x < cxBuffer; x++)
						BUFFER(x, y) = ' ';

				xCaret = 0;
				yCaret = 0;

				InvalidateRect(hwnd, NULL, FALSE);  // FALSE????? 使得整个客户区无效, 但是不允许用背景画刷涂掉原来的数据, 直接写新的;
				break;

			default:  // character codes
				BUFFER(xCaret, yCaret) = (TCHAR)wParam;

				HideCaret(hwnd);  // 如果窗口过程处理的是一个非WM_PAINT消息, 但是要在窗口中绘制某些东西的时候, 必须调用HideCaret隐藏插入符号, 当他在窗口内的绘制结束后再调用ShowCaret来显示插入符号.
				hdc = GetDC(hwnd);
				SelectObject(hdc, CreateFont(0, 0, 0, 0, 0, 0, 0, 0,
					dwCharSet, 0, 0, 0, FIXED_PITCH, NULL));
				TextOut(hdc, xCaret * cxChar, yCaret * cyChar, &BUFFER(xCaret, yCaret), 1);

				DeleteObject(SelectObject(hdc, GetStockObject(SYSTEM_FONT)));
				ReleaseDC(hwnd, hdc);
				ShowCaret(hwnd);

				if (++xCaret == cxBuffer)
				{
					xCaret = 0;
					if (++yCaret == cxBuffer)
						yCaret = 0;
				}
				break;
			}
		}
		SetCaretPos(xCaret * cxChar, yCaret * cyChar);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		SelectObject(hdc, CreateFont(0, 0, 0, 0, 0, 0, 0, 0,
			dwCharSet, 0, 0, 0, FIXED_PITCH, NULL));

		for (y = 0; y < cyBuffer; y++)
			TextOut(hdc, 0, y * cyChar, &BUFFER(0, y), cxBuffer);
			
		DeleteObject(SelectObject(hdc, GetStockObject(SYSTEM_FONT)));
		EndPaint(hwnd, &ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}