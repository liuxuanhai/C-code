#define	SZAPPNAME	"p266计时器 方法一"
#define ID_TIMER	1
#include			"DX_WinMain.cpp"

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static BOOL		fFlipFlop = FALSE;
	HBRUSH			hBrush;
	HDC				hdc;
	PAINTSTRUCT		ps;
	RECT			rc;

	switch (message)
	{
	case WM_CREATE:
		SetTimer(hwnd, ID_TIMER, 1000, NULL);
		return 0;

	case WM_TIMER:
		MessageBeep(-1);
		fFlipFlop = !fFlipFlop;
		InvalidateRect(hwnd, NULL, FALSE);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		GetClientRect(hwnd, &rc);
		hBrush = CreateSolidBrush(fFlipFlop ? RGB(255, 0, 0) : RGB(0, 0, 255));
		FillRect(hdc, &rc, hBrush);

		EndPaint(hwnd, &ps);
		DeleteObject(hBrush);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}