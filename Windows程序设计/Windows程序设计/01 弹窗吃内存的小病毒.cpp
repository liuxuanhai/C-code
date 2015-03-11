#include <windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	int i = 0;
	while (malloc(1024))
	{
		TCHAR szBuffer[100];
		if (++i % (1024 * 100) == 0)
		{
			wsprintf(szBuffer, TEXT("我已经吃了%dM内存."), i/1024);
			MessageBox(NULL, szBuffer, TEXT("message"), MB_OK);
		}
		if (i == 1024 * 1024)
			break;
	}
}