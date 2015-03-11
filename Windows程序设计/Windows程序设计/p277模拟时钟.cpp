#define  SZAPPNAME		"p277模拟时钟"
#include				"DX_WinMain.cpp"
#include				<cmath>
#define	 ID_TIMER		1
#define  TWOPI			(2 * 3.14159)

	// 设置映射模式： x[-1000, 1000]↑, y[-1000, 1000]→, 视口原点为客户区中心， 窗口原点跟随视口原点；

void SetIsotropic(HDC hdc, int cxClient, int cyClient)
{
	SetMapMode(hdc, MM_ISOTROPIC);
	SetWindowExtEx(hdc, 1000, 1000, NULL);
	SetViewportExtEx(hdc, cxClient / 2, -cyClient / 2, NULL);
	SetViewportOrgEx(hdc, cxClient / 2, cyClient / 2, NULL);
}

	// 把参数中的点绕着原点顺时针旋转

void RotatePoint(POINT pt[], int iNum, int iAngle) // rotate旋转
{
	int		i;
	POINT	ptTemp;

	for (i = 0; i < iNum; i++)
	{
		ptTemp.x = (int)(pt[i].x * cos(TWOPI * iAngle / 360) + pt[i].y * sin(TWOPI * iAngle / 360));
		ptTemp.y = (int)(pt[i].y * cos(TWOPI * iAngle / 360) - pt[i].x * sin(TWOPI * iAngle / 360));
		pt[i] = ptTemp;
	}
}

	// 画表, 除了指针部分

void DrawClock(HDC hdc)
{
	int		iAngle;
	POINT	pt[3];

	for (iAngle = 0; iAngle < 360; iAngle += 6)
	{
		pt[0].x = 0;
		pt[0].y = 900;

		RotatePoint(pt, 1, iAngle);

		pt[2].x = pt[2].y = iAngle % 5 ? 33 : 100;

		pt[0].x -= pt[2].x / 2;
		pt[0].y -= pt[2].y / 2;

		pt[1].x = pt[0].x + pt[2].x;
		pt[1].y = pt[0].y + pt[2].y;

		SelectObject(hdc, GetStockObject(BLACK_BRUSH));

		Ellipse(hdc, pt[0].x, pt[0].y, pt[1].x, pt[1].y);
	}
}

	// 画指针

void DrawHands(HDC hdc, SYSTEMTIME * pst, BOOL fChange)
{
	static POINT	pt[3][5] = {0, -150, 100, 0, 0, 600, -100, 0, 0, -150, 
								0, -200,  50, 0, 0, 800,  -50, 0, 0, -200,
								0,    0,   0, 0, 0,   0,    0, 0, 0,  800};
	int				i, iAngle[3];
	POINT			ptTemp[3][5];

	iAngle[0] = (pst->wHour * 30) % 360 + pst->wMinute / 2;
	iAngle[1] = pst->wMinute * 6;
	iAngle[2] = pst->wSecond * 6;

	memcpy(ptTemp, pt, sizeof(pt));

	for (i = fChange ? 0 : 2; i < 3; i++)
	{
		RotatePoint(ptTemp[i], 5, iAngle[i]);

		Polyline(hdc, ptTemp[i], 5);
	}
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int			cxClient, cyClient;
	static SYSTEMTIME	stPrevious;
	BOOL				fChange;
	HDC					hdc;
	PAINTSTRUCT			ps;
	SYSTEMTIME			st;

	switch (message)
	{
	case WM_CREATE:
		SetTimer(hwnd, ID_TIMER, 1000, NULL);
		GetLocalTime(&st);
		stPrevious = st;
		return 0;

	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		return 0;

	case WM_TIMER:
		GetLocalTime(&st);
		fChange = st.wHour != stPrevious.wHour || st.wMinute != stPrevious.wMinute;

		hdc = GetDC(hwnd);
		SetIsotropic(hdc, cxClient, cyClient);

		SelectObject(hdc, GetStockObject(WHITE_PEN));
		DrawHands(hdc, &stPrevious, fChange);

		SelectObject(hdc, GetStockObject(BLACK_PEN));
		DrawHands(hdc, &st, TRUE);

		ReleaseDC(hwnd, hdc);

		stPrevious = st;
		InvalidateRect(hwnd, NULL, TRUE);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		SetIsotropic(hdc, cxClient, cyClient);
		DrawClock(hdc);
		DrawHands(hdc, &stPrevious, TRUE);

		EndPaint(hwnd, &ps);
		return 0;

	case WM_DESTROY:
		KillTimer(hwnd, ID_TIMER);
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}