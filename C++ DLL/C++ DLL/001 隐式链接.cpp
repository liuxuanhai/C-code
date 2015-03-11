// Build: 2014-10-5 15:04:58

#define	 HEABDLLEC	 extern "C" _declspec(dllexport)
#define  HEABDLL	 _declspec(dllexport)
#include <windows.h>
#include "001 ÒþÊ½Á´½Ó.h"

 int add(int a, int b)
{
	return a + b;
}

void Point::output(int x, int y)
{
	HWND hwnd = GetForegroundWindow();
	WCHAR buf[20];
	wsprintf(buf, L"x = %d, y = %d", x, y);
	SetWindowText(hwnd, buf);
}

void Point::input()
{}