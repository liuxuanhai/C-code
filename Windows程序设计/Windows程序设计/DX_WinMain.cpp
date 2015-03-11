#include <windows.h>
#ifndef DXWINMAIN_CPP
#define DXWINMAIN_CPP
#include "DX_WM.CPP"
#ifndef SZAPPNAME
#define SZAPPNAME "DX_WinMain.cpp"
#endif
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

#ifdef PEEKMESSAGE
void PeekMessageInsertCode(void);
#endif

#ifdef CHANGEWNDCLASS
void ChangeWndClass(WNDCLASS *);
#endif

#ifdef CHANGECREATEWINDOW
HWND ChangeCreateWindow(HINSTANCE);
#endif

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT(SZAPPNAME);
	HWND hwnd;
	MSG  msg;
	WNDCLASS wndclass;

	wndclass.cbClsExtra    = 0;
	wndclass.cbWndExtra    = 0;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hInstance     = hInstance;
	wndclass.lpfnWndProc   = WndProc;
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName  = NULL;
	wndclass.style         = CS_HREDRAW | CS_VREDRAW;

#ifdef CHANGEWNDCLASS
	ChangeWndClass(&wndclass);
#endif

	RegisterClass(&wndclass);

#ifdef CHANGECREATEWINDOW
	hwnd = ChangeCreateWindow(hInstance);
#else
	hwnd = CreateWindow(szAppName, szAppName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
#endif

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

#ifdef PEEKMESSAGE
	while (TRUE)
	{
		// GetMessage函数并不会把控制权交给程序, 除非它从程序的消息队列中获得了消息.
		// PeekMessage函数总是立即返回, 不管消息是否出现. 如果有消息, 返回TRUE, 否则返回FALSE
		if (PeekMessage(&msg, NULL, // 窗口句柄参数
			0, 0,  // 信息范围参数   这三个参数设置成NULL或0, 表示我们想使用PeekMessage()函数返回程序中的所有窗口的所有消息消息
			PM_REMOVE))  // 如果想删除消息对流中的消息, 可以此处设置成PM_REMOVE, 不想删除, 设置成PM_NOREMOVE
			// 这里使用PM_REMOVE可以删除WM_PAINT消息之外的所有消息, 但是如果不把无效区变得有效, WM_PAINT将会一直存在, 这里也将会陷入死循环
		{
			if (msg.message == WM_QUIT)  // 在这里 必须 明确检查WM_QUIT消息, 在一个正常的消息循环中, 不需要这么做, 因为获取一个WM_QUIT消息时, GetMessage函数的返回值是FALSE(0), 但是PeekMessage函数的返回值是表示消息队列中是否有消息, 因此检查WM_QUIT是必要的.
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
			PeekMessageInsertCode();
	}
#else
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
#endif

	return msg.wParam;
}
#endif