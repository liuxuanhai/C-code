// 1. 如何创建一个列表框
// 2. 如何添加列表框的文本项目
// 3. 如何接收来自列表框的消息
// 4. 如何提取字符串
#define SZAPPNAME	"p324简单的列表框程序"
#define CHANGEWNDCLASS
#define ID_LIST		1
#define ID_TEXT		2
#include			"DX_WinMain.cpp"

	// 将主窗口的默认WHITE_BRUSH改了

void ChangeWndClass(WNDCLASS * pwndclass)
{
	pwndclass->hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
}

	// 获取环境变量的字符串, 将环境变量的字符串内容放到列表框中

void FillListBox(HWND hwndList)
{
	int			iLength;
	TCHAR *		pVarBlock, * pVarBeg, * pVarEnd, * pVarName;

	pVarBlock = GetEnvironmentStrings();  // 获取一个指向内存块的指针, 该内存块中存有所有环境变量的名称和值;
	//MessageBox(NULL, pVarBlock, NULL, MB_OK);
	while (*pVarBlock)
	{
		if (*pVarBlock != '=')  // Skip variable 命名以'='开头
		{
			pVarBeg = pVarBlock;  // 变量VarBlock的内存的开始位置
			while(*pVarBlock++ != '=');
			pVarEnd = pVarBlock - 1;  // 指向'='符号 变量VarBlock内存结束位置后边的'='
			iLength = pVarEnd - pVarBeg;  // VarBlock有多少个TCHAR内存大小

				// 给变量名分配空间, 将环境变量的值赋给它并以字符串'\0'结尾

			pVarName = (TCHAR *)calloc(iLength + 1, sizeof(TCHAR));
			CopyMemory(pVarName, pVarBeg, iLength * sizeof(TCHAR));
			pVarName[iLength] = '\0';

				// 把变量名放进列表框, 释放内存

			SendMessage(hwndList, LB_ADDSTRING, 0, (LPARAM)pVarName);
			free(pVarName);
		}
		while(*pVarBlock++ != '\0');
	}
	//FreeEnvironmentStrings(pVarBlock);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND		hwndList, hwndText;
	int				iIndex, iLength, cxChar, cyChar;
	TCHAR			* pVarName, * pVarValue;

	switch (message)
	{
	case WM_CREATE:
		cxChar = LOWORD(GetDialogBaseUnits());
		cyChar = HIWORD(GetDialogBaseUnits());

			// 创建列表框和静态文本框

		hwndList = CreateWindow(TEXT("listbox"), NULL, WS_CHILD | WS_VISIBLE | LBS_STANDARD, 
			cxChar, cyChar * 3, cxChar * 16 + GetSystemMetrics(SM_CXVSCROLL),
			cyChar * 5, 
			hwnd, (HMENU)ID_LIST, 
			(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
			NULL);

		hwndText = CreateWindow(TEXT("static"), NULL,
			WS_CHILD | WS_VISIBLE | SS_LEFT,
			cxChar, cyChar,
			GetSystemMetrics(SM_CXSCREEN), cyChar,
			hwnd, (HMENU)ID_TEXT, 
			(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
			NULL);

			// 将环境变量内容放到列表框

		FillListBox(hwndList);
		return 0;

	case WM_SETFOCUS:
		SetFocus(hwndList);
		return 0;

	case WM_COMMAND:
		if (LOWORD(wParam) == ID_LIST/*列表框的子ID*/ && HIWORD(wParam) == LBN_SELCHANGE)
		{

				// 获取当前选项, 得到选中项目的文本(环境变量的名称), 保存到pVarName中

			iIndex		= SendMessage(hwndList, LB_GETCURSEL, 0, 0);
			iLength		= SendMessage(hwndList, LB_GETTEXTLEN, iIndex, 0) + 1;
			pVarName	= (TCHAR *)calloc(iLength, sizeof(TCHAR));
			SendMessage(hwndList, LB_GETTEXT, iIndex, (LPARAM)pVarName);  // 使用LB_GETTEXT得到选中项的文本, 即环境变量的名称;

				// 获取变量名下面对应的环境字符串
			 
			iLength		= GetEnvironmentVariable(pVarName, NULL, 0);  // 使用GetEnvironmentVariable获得环境变量相对应的环境字符串
			pVarValue	= (TCHAR *)calloc(iLength, sizeof(TCHAR));
			GetEnvironmentVariable(pVarName, pVarValue, iLength);

				// 在静态文本框中显示环境字符串

			SetWindowText(hwndText, pVarValue);  // 再使用SetWindowText把这个字符串送到静态子窗口控件中去显示
			free(pVarName);
			free(pVarValue);
		}
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}