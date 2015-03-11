// 将逻辑点设置成客户区中心, 然后画一个正弦曲线
#define SZAPPNAME "p146逻辑点位于中心的正弦曲线.cpp"
#include "DX_WinMain.cpp"
#include <cmath>


LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC			hdc;
	static int	cxClient, cyClient;
	TCHAR       szBuffer[200];

	switch (message)
	{
	case WM_SIZE:
		cxClient = LOWORD(lParam);  
		cyClient = HIWORD(lParam);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		//SetViewportOrgEx(hdc, cxClient / 2, cyClient / 2, NULL);  // # 1
		SetWindowOrgEx(hdc, -cxClient / 2, -cyClient / 2, NULL);  // # 2 
		// GetVieportOrgEx()中, 得到的(x, y)以设备坐标系坐标(左上角为(0, 0))显示视口原点位置, 这样就标识出了视口原点的位置;
		// GetWindowOrgEx()中, 得到的(x, y)以逻辑坐标系(窗口原点为(0, 0))显示视口原点位置, 这样就标识出了窗口原点的位置;
		// 可以认为只有两个坐标系统, 一个是设备坐标系统, 一直以左上角为(0, 0) 负责标识视口原点位置进而标识窗口原点位置, 然后是逻辑坐标系统, 用来画东西;
		// # 1 视口原点 窗口原点 移到中央, 显示视口原点(504, 244), 窗口原点(0, 0);
		// # 2 视口原点 在左上角, 视口原点(0, 0) 窗口原点 在中央 窗口原点(-504, -244);
		// # 1 # 2 视口原点 在中央 视口原点(504, 244) 窗口原点 在右下角 窗口原点(-504, -244);
		MoveToEx(hdc, -cxClient / 2, 0, NULL);  // 初始坐标默认是(0, 0)是相对于逻辑原点的;
		LineTo(hdc, cxClient / 2, 0);
		MoveToEx(hdc, 0, cyClient / 2, NULL);
		LineTo(hdc, 0, -cyClient / 2);
		MoveToEx(hdc, 0, 0, NULL);
		int x, y;
		for (int i = 0; i < 1000; i++)
		{
			x = i * cxClient / 2 / 1000;  // i / 1000 * (cxClient / 2)
			y = -(int)(sin(i * 2 * 3.1415926 / 1000) * cyClient / 2);  // i / 1000 * 2PIE
			LineTo(hdc, x, y);
		}

		// 输出视口原点 窗口原点 进行视窗转换
		POINT ptOrg;
		GetWindowOrgEx(hdc, &ptOrg);
		TextOut(hdc, 20, 20, szBuffer, wsprintf(szBuffer, TEXT("窗口原点: (%d, %d)"), ptOrg.x, ptOrg.y));
		LPtoDP(hdc, &ptOrg, 1);
		TextOut(hdc, 200, 20, szBuffer, wsprintf(szBuffer, TEXT("LPtoDP: (%d, %d)"), ptOrg.x, ptOrg.y));
		GetViewportOrgEx(hdc, &ptOrg);
		TextOut(hdc, 20, 50, szBuffer, wsprintf(szBuffer, TEXT("视口原点: (%d, %d)"), ptOrg.x, ptOrg.y));
		DPtoLP(hdc, &ptOrg, 1);
		TextOut(hdc, 200, 50, szBuffer, wsprintf(szBuffer, TEXT("DPtoLP: (%d, %d)"), ptOrg.x, ptOrg.y));

		EndPaint(hwnd, &ps);
		return 0;

		// 输出鼠标的坐标
	case WM_MOUSEMOVE:
		static int xMouse, yMouse;
		hdc = GetDC(hwnd);

		// 鼠标轨迹删除  这里删除轨迹完全可以用白色字体把原来字给描掉, 但是我不会使用白色字;
		RECT rectMouse;
			// 无效的区域比黑框框多10px, 这样黑框框被擦除以后就能在经过多出来10px无效区的时候处理WM_PAINT时有效化绘制;
		rectMouse.left = xMouse - 30;
		rectMouse.top  = yMouse - 26;
		rectMouse.right = xMouse + 100;
		rectMouse.bottom = yMouse + 40;
		
		InvalidateRect(hwnd, &rectMouse, TRUE);  // 让一个部分无效化, Send的WM_PAINT不能立即处理, 等WM_MOUSEMOVE消息处理完在处理WM_PAINT那么在无效区画的东西就更新没了;
		UpdateWindow(hwnd);  // 所以, 这里Post一个消息比较靠谱; Post消息以后, 由于是单线程, 只能先去处理WM_PAINT, 处理完了UpdateWindow函数才算执行完, 才能执行下边的东西;
		
		rectMouse.left = xMouse - 10;
		rectMouse.top  = yMouse - 6;
		rectMouse.right = xMouse + 80;
		rectMouse.bottom = yMouse + 20;
		
		// 用黑框框显示更新的区域
		static POINT apt[5];
			// 黑框轨迹删除 这里我会用白色画笔, 可以重描擦除, 但是这里又一个问题, 就是他会把坐标轴和正弦曲线也给擦出了 这个问题解决了---// 无效的区域比黑框框多10px, 这样黑框框被擦除以后就能在经过多出来20px无效区的时候处理WM_PAINT时有效化绘制;;
		SelectObject(hdc, GetStockObject(WHITE_PEN));
		Polyline(hdc, apt, 5);
		SelectObject(hdc, GetStockObject(BLACK_PEN));
		apt[0].x = apt[1].x = rectMouse.left;
		apt[0].y = apt[3].y = rectMouse.top;
		apt[1].y = apt[2].y = rectMouse.bottom;
		apt[2].x = apt[3].x = rectMouse.right;
		apt[4] = apt[0];
		Polyline(hdc, apt, 5);
		// 新坐标输出
		xMouse = LOWORD(lParam); // 这里是以设备坐标获取的坐标值!
		yMouse = HIWORD(lParam);
		TextOut(hdc, xMouse + 10, yMouse, szBuffer, wsprintf(szBuffer, TEXT("(%d, %d)"), xMouse, yMouse));

		ReleaseDC(hwnd, hdc);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}