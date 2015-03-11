#define		SZAPPNAME	"p233击中测试"	
#define		DIVISIONS	5
#include	"DX_WinMain.cpp"

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static bool		fState[DIVISIONS][DIVISIONS];  // 方块的状态
	static int		cxBlock, cyBlock;  // 一个方块的长度和高度
	HDC				hdc;
	int				x, y;
	PAINTSTRUCT		ps;
	RECT			rect;

	switch (message)
	{
	case WM_SIZE:
		cxBlock = LOWORD(lParam) / DIVISIONS;
		cyBlock = HIWORD(lParam) / DIVISIONS;
		return 0;

	case WM_LBUTTONDOWN:
		x = LOWORD(lParam) / cxBlock;
		y = HIWORD(lParam) / cyBlock;

		if (x < DIVISIONS && y < DIVISIONS)
		{
			fState[x][y] ^= 1;  // 按位异或(Xor)

			rect.left	= x * cxBlock - 20;
			rect.top	= y * cyBlock - 20;
			rect.right	= (x + 1) * cxBlock - 20;
			rect.bottom	= (y + 1) * cyBlock - 20;

			InvalidateRect(hwnd, &rect, FALSE);  // 这里FALSE和TRUE的区别???????????? 这里写的FALSE表示该区域不进行背景画刷擦除, 但是WM_PAINT中的Rectangle绘制的矩形框默认内部填充颜色(白色)将内部的对角线给覆盖了;
		}
		else
			MessageBeep(0);  // 如果客户区的宽度或高度不能被5整除, 客户区的左边或底部就会出现一个小长条区域, 不会被矩形覆盖, 这里实现了一个错误处理, 在鼠标单击这片区域的时候, 程序会调用MessageBeep函数进行响应;
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		for (x = 0; x < DIVISIONS; x++)
			for (y = 0; y < DIVISIONS; y++)
			{
				Rectangle(hdc, x * cxBlock, y * cyBlock, (x + 1) * cxBlock, (y + 1) * cyBlock);

				if (fState[x][y])
				{
					MoveToEx	(hdc, x * cxBlock, y * cyBlock, NULL);
					LineTo		(hdc, (x + 1) * cxBlock, (y + 1) * cyBlock);
					MoveToEx	(hdc, x * cxBlock, (y + 1) * cyBlock, NULL);
					LineTo		(hdc, (x + 1) * cxBlock, y * cyBlock);
				}
			}

		EndPaint(hwnd, &ps);
		return 0;

	case WM_CLOSE:
		if (MessageBox(hwnd, TEXT("确认退出?"), TEXT("退出"), MB_YESNO) != IDYES)
			return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}