#include <windows.h>
#include "p075TextOut格式化绘制文字.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("SysMets1");
	HWND hwnd;
	MSG  msg;
	WNDCLASS wndclass;

	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("This program requires Windows NT!"), szAppName, MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(szAppName, TEXT("Get System Metrics No.1"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
	ShowWindow(hwnd, iCmdShow);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int cxChar, cxCaps, cyChar;  // c: count 这里代表像素数
	HDC hdc;
	int i;
	PAINTSTRUCT ps;  // ps.hdc 就是BeginPaint函数返回的hdc, ps.fErase 使无效区域有效的时候是否擦出了背景, 是 FALSE, 否 TRUE(比如Invalidate函数最后一个参数FALSE指定不能擦除背景, 那么这里就是否TRUE); 
	// ps.rcPaint 使用的是逻辑像素坐标, 这里是一个裁剪矩形, 这意味着windows将把绘制限制在这个矩形里的无效区域中;
	TCHAR szBuffer[10];
	TEXTMETRIC tm;

	switch (message)
	{ 
		// windows程序运行的时候, 系统字体不会变化, 因此, 应用程序只需要调用一次GetTextMetrics函数, 最好的时机就是WM_CREATE进行窗口初始化的时候;
	case WM_CREATE:  // 调用CreatWindow()的时候接收到第一条消息(WM_CREATE)
		hdc = GetDC(hwnd);  // 获取窗口的设备环境句柄, 这里获取的句柄跟BeginPaint函数返回的不同, 这个设备环境句柄中的裁剪区域是整个客户区(这样没有无效区域也能绘制), GetDC也不会使无效区域有效化(validateRect(hwnd, NULL));
		
		GetTextMetrics(hdc, &tm);  // 获取默认系统字体的尺寸 他需要一个设备环境句柄, 因为他需要知道设备环境结构中的字体信息, 然后将该信息复制到TEXTMETRICS中;
		cxChar = tm.tmAveCharWidth;  // 平均字符宽度
		cxCaps = (tm.tmPitchAndFamily & 1 ? 3 : 2) * cxChar / 2;  // 大写字符的平均宽度(在变宽字体中, cxCaps设为cxChar的1.5倍) tmPitchAndFamily字段的低位决定字体是否为等宽字体: 1代表变宽字体, 0代表等宽字体
		cyChar = tm.tmHeight + tm.tmExternalLeading;  // 字符的总高度(包括外部间距)
	
		ReleaseDC(hwnd, hdc);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		
		for (i = 0; i < NUMLINES; i++)
		{
			// TextOut函数向窗口的客户区输出一个字符串.
			// TextOut(hdc,  // 设备环境句柄 定义了文本属性和裁剪区域等 // 几乎所有的GDI函数都需要这个句柄作为函数的第一个参数
			//     x, y,  // 字符串在客户区的开始位置 用的是逻辑像素坐标` 默认的设备环境句柄中, 坐标原点在客户区的左上角
			//     psText,  // 指向字符串的指针
			//     iLength  // 字符串的长度(以字符为单位));
			// TextOut()并不认为字符串尾部为0字节表示字符串结束, 它利用iLength参数来决定字符串的长度.
			TextOut(ps.hdc/*其实绘图结构中第一个属性就是DC句柄*/, 0, cyChar * i, sysmetrics[i].szLabel, lstrlen(sysmetrics[i].szLabel));
			TextOut(hdc, 22 * cxCaps, cyChar * i, sysmetrics[i].szDesc, lstrlen(sysmetrics[i].szDesc));

			// 通知windows后继的TextOut函数调用使用的坐标从客户区的右上角开始而不是左上角
			SetTextAlign(hdc, TA_RIGHT | TA_TOP);  // 指定显示的结束位置而不是开始位置

			TextOut(hdc, 22 * cxCaps + 40 * cxChar, cyChar * i, szBuffer, wsprintf(szBuffer, TEXT("%5d"), GetSystemMetrics(sysmetrics[i].Index)));
			
			// 将对齐方式设置为正常
			SetTextAlign(hdc, TA_LEFT | TA_TOP);
		}
		EndPaint(hwnd, &ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}