// 同比例缩放两个坐标轴, 建立宽高比与显示设备无关的图像;
// 默认的映射为MM_LOMETRIC, 当改变范围的时候, 新的x, y轴方向是设置SetWindowExtEx和SetViewportExtEx时x1*x2和y1*y2的值是正数还是负数
#define		SZAPPNAME	"p153自定义映射模式之MM_ISOTROPIC"
#include				"DX_WinMain.cpp"

HDC SetMode(HWND hwnd, HDC hdc);

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT		ps;
	HDC				hdc;
	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		SelectObject(hdc, CreatePen(PS_SOLID, 20, RGB(0xff, 0, 0)));
		hdc = SetMode(hwnd, hdc);

		MoveToEx(hdc, 0, 0, NULL);
		LineTo(hdc, 0, 1000);
		MoveToEx(hdc, 1000, 0, NULL);
		LineTo(hdc, -1000, 0);
		MoveToEx(hdc, 0, 0, NULL);
		LineTo(hdc, 0, -1000);
		MoveToEx(hdc, 0, 0, NULL);
		LineTo(hdc, 1000, 0);

		EndPaint(hwnd, &ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

HDC SetMode(HWND hwnd, HDC hdc)
{
	RECT rcTemp;
	GetClientRect(hwnd, &rcTemp);
	SetMapMode(hdc, MM_ISOTROPIC);

	SetWindowExtEx(hdc, 1000, 1000, NULL);  // 以逻辑坐标的第一象限上(1000, 1000)对应设备坐标第四象限(rcTemp.right, -rcTemp.bottom);
												// 同样, 写            (-1000, -1000)                  (-rcTemp.right, rcTemp.bottom)效果是一样的;
	SetViewportExtEx(hdc, rcTemp.right, -rcTemp.bottom, NULL);

		// 逻辑坐标原点在客户区左下角

	//SetWindowOrgEx(hdc, 0, 1000, NULL);  // 这样写是不对的, 在宽度大于高度的时候会导致逻辑原点被抬高
	//SetViewportOrgEx(hdc, 0, rcTemp.bottom, NULL);  // 这样写才是对的

		// 逻辑坐标原点在客户区左上角

	//SetWindowOrgEx(hdc, 0, 1000, NULL);  // 同样, 这里只能这样写

		// 逻辑坐标原点在客户区中心
	SetViewportExtEx(hdc, rcTemp.right / 2, -rcTemp.bottom / 2, NULL);  // 别忘了这里对应的是一半
	SetViewportOrgEx(hdc, rcTemp.right / 2, rcTemp.bottom / 2, NULL);

	return hdc;
}