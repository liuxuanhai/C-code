// 一些常用的WM消息的特殊处理函数;
#include <windows.h>
#ifndef DXWM_CPP
#define DXWM_CPP
// 鼠标上显示坐标的函数;
void WM_MouseMove_ShowCoordinate(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int	xMouse, yMouse;
	TCHAR       szBuffer[200];
	HDC			hdc;
	hdc = GetDC(hwnd);

	// 鼠标轨迹删除  这里删除轨迹完全可以用白色字体把原来字给描掉, 但是我不会使用白色字;
	RECT rectMouse;
		// 无效的区域比黑框框多10px, 这样黑框框被擦除以后就能在经过多出来10px无效区的时候处理WM_PAINT时有效化绘制;
	rectMouse.left   = xMouse - 30;
	rectMouse.top    = yMouse - 26;
	rectMouse.right  = xMouse + 100;
	rectMouse.bottom = yMouse + 40;
		
	InvalidateRect  (hwnd, &rectMouse, TRUE);  // 让一个部分无效化, Send的WM_PAINT不能立即处理, 等WM_MOUSEMOVE消息处理完在处理WM_PAINT那么在无效区画的东西就更新没了;
	UpdateWindow    (hwnd);  // 所以, 这里Post一个消息比较靠谱; Post消息以后, 由于是单线程, 只能先去处理WM_PAINT, 处理完了UpdateWindow函数才算执行完, 才能执行下边的东西;
		
	rectMouse.left   = xMouse - 10;
	rectMouse.top    = yMouse - 6;
	rectMouse.right  = xMouse + 80;
	rectMouse.bottom = yMouse + 20;
		
	// 用黑框框显示更新的区域
	static POINT      apt[5];
		// 黑框轨迹删除 这里我会用白色画笔, 可以重描擦除, 但是这里又一个问题, 就是他会把坐标轴和正弦曲线也给擦出了 这个问题解决了---// 无效的区域比黑框框多10px, 这样黑框框被擦除以后就能在经过多出来20px无效区的时候处理WM_PAINT时有效化绘制;;
	SelectObject    (hdc, GetStockObject(WHITE_PEN));
	Polyline        (hdc, apt, 5);
	SelectObject    (hdc, GetStockObject(BLACK_PEN));
	apt[0].x = apt[1].x = rectMouse.left;
	apt[0].y = apt[3].y = rectMouse.top;
	apt[1].y = apt[2].y = rectMouse.bottom;
	apt[2].x = apt[3].x = rectMouse.right;
	apt[4]   = apt[0];
	Polyline        (hdc, apt, 5);
	// 新坐标输出
	xMouse           = LOWORD(lParam); // 这里是以设备坐标获取的坐标值!
	yMouse           = HIWORD(lParam);
	TextOut(hdc, xMouse + 10, yMouse, szBuffer, wsprintf(szBuffer, TEXT("(%d, %d)"), xMouse, yMouse));

	ReleaseDC(hwnd, hdc);
}

#endif