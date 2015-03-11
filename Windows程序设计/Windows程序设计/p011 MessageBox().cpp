#include <windows.h>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR
				   szCmdLine, int iCmdShow)
{
	MessageBox(NULL, TEXT("Content"), TEXT("Caption Bar"), MB_OKCANCEL);
	return 0;
}