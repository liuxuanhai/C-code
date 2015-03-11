#include <iostream>
#include <windows.h>
using namespace std;
HWND GetConsoleHwnd(void);
int main(void)
{
	TCHAR szPath[MAX_PATH + 1];
	HWND hwnd = GetConsoleHwnd();
	GetCurrentDirectory(MAX_PATH + 1, szPath);
	SetWindowText(hwnd, TEXT("¥Û–€∏Á∏Á"));
	MessageBox(NULL, szPath, NULL, 0);
	//SetClassLong(hwnd, GCL_HBRBACKGROUND, (long)CreateSolidBrush(RGB(0, 0, 255)));

	return 0;
}

 HWND GetConsoleHwnd(void)
 {
       #define MY_BUFSIZE 1024 // Buffer size for console window titles.
       HWND hwndFound;         // This is what is returned to the caller.
	   WCHAR pszNewWindowTitle[MY_BUFSIZE]; // Contains fabricated
                                           // WindowTitle.
	   WCHAR pszOldWindowTitle[MY_BUFSIZE]; // Contains original
                                           // WindowTitle.

       // Fetch current window title.

       GetConsoleTitle(pszOldWindowTitle, MY_BUFSIZE);

       // Format a "unique" NewWindowTitle.

	   wsprintf(pszNewWindowTitle,TEXT("%d/%d"),
                   GetTickCount(),
                   GetCurrentProcessId());

       // Change current window title.

       SetConsoleTitle(pszNewWindowTitle);

       // Ensure window title has been updated.

       Sleep(40);

       // Look for NewWindowTitle.

       hwndFound=FindWindow(NULL, pszNewWindowTitle);

       // Restore original window title.

       SetConsoleTitle(pszOldWindowTitle);

       return(hwndFound);
}