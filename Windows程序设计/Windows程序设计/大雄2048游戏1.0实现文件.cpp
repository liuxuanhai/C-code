#include "大雄2048游戏1.0.h"
#include <ctime>
void Box::CreateBox(HWND hwnd, const int iBoxID , const int BoxSumNum)
{
	_hwndMain	= hwnd;
	_iBoxID		= iBoxID;
	srand((unsigned int)time(0));
	if (BoxSumNum <= 0)
		_iBoxSumNum = rand() % 2 * 2 + 2;	// 如果没有给定值, 那么随机出2或4
	else
		_iBoxSumNum	= BoxSumNum;
	wsprintf(_szBoxSumNum, TEXT("%d"), _iBoxSumNum);	// 将数字转换成字符串形式
	_hwnd = CreateWindow(TEXT("button"), _szBoxSumNum,
						 WS_CHILDWINDOW,		// 默认子窗口不显示
						 0, 0, 0, 0,
						 hwnd, (HMENU)(_iBoxID), 
						 (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
}

Box::Box()
{
	_iBoxSumNum		= -1;
	_szBoxSumNum[0] = 'N';
	_szBoxSumNum[1] = '\0';
	_iBoxID			= -1;
	_hwnd			= (HWND)-1;
	_isShow			= false;
	SetRect(&_rcBoxPos		, -1, -1, -1, -1);
	SetRect(&_rcMainClient	, -1, -1, -1, -1);
	_hwndMain		= (HWND)-1;
}

void Box::MoveBox(const RECT & _rcClient)
{
	int x = _iBoxID & 0xff;
	int y = _iBoxID >> 8;

		// Box左上角的位置
	POINT	ptPos;
	ptPos.x = _rcClient.right	/ DIVISION * x;
	ptPos.y = _rcClient.bottom	/ DIVISION * y;

		// Box的大小
	int cx = _rcClient.right	/ DIVISION;
	int cy = _rcClient.bottom	/ DIVISION;
	MoveWindow(_hwnd, ptPos.x + 3,	 ptPos.y + 3, cx - 4, cy - 4,TRUE);

	SetRect(&_rcBoxPos, ptPos.x, ptPos.y, ptPos.x + cx, ptPos.y + cy);
	_rcMainClient = _rcClient;
}

void Box::Show()
{
	_isShow = true;
	ShowWindow(_hwnd, SW_SHOW);
}

void Box::Hide()
{
	_isShow = false;
	ShowWindow(_hwnd, SW_HIDE);
}

	// 这里是Box & 而不是Box
Box & SelectDir(Box BoxDiv[][4], EnumOffsetBox of, int & x, int & y, int flag = 0)
{
	switch (of)
	{
	case EnumLeft:	
		if (flag)
			return BoxDiv[y][x--];
		else 
			return BoxDiv[y][x-1];
	case EnumRight:	
		if (flag)
			return BoxDiv[y][x++];
		else
			return BoxDiv[y][x+1];
	case EnumUp:
		if (flag)
			return BoxDiv[y--][x];
		else
			return BoxDiv[y-1][x];
	case EnumDown: 
		if (flag)
			return BoxDiv[y++][x];
		else
			return BoxDiv[y+1][x];
	default:
		MessageBox(NULL, TEXT("SelectDir函数出错"), NULL, NULL);
		return BoxDiv[x][y];
	}
}

bool Box::OffsetBox(Box BoxDiv[][4], EnumOffsetBox of)
{
	int x = _iBoxID & 0xff;
	int y = _iBoxID >> 8;
	int flag = 0;	// 用于标记是否移动了Box

		// ps: 注释以左移为例子

	for (;;)
	{
			// 如果要左移的Box是显示的
		if (BoxDiv[y][x].GetIsShow())
		{
				// 如果目标Box在最左端
		if ((of == EnumLeft		&& x == 0)				||	// 最左端判断
			(of == EnumRight	&& x == DIVISION - 1)	||	// 最右端判断
			(of == EnumUp		&& y == 0)				||	// 最上端判断
			(of == EnumDown		&& y == DIVISION - 1))		// 最下端判断
			break;

				// 如果目标Box左边有Box显示
			if (SelectDir(BoxDiv, of, x, y).GetIsShow())
			{	
					// 如果左Box与目标Box里面的数相同
				if (SelectDir(BoxDiv, of, x, y).GetBoxSumNum() == BoxDiv[y][x].GetBoxSumNum())
				{
						// 设置左Box为两个Box的和, 隐藏目标Box
					SelectDir(BoxDiv, of, x, y).SetBoxSumNum(SelectDir(BoxDiv, of, x, y).GetBoxSumNum() + BoxDiv[y][x].GetBoxSumNum());
					if (SendMessage(BoxDiv[y][x]._hwnd, BM_GETSTATE, 0, 0))
						SendMessage(BoxDiv[y][x]._hwnd, BM_SETSTATE, 0, 0);	// 如果Box要被隐藏, 这里保证它隐藏之前是非按下状态, 以防止下次显示的时候是按下的
					SendMessage(SelectDir(BoxDiv, of, x, y)._hwnd, BM_SETSTATE, 1, 0);	// 让融合了的Box显示被按下的状态
					SelectDir(BoxDiv, of, x, y, 1).Hide();
					flag = 1;
					break;
				}
				else
					break;
			}	// 如果目标左边Box不显示
			else
			{
				SelectDir(BoxDiv, of, x, y).SetBoxSumNum(BoxDiv[y][x].GetBoxSumNum());
				SelectDir(BoxDiv, of, x, y).Show();
				if (SendMessage(BoxDiv[y][x]._hwnd, BM_GETSTATE, 0, 0))
					SendMessage(BoxDiv[y][x]._hwnd, BM_SETSTATE, 0, 0);	// 如果Box要被隐藏, 这里保证它隐藏之前是非按下状态, 以防止下次显示的时候是按下的
				SelectDir(BoxDiv, of, x, y, 1).Hide();
				flag = 1;
			}
			x = min(DIVISION - 1, max(0, x));
			y = min(DIVISION - 1, max(0, y));
		}
		else
			break;	
	}
	return flag == 1;
}