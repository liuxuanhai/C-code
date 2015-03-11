#define		SZAPPNAME	"p249设计一个矩形"
#include				"DX_WinMain.cpp"

void DrawBoxOutline(HWND hwnd, POINT ptBeg, POINT ptEnd)
{
	HDC		hdc;

	hdc = GetDC(hwnd);

	SetROP2(hdc, R2_NOT);  // 绘图模式, R2_NOT将目标颜色取反来绘制, 不管画笔的颜色;
	SelectObject(hdc, GetStockObject(NULL_BRUSH));
	Rectangle(hdc, ptBeg.x, ptBeg.y, ptEnd.x, ptEnd.y);

	ReleaseDC(hwnd, hdc);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT		ps;
	HDC				hdc;
	static BOOL		fBlocking, fValidBox;
	static POINT	ptBeg, ptEnd, ptBoxBeg, ptBoxEnd;

	switch (message)
	{
	case WM_LBUTTONDOWN:
		ptBeg.x = ptEnd.x = LOWORD(lParam);
		ptBeg.y = ptEnd.y = HIWORD(lParam);

		DrawBoxOutline(hwnd, ptBeg, ptEnd);

		SetCursor(LoadCursor(NULL, IDC_CROSS));  // 将鼠标设置成十字形
		fBlocking = TRUE;
		return 0;

	case WM_MOUSEMOVE:
		if (fBlocking)
		{
			SetCursor(LoadCursor(NULL, IDC_CROSS));

			DrawBoxOutline(hwnd, ptBeg, ptEnd);  // 由于选择的是取反绘制, 所以再把原来的黑线重新绘制一次将会得到白线;

			ptEnd.x = LOWORD(lParam);
			ptEnd.y = HIWORD(lParam);

			DrawBoxOutline(hwnd, ptBeg, ptEnd);  // 绘制黑线
		}
		return 0;

	case WM_LBUTTONUP:
		if (fBlocking)
		{
			DrawBoxOutline(hwnd, ptBeg, ptEnd);

			ptBoxBeg	= ptBeg;
			ptBoxEnd.x	= LOWORD(lParam);
			ptBoxEnd.y = HIWORD(lParam);

			SetCursor(LoadCursor(NULL, IDC_ARROW));

			fBlocking	= FALSE;
			fValidBox	= TRUE;

			InvalidateRect(hwnd, NULL, TRUE);
		}
		return 0;

	case WM_CHAR:
		if (fBlocking & (wParam == 'x1B'))
		{
			DrawBoxOutline(hwnd, ptBeg, ptEnd);

			SetCursor(LoadCursor(NULL, IDC_ARROW));

			fBlocking	= FALSE;
		}
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		if (fValidBox)
		{
			SelectObject(hdc, GetStockObject(BLACK_BRUSH));
			Rectangle(hdc, ptBoxBeg.x, ptBoxBeg.y, ptBoxEnd.x, ptBoxEnd.y);
		}

		if (fBlocking)
		{
			SetROP2(hdc, R2_NOT);
			SelectObject(hdc, GetStockObject(NULL_BRUSH));
			Rectangle(hdc, ptBeg.x, ptBeg.y, ptEnd.x, ptEnd.y);
		}

		EndPaint(hwnd, &ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}