#include <windows.h>

	// 基础数字类, 只能在给定位置显示一个固定大小(42 x 72)的数字

class BaseDigit
{
private:
	static const int DigitOriWidth = 42;
	static const int DigitOriHeight = 72;	// 最初的Digit的宽度和高度
	int		digit;		// 显示的数字
	HWND	hwnd;		// 写在这个窗口中
	HBRUSH	hBrush;		// 给数字上色的画刷, 默认是红色
	HPEN	hPen;		// 数字的边框, 默认是黑色
	static const BOOL	fSevenSegment[10][7];
	static const POINT	ptSegment[7][6];
protected:
	POINT	point;		// 从这个位置开始写, 左上角坐标
	HDC		hdc;		// GetDC()获取
public:
	BaseDigit(HWND, int x = 0, int y = 0, int _digit = 0);
	virtual ~BaseDigit();
	virtual void ShowDigit();
	void SetColor(COLORREF);	// 设置数字的颜色
	void SetColor(int r, int g, int b);
	void HideDigit();	// 隐藏
	void OffsetDigit(int xOff, int yOff);
	static int GetOriWidth() { return DigitOriWidth; }
	static int GetOriHeight() { return DigitOriHeight; }
	void SetDigit(int _digit) { digit = _digit; }
};

	// 添加缩放的特性

class ZoomDigit : public BaseDigit
{
private:
	int ZoomWidth;	// MM_ISOTROPIC模式下的视口宽度	默认42
	int ZoomHeigh;	// MM_ISOTROPIC模式下的视口高度	默认72
	int WidthToHeigh();
public:
	ZoomDigit(HWND, int x, int y, int _digit = 0, int width = GetOriWidth());
	virtual ~ZoomDigit() {}
	void Zoom(int xOff);
	void ShowDigit();
};