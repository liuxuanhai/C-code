#define	SZAPPNAME	"p300自绘按钮"
#define ID_SMALLER	1
#define ID_LARGER	2
#define BTN_WIDTH	(8 * cxChar)
#define BTN_HEIGHT	(4 * cyChar)
#include "DX_WinMain.cpp"

	// 用 多边形填充模式 将pt数组中得点连接成一个封闭图形

void Triangle(HDC hdc, POINT pt[])
{
	SelectObject(hdc, GetStockObject(BLACK_BRUSH));
	Polygon(hdc, pt, 3);
	SelectObject(hdc, GetStockObject(WHITE_BRUSH));
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND		hwndSmaller, hwndLarger;
	static int		cxClient, cyClient, cxChar, cyChar;
	int				cx, cy;
	LPDRAWITEMSTRUCT pdis;  // 指向一个DRAWITEMSTRUCT类型的结构, 这个结构存有必要的信息来帮助程序绘制按钮: hDC(按钮设备环境), rcItem(RECT结构, 提供按钮的尺寸), CtlID(控件窗口ID), itemState(按钮是否按下或具有输入焦点)
	POINT			pt[3];
	RECT			rc;  // 保存窗口矩形在设备坐标的位置

	switch (message)
	{
	case WM_CREATE:
		cxChar = LOWORD(GetDialogBaseUnits());  // 此函数用来获取字符的默认字体的宽度和高度, 对话框使用这个函数获取字体尺寸, 该函数返回一个32位值, 低位字和高位字分别是子窗口的宽度和高度; 
		cyChar = HIWORD(GetDialogBaseUnits());

			// 创建自绘按钮

		hwndSmaller	= CreateWindow(TEXT("button"), TEXT(""), WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
			0, 0, BTN_WIDTH, BTN_HEIGHT, hwnd, (HMENU)ID_SMALLER, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);

		hwndLarger		= CreateWindow(TEXT("button"), TEXT(""), WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
			0, 0, BTN_WIDTH, BTN_HEIGHT, hwnd, (HMENU)ID_LARGER, ((LPCREATESTRUCT)lParam)->hInstance, NULL);

		return 0;

	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);

			// 将子窗口按钮移动到客户区中央

		MoveWindow(hwndSmaller, cxClient / 2 - 3 * BTN_WIDTH / 2, cyClient / 2 - BTN_HEIGHT / 2, BTN_WIDTH, BTN_HEIGHT, TRUE);
		MoveWindow(hwndLarger , cxClient / 2 + 3 * BTN_WIDTH / 2, cyClient / 2 - BTN_HEIGHT / 2, BTN_WIDTH, BTN_HEIGHT, TRUE);

		return 0;

	case WM_COMMAND:  // wParam 高位字是通知码 低位字是子窗口ID  lParam 子窗口句柄
		GetWindowRect(hwnd, &rc);  // 这个不是GetClientRect, 这个是获取的窗口在设备坐标下的位置

			// 将整个窗口放大或缩小10%

		switch (wParam)
		{
		case ID_SMALLER:
			rc.left			+= cxClient / 20;
			rc.right		-= cxClient / 20;
			rc.top			+= cyClient / 20;
			rc.bottom		-= cyClient / 20;
			break;

		case ID_LARGER:
			rc.left			-= cxClient / 20;
			rc.right		+= cxClient / 20;
			rc.top			-= cyClient / 20;
			rc.bottom		+= cyClient / 20;
			break;
		}

		MoveWindow(hwnd, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, TRUE);  // MoveWindow不光能够移动子窗口, 还能移动父窗口嘞

		return 0;

	case WM_DRAWITEM:  // 对于BS_OWNERDRAW样式的按钮, 在需要重新绘制时, 它会向其父窗口发送WM_DRAWITEM消息
		// lParam 指向一个DRAWITEMSTRUCT类型的结构;
		pdis = (LPDRAWITEMSTRUCT)lParam;  // DRAWITEMSTRUCT类型的结构, 这个结构存有必要的信息来帮助程序绘制按钮: hDC(按钮设备环境), rcItem(RECT结构, 提供按钮的尺寸), CtlID(控件窗口ID), itemState(按钮是否按下或具有输入焦点)

			// 绘制一个白底黑框的区域

		FillRect(pdis->hDC, &pdis->rcItem, (HBRUSH)GetStockObject(WHITE_BRUSH));
		FrameRect(pdis->hDC, &pdis->rcItem, (HBRUSH)GetStockObject(BLACK_BRUSH));

			// 绘制按钮内的两种类型的三角形

		cx = pdis->rcItem.right - pdis->rcItem.left;
		cy = pdis->rcItem.bottom - pdis->rcItem.top;

		switch (pdis->CtlID)
		{
		case ID_SMALLER:
			pt[0].x = 3 * cx / 8;		pt[0].y = 1 * cy / 8;
			pt[1].x = 5 * cx / 8;		pt[1].y = 1 * cy / 8;
			pt[2].x = 4 * cx / 8;		pt[2].y = 3 * cy / 8;
			Triangle(pdis->hDC, pt);
			pt[0].x = 7 * cx / 8;		pt[0].y = 3 * cy / 8;
			pt[1].x = 7 * cx / 8;		pt[1].y = 5 * cy / 8;
			pt[2].x = 5 * cx / 8;		pt[2].y = 4 * cy / 8;
			Triangle(pdis->hDC, pt);
			pt[0].x = 5 * cx / 8;		pt[0].y = 7 * cy / 8;
			pt[1].x = 3 * cx / 8;		pt[1].y = 7 * cy / 8;
			pt[2].x = 4 * cx / 8;		pt[2].y = 5 * cy / 8;
			Triangle(pdis->hDC, pt);
			pt[0].x = 1 * cx / 8;		pt[0].y = 5 * cy / 8;
			pt[1].x = 1 * cx / 8;		pt[1].y = 3 * cy / 8;
			pt[2].x = 3 * cx / 8;		pt[2].y = 4 * cy / 8;
			Triangle(pdis->hDC, pt);
			break;

		case ID_LARGER:
			pt[0].x = 5 * cx / 8;		pt[0].y = 3 * cy / 8;
			pt[1].x = 3 * cx / 8;		pt[1].y = 3 * cy / 8;
			pt[2].x = 4 * cx / 8;		pt[2].y = 1 * cy / 8;
			Triangle(pdis->hDC, pt);
			pt[0].x = 5 * cx / 8;		pt[0].y = 5 * cy / 8;
			pt[1].x = 5 * cx / 8;		pt[1].y = 3 * cy / 8;
			pt[2].x = 7 * cx / 8;		pt[2].y = 4 * cy / 8;
			Triangle(pdis->hDC, pt);
			pt[0].x = 3 * cx / 8;		pt[0].y = 5 * cy / 8;
			pt[1].x = 5 * cx / 8;		pt[1].y = 5 * cy / 8;
			pt[2].x = 4 * cx / 8;		pt[2].y = 7 * cy / 8;
			Triangle(pdis->hDC, pt);
			pt[0].x = 3 * cx / 8;		pt[0].y = 3 * cy / 8;
			pt[1].x = 3 * cx / 8;		pt[1].y = 5 * cy / 8;
			pt[2].x = 1 * cx / 8;		pt[2].y = 4 * cy / 8;
			Triangle(pdis->hDC, pt);
			break;
		}

			// 如果按钮被选中, 反转矩形内所有像素

		if (pdis->itemState & ODS_SELECTED)
			InvertRect(pdis->hDC, &pdis->rcItem);

			// 如果按钮具有输入焦点, 画一个虚线框

		if (pdis->itemState & ODS_FOCUS)
		{
			pdis->rcItem.left	+= cx / 16;
			pdis->rcItem.top	+= cy / 16;
			pdis->rcItem.right	-= cx / 16;
			pdis->rcItem.bottom	-= cy / 16;
			DrawFocusRect(pdis->hDC, &pdis->rcItem);
		}

		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}