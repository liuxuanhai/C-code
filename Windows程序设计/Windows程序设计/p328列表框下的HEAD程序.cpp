#define SZAPPNAME	"p328列表框下的HEAD程序"
#define CHANGEWNDCLASS
#define CHANGECREATEWINDOW
#define ID_LIST		1
#define ID_TEXT		2
#define MAXREAD		8129
#define DIRATTR		(DDL_READWRITE/*普通文件*/ | DDL_READONLY/*只读文件*/ | DDL_HIDDEN/*隐藏文件*/ | DDL_SYSTEM/*系统文件*/ | DDL_DIRECTORY/*子目录*/ | DDL_ARCHIVE/*设置了存档位的文件*/ | DDL_DRIVES/*包括驱动器字符*/)  /*DDL_EXCLUSIVE 只搜索指定的值*/ /*DDL: dialog directory list(对话框目录列表)*/
#define DTFLAGS		(DT_WORDBREAK | DT_EXPANDTABS | DT_NOCLIP | DT_NOPREFIX)
#include			"DX_WinMain.cpp"

WNDPROC OldList;

void ChangeWndClass(WNDCLASS * wndclass)
{
	wndclass->hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
}

HWND ChangeCreateWindow(HINSTANCE hInstance)
{
	return CreateWindow(TEXT(SZAPPNAME), TEXT(SZAPPNAME), WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
}

LRESULT CALLBACK ListProc(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static BOOL		bValidFile;
	static BYTE		buffer[MAXREAD];  // 用于保存文件中的内容
	static HWND		hwndList, hwndText;
	static TCHAR	szFile[MAX_PATH + 1];
	static RECT		rect;  // 用来显示文件的内容的区域
	HANDLE			hFile;
	HDC				hdc;
	int				i, cxChar, cyChar;
	PAINTSTRUCT		ps;
	TCHAR			szBuffer[MAX_PATH + 1];  // 用于保存当前目录或文件名或目录加文件名等等

	switch (message)
	{
	case WM_CREATE:
		cxChar = LOWORD(GetDialogBaseUnits());
		cyChar = HIWORD(GetDialogBaseUnits());

		rect.left = 20 * cxChar;
		rect.top  = 3  * cyChar;

			// 创建列表框

		hwndList = CreateWindow(TEXT("listbox"), NULL, WS_CHILDWINDOW | WS_VISIBLE | LBS_STANDARD/*显示的文件的属性*/,
			cxChar, cyChar * 3, 
			cxChar * 13 + GetSystemMetrics(SM_CXVSCROLL), cyChar * 10,
			hwnd, (HMENU)ID_LIST, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);

			// 获取当前目录

		GetCurrentDirectory(MAX_PATH + 1, szBuffer);  // 这个是程序刚刚开始执行的时候默认显示的内容
		//MessageBox(NULL, szBuffer, NULL, NULL);

			// 创建文本框

		hwndText = CreateWindow(TEXT("static"), 
			szBuffer, // 程序开始的时候显示的 本程序的目录位置
			WS_CHILDWINDOW | WS_VISIBLE | SS_LEFT,
			cxChar, cyChar, cxChar * MAX_PATH, cyChar, 
			hwnd, (HMENU)ID_TEXT, 
			(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);

			// 用新的窗口过程替换列表框原来的窗口过程

		OldList = (WNDPROC)SetWindowLong(hwndList, GWL_WNDPROC, (LPARAM)ListProc);

			// 将文件目录列表(子目录和磁盘驱动器)写入列表框

		SendMessage(hwndList, LB_DIR, DIRATTR/*文件属性*/, (LPARAM)TEXT("*.*"));  // lParam参数是指向文件限定字符串例如("*.*")的指针, 该文件限定不影响列表框中包含的子目录;
		return 0;

	case WM_SIZE:
		rect.right		= LOWORD(lParam);
		rect.bottom		= HIWORD(lParam);

				// 用来证实rect的位置 - 用来显示文件的内容的区域

		FrameRect(GetDC(hwnd), &rect, (HBRUSH)GetStockObject(BLACK_BRUSH));
		return 0;

	case WM_SETFOCUS:
		SetFocus(hwndList);
		return 0;

	case WM_COMMAND:
		if (LOWORD(wParam) == ID_LIST && HIWORD(wParam) == LBN_DBLCLK)
		{

				// 获取当前选中项的索引值 如果没有选中项, 函数返回LB_ERR(-1)

			if (LB_ERR == (i = SendMessage(hwndList, LB_GETCURSEL, 0, 0)))
				break;

				// 将当前选中项的变量名保存进szBuffer  (比如点的是p328.txt, 那么szBuffer中保存的是"p328.txt", 并不包含目录)

			SendMessage(hwndList, LB_GETTEXT, i, (LPARAM)szBuffer);

				// 如果选中项是一个文件的话

			if (INVALID_HANDLE_VALUE != (hFile = CreateFile(szBuffer, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL)))
			{  // valid 有效的               //  CreateFile函数返回文件的句柄, 这个文件句柄将被传递给Windows函数ReadFile和CloseHandle;
			   // invalid 无效的        	  // CreateFile检查列表中得选中项, 如果返回错误, 表明选中的不是一个文件, 可能是一个子目录

					// 关闭文件句柄
				CloseHandle(hFile);

					// 是一个有效的文件
				bValidFile = TRUE;

					// 将文件目录+名字复制给szFile
				lstrcpy(szFile, szBuffer);

					// 获取当前文件目录
				GetCurrentDirectory(MAX_PATH + 1, szBuffer);

					// 防止目录最有一个字符不是'\'字符
				if (szBuffer[lstrlen(szBuffer) - 1] != '\\')
					lstrcat(szBuffer, TEXT("\\"));

					// 将文件目录和文件名字加到一起, 放到静态文本框中
				SetWindowText(hwndText, lstrcat(szBuffer, szFile));
			}

				// 如果不是一个有效文件, 那么可能是一个目录或者是一个驱动盘	
	 
			else
			{
					// 不是一个有效文件
				bValidFile = FALSE;

					// 将选中文本最后一个']'改成'\0'
					// 如过是目录: "[windows程序设计]" 这个文件夹名改成了 "[windows程序设计\0"
					// 如果是驱动: "[-g-]" 这个驱动盘改成了 "[-g-\0"

				szBuffer[lstrlen(szBuffer) - 1] = '\0';

					// if中的SetCurrentDirectory作用, 如果是一个子目录, 直接打开, 不会进入if循环
					// 如果是一个驱动, 那么进入if, 打开的是驱动
					// 如果是选中了驱动盘, 那么用SetCurrentDirectory打开这个驱动盘

				if (!SetCurrentDirectory(szBuffer + 1))
				{
					szBuffer[3] = ':';
					szBuffer[4] = '\0';
					SetCurrentDirectory(szBuffer + 2);  // szBuffer如果是驱动的话字符串是"[-g-\0", 上面的步骤将他改成了"[-g:\0", szBuffer即成了"g:"
				}

					// 获取新的目录名, 然后输出到文本框

				GetCurrentDirectory(MAX_PATH + 1, szBuffer);
				SetWindowText(hwndText, szBuffer);
						// 更新命令
				SendMessage(hwndList, LB_RESETCONTENT, 0, 0);
						// 选择可显示的文件的属性
				SendMessage(hwndList, LB_DIR, DIRATTR, (LPARAM)TEXT("*.*"));
			}
			InvalidateRect(hwnd, NULL, TRUE);
		}
		return 0;

	case WM_PAINT:

			// 如果不是有效文件, 直接退出

		if (!bValidFile)  
			break;

			// 检查一下, 如果是无效文件, 直接退出

		if (INVALID_HANDLE_VALUE == (hFile = CreateFile(szFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL)))
		{
			bValidFile = FALSE;
			break;
		}

			// 如果是有效文件, 那么进行读取, 将内容保存到buffer中, i保存了buffer中的位数

		ReadFile(hFile, buffer, MAXREAD, (LPDWORD)&i, NULL);
		CloseHandle(hFile);

			// 为文本输出设置设备环境

		hdc = BeginPaint(hwnd, &ps);
		SelectObject(hdc, GetStockObject(SYSTEM_FIXED_FONT));
		SetTextColor(hdc, GetSysColor(COLOR_BTNTEXT));
		SetBkColor(hdc, GetSysColor(COLOR_BTNFACE));

			// Assume the file is ASCII

		DrawTextA(hdc, (LPCSTR)buffer, i, &rect, DTFLAGS);

		EndPaint(hwnd, &ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

LRESULT CALLBACK ListProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_KEYDOWN && wParam == VK_RETURN)
		SendMessage(GetParent(hwnd), WM_COMMAND, MAKELONG(1, LBN_DBLCLK), (LPARAM)hwnd);
	
	return CallWindowProc(OldList, hwnd, message, wParam, lParam);
}