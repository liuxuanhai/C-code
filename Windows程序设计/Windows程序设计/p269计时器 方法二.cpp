#define SZAPPNAME	"p269计时器 方法二"
#define ID_TIMER	1
#include			"DX_WinMain.cpp"

// 这个回调函数只处理WM_TIMER消息, Windows只发送WM_TIMER消息到TimerProc;
VOID CALLBACK TimerProc(HWND hwnd, UINT message, UINT, DWORD)
{
	static BOOL		fFlipFlop = FALSE;
	HBRUSH			hBrush;
	HDC				hdc;
	RECT			rc;

	MessageBeep(-1);
	fFlipFlop = !fFlipFlop;

	GetClientRect(hwnd, &rc);

	hdc		= GetDC(hwnd);
	hBrush	= CreateSolidBrush(fFlipFlop ? RGB(255, 0, 0) : RGB(0, 0, 255));
	
	FillRect(hdc, &rc, hBrush);
	ReleaseDC(hwnd, hdc);
	DeleteObject(hBrush);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		SetTimer(hwnd, ID_TIMER, 1000, TimerProc);
		return 0;

	case WM_DESTROY:
		KillTimer(hwnd, ID_TIMER);
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}