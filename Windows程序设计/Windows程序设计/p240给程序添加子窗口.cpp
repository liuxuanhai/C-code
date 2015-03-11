#include <windows.h>
#define	DIVSIONS	5

LRESULT CALLBACK WndProc		(HWND, UINT, WPARAM, LPARAM);  // 主窗口窗口过程
LRESULT CALLBACK ChildWndProc	(HWND, UINT, WPARAM, LPARAM);  // 25个子窗口窗口过程

TCHAR	szChildClass[] = TEXT("p240给程序加上子窗口_子窗口类");

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	static TCHAR	szAppName[] = TEXT("p240给程序加上子窗口");
	HWND			hwnd;
	MSG				msg;
	WNDCLASS		wndclass;

	wndclass.style			= CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc	= WndProc;
	wndclass.cbClsExtra		= 0;
	wndclass.cbWndExtra		= 0;
	wndclass.hInstance		= hInstance;
	wndclass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName	= NULL;
	wndclass.lpszClassName	= szAppName;

	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("Program requires Windows 7 !"), szAppName, MB_ICONERROR);
		return 0;
	}

	wndclass.lpfnWndProc	= ChildWndProc;
	wndclass.cbWndExtra		= sizeof(long);  // 通知Windows在内部结构中给基于这个窗口类的每个窗口预留sizeof(long)个字节的额外空间  通过SetWindowWord函数可以设置这个额外空间
											 // 用户可以利用这些空间为每个窗口保存不同的信息;
	wndclass.hIcon			= NULL;  // 不需要图标
	wndclass.lpszClassName	= szChildClass;  // 子窗口名称

	RegisterClass(&wndclass);

	hwnd = CreateWindow(szAppName, szAppName,
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT, CW_USEDEFAULT,
						CW_USEDEFAULT, CW_USEDEFAULT,
						NULL/*父窗口句柄*/, NULL/*菜单句柄*/, hInstance/*实例句柄*/, NULL/*额外参数*/);
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND	hWndChild[DIVSIONS][DIVSIONS];
	int			cxBlock, cyBlock, x, y;

	switch (message)
	{
	case WM_CREATE:
		for (x = 0; x < DIVSIONS; x++)
			for (y = 0; y < DIVSIONS; y++)
				hWndChild[x][y] = CreateWindow(szChildClass, NULL, 
												WS_CHILDWINDOW | WS_VISIBLE,
												0, 0, 0, 0, // 窗口位置和大小在后面的WndProc函数中定义, 在MoveWindow函数调用的时候进行的设置
												hwnd/*父窗口句柄*/, (HMENU)(y << 8 | x)/*对于主窗口来说这个是菜单句柄, 对于子窗口来说, 该参数称为"子ID"或"子窗口ID", 这是一个用来唯一标识子窗口的数值*/,
																// 这里简单的将子窗口ID设置成了x和y的组合
																// 相应的, 获取子窗口ID的函数是 1. idChild = GetWindowLong(hwndChild, GWL_ID);  2, idChild = GetDlgCtrlId(hwndChild);
												(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE)/*实例句柄, 在WinMain中, 很容易获取这个句柄, 因为他是WinMain中的一个参数*/,
														// 这里获取的hInstance是在设置窗口类中保存进去的
												// 而创建子窗口时, 程序必须调用GetWindowLong从Windows给窗口保留的结构中提取hInstance的值;
												NULL/*额外参数*/);
		return 0;

	case WM_SIZE:
		cxBlock = LOWORD(lParam) / DIVSIONS;
		cyBlock = HIWORD(lParam) / DIVSIONS;

		for (x = 0; x < DIVSIONS; x++)
			for (y = 0; y < DIVSIONS; y++)
				// MoveWindow函数的参数包括子窗口左上角相对于父窗口客户区的坐标, 子窗口的宽度和高度以及是否需要重画子窗口的标志
				MoveWindow(hWndChild[x][y],  // 此数组为每个子窗口保存了一个不同的窗口句柄; 
					x * cxBlock, y * cyBlock,  // 子窗口左上角相对于父窗口客户区的坐标
					cxBlock, cyBlock,  // 子窗口的宽度和高度
					TRUE);  // 是否需要重画子窗口的标志
		return 0;

	case WM_LBUTTONDOWN:
		MessageBeep(0);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

// 这个窗口过程为所有的25个子窗口处理消息
LRESULT CALLBACK ChildWndProc(HWND hwnd,  // 接收消息的子窗口句柄
							  UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC			hdc;
	PAINTSTRUCT	ps;
	RECT		rect;

	switch (message)
	{
	case WM_CREATE:  // 一共发生25次, 因为存在25个子窗口
		SetWindowLong(hwnd, 0, 0);  // on/off flag  利用在窗口结构预留的额外空间中保存一个0
				// ChildWndProc利用这个值保存矩形的当前状态(x形或没有x形)
		return 0;

	case WM_LBUTTONDOWN:
		SetWindowLong(hwnd, 0, 1 ^ GetWindowLong(hwnd, 0));
		InvalidateRect(hwnd, NULL, FALSE);  // 由于所画矩形的大小与客户区的大小一致, 所以这里WM_PAINT的处理就简单的多了;
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		GetClientRect(hwnd, &rect);  // 这里的hwnd是一个子窗口, 所以Client指的是子窗口客户区, rect保存的是子窗口客户区
		Rectangle(hdc, 0, 0, rect.right, rect.bottom);

		if (GetWindowLong(hwnd, 0))
		{
			MoveToEx(hdc, 0, 0, NULL);
			LineTo(hdc, rect.right, rect.bottom);
			MoveToEx(hdc, 0, rect.bottom, NULL);
			LineTo(hdc, rect.right, 0);
		}

		EndPaint(hwnd, &ps);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}