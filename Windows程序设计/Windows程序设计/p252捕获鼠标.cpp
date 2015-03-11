#define	SZAPPNAME "p252捕获鼠标"
#include "DX_WinMain.cpp"

void DrawBoxOutline(HWND hwnd, POINT ptBeg, POINT ptEnd)
{
	HDC	hdc;
	hdc = GetDC(hwnd);

	SetROP2(hdc, R2_NOT);
	SelectObject(hdc, GetStockObject(NULL_BRUSH));
	Rectangle(hdc, ptBeg.x, ptBeg.y, ptEnd.x, ptEnd.y);

	ReleaseDC(hwnd, hdc);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static BOOL		fBlocking, fValidBox;
	static POINT	ptBeg, ptEnd, ptBoxBeg, ptBoxEnd;
	HDC				hdc;
	PAINTSTRUCT		ps;

	switch (message)
	{
	case WM_LBUTTONDOWN:
		ptBeg.x = ptEnd.x = LOWORD(lParam);
		ptEnd.y = ptBeg.y = HIWORD(lParam);

		DrawBoxOutline(hwnd, ptBeg, ptEnd);

		SetCapture(hwnd);  // 设置捕获鼠标  这个函数还避免了"p249设计一个矩形.cpp"中的鼠标来回在"十字"与"指针"之间的闪烁问题;
		SetCursor(LoadCursor(NULL, IDC_CROSS));

		fBlocking = TRUE;
		return 0;

	case WM_MOUSEMOVE:
		if (fBlocking)
		{
			SetCursor(LoadCursor(NULL, IDC_CROSS));

			DrawBoxOutline(hwnd, ptBeg, ptEnd);

			ptEnd.x = LOWORD(lParam);
			ptEnd.y = HIWORD(lParam);

			DrawBoxOutline(hwnd, ptBeg, ptEnd);
		}
		return 0;

	case WM_LBUTTONUP:
		if (fBlocking)
		{
			DrawBoxOutline(hwnd, ptBeg, ptEnd);

			ptBoxBeg		= ptBeg;
			ptBoxEnd.x		= LOWORD(lParam);
			ptBoxEnd.y		= HIWORD(lParam);

			ReleaseCapture();  // 释放捕获鼠标
			SetCursor(LoadCursor(NULL, IDC_ARROW));

			fBlocking		= FALSE;
			fValidBox		= TRUE;

			InvalidateRect(hwnd, NULL, TRUE);
		}

		return 0;
		
	case WM_CHAR:
		if (fBlocking & (wParam == '\x1B'))  // i.e., Escape
		{
			DrawBoxOutline(hwnd, ptBeg, ptEnd);
			ReleaseCapture();  // 释放捕获鼠标
			SetCursor(LoadCursor(NULL, IDC_ARROW));
			fBlocking = FALSE;
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