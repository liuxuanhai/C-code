// 待解决Bug:
//			为什么窗口远点在鼠标滑过的时候闪烁;
// 证明改变视口原点窗口原点跟着改变, 改变窗口原点, 视口原点不动;
// 注意: GetViewportOrgEx和GetWindowOrgEx都是得到的 视口原点 的坐标, 只是一个是设备坐标系下的, 一个是逻辑坐标系下的;!!!!!!!!!!!!!!!!!!!!
// 刚刚左击设置好了视口原点, 结果一右击视口原点又回到了左上角, 这是因为左击时WM_PAINT的hdc在执行完了后就被销毁了, 然后右击进入WM_PAINT以后是新的hdc;
// 记住一点: GetViewportOrgEx和GetWindowOrgEx返回的值在经过DPtoLP后永远相等;
#define SZAPPNAME "p147视口和窗口.cpp"
#include "DX_WinMain.cpp"

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT  ps;
	HDC          hdc;
	static POINT ptViewport, ptWindow;
	TCHAR        szBuffer[100];
	static enum{Neither, View, Wnd, All}ViewOrWnd = Neither;

	switch (message)
	{
	case WM_CREATE:
		hdc = GetDC(hwnd);

		SetPixel(hdc, ptViewport.x, ptViewport.y, RGB(0xff, 0, 0));
		SetPixel(hdc, ptWindow.x, ptWindow.y, RGB(0xff, 0, 0));

		ReleaseDC(hwnd, hdc);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		
		// 视口原点的相关操作
		if (ViewOrWnd == View || ViewOrWnd == All)  // 选择设置视口还是窗口(鼠标左击了还是右击了);
			SetViewportOrgEx(hdc, ptViewport.x, ptViewport.y, NULL);
		if (!GetViewportOrgEx(hdc, &ptViewport))
			MessageBox(NULL, TEXT("未能成功获取视口原点"), TEXT("Error"), MB_ICONERROR);
		else
		{
			POINT ptTemp;
			ptTemp = ptViewport;  // 用来保存用于TextOut输出的逻辑坐标值;
			DPtoLP(hdc, &ptViewport, 1);  // GetViewprotOrgEx 获取的是设备坐标系统的值, 要转化成逻辑坐标值;
			TextOut(hdc, ptViewport.x, ptViewport.y, szBuffer, wsprintf(szBuffer, TEXT("设置视口原点: (%d, %d)"), ptTemp.x, ptTemp.y));
			MoveToEx(hdc, ptViewport.x + 100, ptViewport.y, NULL);
			LineTo(hdc, ptViewport.x, ptViewport.y);
			LPtoDP(hdc, &ptViewport, 1);  // 用完要设置回设备坐标, ptViewport是个static, 要保证下次进入WM_PAINT即使没有左击SetViewportOrgEx使用的时候还是设备坐标单位而不是逻辑坐标单位!
		}
		
		// 窗口原点的相关操作
		if (ViewOrWnd == Wnd || ViewOrWnd == All)
			SetWindowOrgEx(hdc, ptViewport.x - ptWindow.x, ptViewport.y - ptWindow.y, NULL);  // 设置窗口原点
		if (!GetWindowOrgEx(hdc, &ptWindow))
			MessageBox(NULL, TEXT("未能成功获取窗口原点"), TEXT("Error"), MB_ICONERROR);
		else
		{
			// 如果视口原点与窗口原点在同一位置, 调整输出
			if (0 == ptWindow.x && 0 == ptWindow.y)
				TextOut(hdc, ptWindow.x + 200, ptWindow.y, szBuffer, wsprintf(szBuffer, TEXT("设置窗口原点: (%d, %d)"), ptWindow.x, ptWindow.y));
			else
				TextOut(hdc, 0, 0, szBuffer, wsprintf(szBuffer, TEXT("设置窗口原点: (%d, %d)"), ptWindow.x, ptWindow.y));
			
			MoveToEx(hdc, 0, 0 + 100, NULL);
			LineTo(hdc, 0, 0);
		}

		// 在固定区域输出而不管逻辑坐标在哪里的办法
		POINT ptTemp2;
		ptTemp2.x = 500;
		ptTemp2.y = 0;
		DPtoLP(hdc, &ptTemp2, 1);
		if (ptWindow.x == 0 && ptWindow.y == 0)
			TextOut(hdc, ptTemp2.x, ptTemp2.y, TEXT("视口原点与窗口原点在 同一个 位置"), lstrlen(TEXT("视口原点与窗口原点在 同一个 位置")));
		else
			TextOut(hdc, ptTemp2.x, ptTemp2.y, TEXT("视口原点与窗口原点在 不同的 位置"), lstrlen(TEXT("视口原点与窗口原点在 不同的 位置")));

		EndPaint(hwnd, &ps);
		return 0;
  
	case WM_LBUTTONDOWN:
		// 左击时, 将鼠标位置保存下来, 设置为视口原点
		ptViewport.x = LOWORD(lParam);
		ptViewport.y = HIWORD(lParam);
		ViewOrWnd    = View;
		InvalidateRect(hwnd, NULL, TRUE);
		return 0;

	case WM_RBUTTONDOWN: 
		// 右击时, 键鼠标位置保存下来, 设置为窗口原点
		ptWindow.x = LOWORD(lParam);
		ptWindow.y = HIWORD(lParam);  // 获取鼠标位置DP
		ViewOrWnd  = Wnd;
		InvalidateRect(hwnd, NULL, TRUE);
		return 0;

	// 输出鼠标的坐标
	case WM_MOUSEMOVE:
		WM_MouseMove_ShowCoordinate(hwnd, message, wParam, lParam);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}