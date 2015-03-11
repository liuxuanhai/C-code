#include "dxDigit.h"

	// 非静态数据成员能在类外定义, 静态数据成员在类外定义不用加上关键字static

		// 用于控制显示哪个数字
const BOOL	BaseDigit::fSevenSegment[10][7] ={
				1, 1, 1, 0, 1, 1, 1,  // 0
				0, 0, 1, 0, 0, 1, 0,  // 1
				1, 0, 1, 1, 1, 0, 1,  // 2
				1, 0, 1, 1, 0, 1, 1,  // 3
				0, 1, 1, 1, 0, 1, 0,  // 4
				1, 1, 0, 1, 0, 1, 1,  // 5
				1, 1, 0, 1, 1, 1, 1,  // 6
				1, 0, 1, 0, 0, 1, 0,  // 7
				1, 1, 1, 1, 1, 1, 1,  // 8
				1, 1, 1, 1, 0, 1, 1	};// 9

		// 用于控制所有数字的坐标
const POINT BaseDigit::ptSegment[7][6] = {
	7, 6, 11, 2, 31, 2, 35, 6, 31, 10, 11, 10,
	6, 7, 10, 11, 10, 31, 6, 35, 2, 31, 2, 11,
	36, 7, 40, 11, 40, 31, 36, 35, 32, 31, 32, 11,
	7, 36, 11, 32, 31, 32, 35, 36, 31, 40, 11, 40,
	6, 37, 10, 41, 10, 61, 6, 65, 2, 61, 2, 41,
	36, 37, 40, 41, 40, 61, 36, 65, 32, 61, 32, 41,
	7, 66, 11, 62, 31, 62, 35, 66, 31, 70, 11, 70 };

BaseDigit::BaseDigit(HWND _hwnd, int _x, int _y, int _digit)
{
	digit		= _digit;
	hwnd		= _hwnd;
	point.x		= _x;
	point.y		= _y;
	hdc			= GetDC(hwnd);
	hBrush		= CreateSolidBrush(RGB(255, 0, 0));
	hPen		= CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	SelectObject(hdc, hBrush);
	SelectObject(hdc, hPen);
}

BaseDigit::~BaseDigit()
{
	ReleaseDC	(hwnd, hdc);
	DeleteObject(hBrush);
	DeleteObject(hPen);
}

void BaseDigit::ShowDigit ()
{
		// 矫正视口原点位置
	SetViewportOrgEx(hdc, point.x, point.y, NULL);

		// 显示

	for (int iSeg = 0; iSeg < 7; iSeg++)
		if (fSevenSegment[digit][iSeg])
			Polygon(hdc, ptSegment[iSeg], 6);
}

void BaseDigit::SetColor(COLORREF color)
{
	HBRUSH hBrushPrev = hBrush;
	hBrush = CreateSolidBrush(color);
	hBrushPrev = (HBRUSH)SelectObject(hdc, hBrush);
	DeleteObject(hBrushPrev);
	ShowDigit();
}

void BaseDigit::SetColor(int r, int g, int b)
{
	SetColor(RGB(r, g, b));
}

void BaseDigit::HideDigit()
{
	SaveDC(hdc);
	HPEN hPenTemp = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	SelectObject(hdc, hPenTemp);		// 白色画笔选进设备环境, 默认的库白色画笔不能跟随缩放, 只能自己创建
	SelectObject(hdc, (HBRUSH)GetStockObject(WHITE_BRUSH));	// 白色画刷选进设备环境
	ShowDigit();	// 白色覆盖
	RestoreDC(hdc, -1);	// 恢复原来的设备环境
	DeleteObject(hPenTemp);
}

void BaseDigit::OffsetDigit(int x, int y)
{
	point.x += x;
	point.y += y;
	ShowDigit();
}

	// ZoomDigit Class

int ZoomDigit::WidthToHeigh()
{
	return (GetOriHeight() * ZoomWidth / GetOriWidth());
}

ZoomDigit::ZoomDigit(HWND hwnd, int x, int y, int _digit, int width) : BaseDigit(hwnd, x, y, _digit)
{
	ZoomWidth = width;
	ZoomHeigh = WidthToHeigh();	// 采用赋值的形式是为了便于阅读
	if (ZoomWidth != GetOriWidth())	// 如果设置了缩放数据, 执行缩放函数
	{
		//MessageBox(NULL, NULL, NULL, NULL);
		Zoom(ZoomWidth - GetOriWidth());
	}
}

void ZoomDigit::ShowDigit()
{
	//HideDigit();	// 将原来的隐藏掉
	SaveDC(hdc);
	SetMapMode(hdc, MM_ISOTROPIC);	// 将映射模式改变
	SetWindowExtEx(hdc, GetOriWidth(), GetOriHeight(), NULL);	// 窗口大小设置为一个Digit的原始大小
	SetViewportExtEx(hdc, ZoomWidth, ZoomHeigh, NULL);
	BaseDigit::ShowDigit();
	RestoreDC(hdc, -1);
}

void ZoomDigit::Zoom(int xOff)
{
	HideDigit();
	ZoomWidth += xOff;
	ZoomHeigh = WidthToHeigh();
	ShowDigit();
}