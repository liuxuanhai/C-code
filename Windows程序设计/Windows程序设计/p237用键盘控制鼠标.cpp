#define	SZAPPNAME	"p237用键盘控制鼠标"
#include			"DX_WinMain.cpp"
#define DIVNUM		5

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT	ps;
	HDC			hdc;
	static int	cxClient, cyClient, cxBlock, cyBlock;
	static bool	fBlock[DIVNUM][DIVNUM];

	switch (message)
	{
	case WM_SIZE:
		cxClient	= LOWORD(lParam);
		cyClient	= HIWORD(lParam);
		cxBlock		= cxClient /  DIVNUM;
		cyBlock		= cyClient / DIVNUM;
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		for (int x = 0; x < DIVNUM; x++)
		for (int y = 0; y < DIVNUM; y++)
		{
			RECT temp;
			SetRect(&temp, x * cxBlock, y * cyBlock, (x + 1) * cxBlock, (y + 1) * cyBlock);
			Rectangle(hdc, temp.left, temp.top, temp.right, temp.bottom);
			if (fBlock[x][y] == TRUE)
				InvertRect(hdc, &temp);
		}

		EndPaint(hwnd, &ps);
		return 0;

	case WM_LBUTTONDOWN:
		int x, y;
		x = LOWORD(lParam) / cxBlock;
		y = HIWORD(lParam) / cyBlock;
		fBlock[x][y] ^= 1;
		InvalidateRect(hwnd, NULL, FALSE);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

//////////////// 加上键盘接口的部分代码 //////////////////
	case WM_SETFOCUS:
		ShowCursor(TRUE);
		return 0;

	case WM_KILLFOCUS:
		ShowCursor(FALSE);
		return 0;

	case WM_KEYDOWN:
		POINT point;
		GetCursorPos(&point);
		ScreenToClient(hwnd, &point);

		x = max(0, min(DIVNUM - 1, point.x / cxBlock));
		y = max(0, min(DIVNUM - 1, point.y / cyBlock));

		switch (wParam)
		{
		case VK_UP:
			y--;
			break;

		case VK_DOWN:
			y++;
			break;

		case VK_LEFT:
			x--;
			break;

		case VK_RIGHT:
			x++;
			break;

		case VK_HOME:
			x = y = 0;
			break;

		case VK_END:
			x = y = DIVNUM - 1;
			break;

		case VK_RETURN:
		case VK_SPACE:
			SendMessage(hwnd, WM_LBUTTONDOWN, MK_LBUTTON, MAKELONG(x * cxBlock, y * cyBlock));
			break;
		}
		x = (x + DIVNUM) % DIVNUM;
		y = (y + DIVNUM) % DIVNUM;

		point.x = x * cxBlock + cxBlock / 2;
		point.y = y * cyBlock + cyBlock / 2;

		ClientToScreen(hwnd, &point);
		SetCursorPos(point.x, point.y);
		return 0;
/////////////////////////////////////////////////////////

	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}