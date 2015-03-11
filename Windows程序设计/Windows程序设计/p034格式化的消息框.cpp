#include <windows.h>
#include <tchar.h>
#include <stdio.h>

int CDECL MessageBoxPrintf(TCHAR * szCaption, TCHAR * szFormat, ...)
{
	TCHAR szBuffer[1024];
	va_list pArgList;  // typedef char * va_list;
	va_start(pArgList, szFormat);// pArgList = (char *) &szFormat + sizeof(szFormat); va_start宏将pArg设为指向一个在堆栈参数szFormat之上的堆栈变量
	// va_arg(pArgList, int); 将会读取第一个int并将指针指向sizeof(int)之后的指针;
	_vsntprintf_s(szBuffer, sizeof(szBuffer) / sizeof(TCHAR),  // 如果是宽字符, 返回的将会是实际字符2倍的字节数, 所以这里要除以sizeof(TCHAR)
		szFormat, pArgList);
	va_end(pArgList);

	return MessageBox(NULL, szBuffer, szCaption, 0);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	int cxScreen, cyScreen;

	cxScreen = GetSystemMetrics(SM_CXSCREEN);
	cyScreen = GetSystemMetrics(SM_CYSCREEN);

	MessageBoxPrintf(TEXT("ScrnSize"), TEXT("The screen is %i pixels wide by %i pixels high."), cxScreen, cyScreen);

	return 0;
}