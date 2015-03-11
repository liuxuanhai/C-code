#define	SZAPPNAME	"p225简单的鼠标处理程序"
#define MAXPOINTS	1000
#include			"DX_WinMain.cpp"

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static POINT	pt[MAXPOINTS];
	static int		iCount;
	HDC				hdc;
	int				i, j;
	PAINTSTRUCT		ps;

	switch (message)
	{
	case WM_LBUTTONDOWN:
		iCount = 0;
		InvalidateRect(hwnd, NULL, TRUE);
		return 0;

	case WM_MOUSEMOVE:
		if (wParam & MK_LBUTTON && iCount < 1000)
		{
			pt[iCount  ].x = LOWORD(lParam);
			pt[iCount++].y = HIWORD(lParam);

			hdc = GetDC(hwnd);
			SetPixel(hdc, LOWORD(lParam), HIWORD(lParam), NULL);
			ReleaseDC(hwnd, hdc);
		}
		return 0;

	case WM_LBUTTONUP:
		InvalidateRect(hwnd, NULL, FALSE);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		SetCursor(LoadCursor(NULL, IDC_WAIT));
		ShowCursor(TRUE);

		for (i = 0; i < iCount - 1; i++)
			for (j = i + 1; j < iCount; j++)
			{
				MoveToEx(hdc, pt[i].x, pt[i].y, NULL);
				LineTo(hdc, pt[j].x, pt[j].y);
			}
		
		ShowCursor(FALSE);
		SetCursor(LoadCursor(NULL, IDC_ARROW));

		EndPaint(hwnd, &ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}