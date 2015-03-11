#include <windows.h>
#include <stdio.h>

// 窗口过程函数
LRESULT CALLBACK WinSunProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WinMain(HINSTANCE hInstance, HINSTANCE
			hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// 设计窗口类
	WNDCLASS wndcls;  // 一个窗口类
	wndcls.cbClsExtra = 0;  // 类附加字节数
	wndcls.cbWndExtra = 0;  // 窗口附加字节数	
	wndcls.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);  // 背景颜色设置(有强制类型转换)
	wndcls.hCursor = LoadCursor(NULL, IDC_CROSS);  // 光标设置 NULL 说明使用的是标准光标
	wndcls.hIcon = LoadIcon(NULL, IDI_ERROR);  // 图标
	wndcls.hInstance = hInstance;  // 应用程序实例号
	wndcls.lpfnWndProc = WinSunProc;  // 窗口过程函数
	wndcls.lpszClassName = TEXT("wndcls类的类名");  // 类名设置
	wndcls.lpszMenuName = NULL;  // 没有菜单
	wndcls.style = CS_HREDRAW | CS_VREDRAW;  // 类类型 水平重画 shuzhichonghua
	RegisterClass(&wndcls);  // 注册窗口类

	HWND hwnd;  // 定义一个句柄
	hwnd = CreateWindow(TEXT("wndcls类的类名")/*类名*/, TEXT("我是窗口的名字"), WS_OVERLAPPEDWINDOW/*窗口类型 标题栏 最小化 最大化*/, 0, 0,/*创建的时候x, y坐标*/600, 400,/*窗口的宽度和高度*/NULL,/*父窗口*/ NULL, /*菜单*/ hInstance, /*实例程序的句柄*/ 0, 0,/*窗口创建的时候的位置*/ 600, 400,/*窗口的大小*/ NULL,/*父窗口*/NULL,/*菜单*/hInstance,/*实例句柄*/NULL/*窗口创建的数据*/);
	ShowWindow(hwnd, SW_SHOWNORMAL);  // 显示窗口
	UpdateWindow(hwnd);  // 更新一个窗口

	// 消息循环
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WinSunProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CHAR:
		MessageBox(hwnd, TEXT("键盘被按下了"), TEXT("case WM_CHAR:"), 0);
		break;
	case WM_LBUTTONDOWN:
		MessageBox(hwnd, TEXT("鼠标被点击了"), TEXT("case WM_LBUTTONDOWN"), 0);
		HDC hdc;
		hdc = GetDC(hwnd);
		TextOut(hdc, 0, 50, TEXT("case WM_LBUTTONDOWN"), strlen("case WM_LBUTTONDOWN"));
		
		break;
	case WM_PAINT:  // 窗口重绘
		HDC hDc;
		PAINTSTRUCT ps;
		hDc = BeginPaint(hwnd, &ps);
		TextOut(hDc, 0, 0, TEXT("窗口重绘了"), strlen("窗口重绘了"));
		EndPaint(hwnd, &ps);
		ReleaseDC(hwnd, hDc);
		break;
	case WM_CLOSE:
		if (IDYES == MessageBox(hwnd, TEXT("是否真的结束?"), TEXT("case WM_CLOSE"), MB_YESNO))
		{
			DestroyWindow(hwnd);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	}
	return 0;
}