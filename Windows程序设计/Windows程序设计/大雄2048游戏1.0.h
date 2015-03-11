#ifndef DAXIONG2048_H_
#define DAXIONG2048_H_
#include <windows.h>
const  int	DIVISION =	4;
enum EnumOffsetBox{EnumLeft, EnumRight, EnumUp, EnumDown};
class Box
{
private:
	int		_iBoxSumNum;	// Box里面的数
	TCHAR	_szBoxSumNum[5];// Box里面的数的字符串形式
	int		_iBoxID;		// Box的ID
	HWND	_hwnd;			// Box句柄
	bool	_isShow;		// Box是否显示出来
	RECT	_rcBoxPos;		// Box的位置大小等
	RECT	_rcMainClient;	// 主窗口RECT
	HWND	_hwndMain;		// 主窗口句柄
public:
	void CreateBox(HWND hwnd, const int iBoxID, const int BoxSumNum = -1);	// 默认-1(内部进行2 / 4随机);
	Box();

	void MoveBox(const RECT & rcClient);	// 将Box移动到对应的位置
	void Show();
	void Hide();
	bool OffsetBox(Box [][4], EnumOffsetBox);
	RECT GetRcBoxPos() const {return _rcBoxPos;}
	HWND GetBoxHwnd() const {return _hwnd;}
	int	 GetBoxSumNum() const {return _iBoxSumNum;}
	bool GetIsShow() const {return _isShow;};
	void SetBoxSumNum(const int n) {_iBoxSumNum = n; wsprintf(_szBoxSumNum, TEXT("%d"), _iBoxSumNum); SetWindowText(_hwnd, _szBoxSumNum);}
};

#endif