#include <Windows.h>
#include <cstdlib>
#include <ctime>
#define		SNAKEWIDTH			20		// 蛇身宽度
#define		SNAKEMOVETIME		300		// 蛇的移动时间间隔(毫秒)
#define		SNAKEMOVEDISTANCE	20		// 蛇的移动距离间隔(像素)
const RECT	SNAKEINITPOS		= {100, 100, 100 + SNAKEWIDTH, 100 + SNAKEWIDTH};
int			iNum_Snake			= 4;	// 蛇身长度(这里初始化的是初始长度)
int			xMove				= SNAKEWIDTH;	// 蛇x方向移动距离
int			yMove				= 0;			// 蛇y方向移动距离
int			xPrevMove;							// 在出现蛇吃自己脖子情况后要恢复原来的移动状态
int			yPrevMove;					

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void initSnake(RECT *, BOOL = FALSE);			// 初始化蛇的坐标
void drawSnake(HDC, RECT *);					// 根据坐标画蛇
void MoveSnake(RECT *);							// 移动蛇
void SetFoodPos(HWND, RECT &, const RECT *);	// 设置食物位置
BOOL isDied(HWND, const RECT *);				// 死亡判断
BOOL isEat(RECT *, const RECT *);				// 判断是否吃到了食物 如果吃到了, 重新设置蛇数组坐标

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	static TCHAR	szAppName[] = TEXT("大雄贪吃蛇1.0");
	MSG				msg;
	WNDCLASS		wndclass;
	HWND			hwnd;

	wndclass.cbClsExtra		= 0;
	wndclass.cbWndExtra		= 0;
	wndclass.hbrBackground		= (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.hCursor			= LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon				= LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hInstance			= hInstance;
	wndclass.lpfnWndProc		= WndProc;
	wndclass.lpszClassName		= szAppName;
	wndclass.lpszMenuName		= NULL;
	wndclass.style				= CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wndclass);

	hwnd = CreateWindow(szAppName, szAppName,
						WS_OVERLAPPEDWINDOW, 
						CW_USEDEFAULT, CW_USEDEFAULT,
						CW_USEDEFAULT, CW_USEDEFAULT,
						NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static RECT		rcSnake[1000] = {SNAKEINITPOS.left, SNAKEINITPOS.top, SNAKEINITPOS.right, SNAKEINITPOS.bottom};
	initSnake		(rcSnake);
	static int		cxClient, cyClient;
	PAINTSTRUCT		ps;
	HDC				hdc;
	static RECT		rcFood;  // 随机食物位置

	switch (message)
	{
	case WM_CREATE:

			// 开启计数器

		SetTimer(hwnd, 1, SNAKEMOVETIME, NULL);  // 使用计时器ID为1的计时器

		break;

	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);

			// 设置随机食物位置

		SetFoodPos(hwnd, rcFood, rcSnake);

		return 0;

	case WM_TIMER:
			// 移动蛇

		MoveSnake(rcSnake);
		
			// 死亡判断
	
		if (isDied(hwnd, rcSnake))
		{
			*rcSnake = SNAKEINITPOS;
			initSnake(rcSnake, TRUE);	// 初始化蛇的位置, TRUE使得initSnake函数能够第二次使用
			KillTimer(hwnd, 1);		// 停止发送WM_TIMER, 游戏结束
			MessageBox(hwnd, TEXT("你死了!"), TEXT("大雄哥哥温馨提醒"), MB_OKCANCEL);
		}

			// 是否吃到了食物

		if (isEat(rcSnake, &rcFood))
		{
			SetFoodPos(hwnd, rcFood, rcSnake);  // 更新食物
			iNum_Snake++;
		}

			// 更新客户区

		InvalidateRect(hwnd, NULL, TRUE);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		
			// 画蛇

		drawSnake(hdc, rcSnake);

			// 画食物

		Rectangle(hdc, rcFood.left, rcFood.top, rcFood.right, rcFood.bottom);
		InvertRect(hdc, &rcFood);

		EndPaint(hwnd, &ps);
		return 0;

	case WM_KEYUP:
		int xTemp;
		int yTemp;
		xTemp = xMove;
		yTemp = yMove;

		switch (wParam)
		{
		case VK_UP:		xMove = 0;				yMove = -SNAKEWIDTH;	break;
		case VK_DOWN:	xMove = 0;				yMove = SNAKEWIDTH;		break;
		case VK_LEFT:	xMove = -SNAKEWIDTH;	yMove = 0;				break;
		case VK_RIGHT:	xMove = SNAKEWIDTH;		yMove = 0;				break;
		}

		if (xTemp != xMove || yTemp != yMove)  // 防止出现如向上移动的时候反复按VK_DOWN使得xPrevMove也保存"蛇吃脖子"的移动错误;
		{
			xPrevMove = xTemp;
			yPrevMove = yTemp;
		}
		return 0;

	case WM_DESTROY:
		KillTimer(hwnd, 1);  // 关闭计数器1
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

void initSnake(RECT * rcSnake, BOOL b)
{
	static BOOL flag = FALSE;
	if (flag && !b)
		return;
	for (int i = 1; i < iNum_Snake; i++)
	{
		rcSnake[i] = rcSnake[i-1];
		OffsetRect(&rcSnake[i], -SNAKEWIDTH, 0);
	}
	flag = TRUE;
}

void drawSnake(HDC hdc, RECT * rcBeg)
{
	HBRUSH hPrevBrush = (HBRUSH)GetCurrentObject(hdc, OBJ_BRUSH);
		
		// 画蛇头

	Rectangle(hdc, rcBeg->left, rcBeg->top, rcBeg->right, rcBeg->bottom);
	SelectObject(hdc, (HBRUSH)GetStockObject(BLACK_BRUSH));
	
		// 画蛇身

	for (int i = 1; i < iNum_Snake; i++)
		Rectangle(hdc, rcBeg[i].left, rcBeg[i].top, rcBeg[i].right, rcBeg[i].bottom);
	
	SelectObject(hdc, hPrevBrush);
}

void MoveSnake(RECT * rcSnake)
{

		// 移动蛇头

	RECT rcTemp = *rcSnake;
	OffsetRect(&rcTemp, xMove, yMove);
	
		// 移除蛇头吃蛇脖子的错误

	POINT ptTemp = {rcTemp.left + SNAKEWIDTH / 2, rcTemp.top + SNAKEWIDTH / 2};
	if (PtInRect(&rcSnake[1], ptTemp))
	{
		xMove = xPrevMove;
		yMove = yPrevMove;
		return;
	}

		// 移动蛇身

	for (int i = iNum_Snake - 1; i > 0; i--)
		rcSnake[i] = rcSnake[i-1];
	rcSnake[0] = rcTemp;
}

BOOL isDied(HWND hwnd, const RECT * rcSnake)
{
	RECT rcClient;
	GetClientRect(hwnd, &rcClient);
	POINT ptTemp = {rcSnake->left + SNAKEWIDTH / 2, rcSnake->top + SNAKEWIDTH / 2};
	if (PtInRect(&rcClient, ptTemp))  // 撞墙判断
	{
		for (int i = 4; i < iNum_Snake; i++)  
			if (PtInRect(&rcSnake[i], ptTemp))  // 自吃判断
				return TRUE;
	}
	else
		return TRUE;
	return FALSE;
}

void SetFoodPos(HWND hwnd, RECT & rcFood, const RECT * rcSnake)
{
	RECT rcClient;
	GetClientRect(hwnd, &rcClient);
		
		// 生成随机位置

	srand(rand());
	rcFood.left		= rand() % rcClient.right  / SNAKEWIDTH * SNAKEWIDTH;  // 保证食物和蛇身在同一水平线上
	rcFood.top		= rand() % rcClient.bottom / SNAKEWIDTH * SNAKEWIDTH;
	rcFood.right	= rcFood.left + SNAKEWIDTH;
	rcFood.bottom	= rcFood.top  + SNAKEWIDTH;

	////	// 防止随机到蛇身上

	//int flag = 0;
	//for (int i = 0; i < iNum_Snake; i++)  
	//	if (rcSnake[i].left		== rcFood.left	&&
	//		rcSnake[i].right	== rcFood.right	&&
	//		rcSnake[i].top		== rcFood.top	&&
	//		rcSnake[i].bottom	== rcFood.bottom)
	//		SetFoodPos(hwnd, rcFood, rcSnake);
			
}

BOOL isEat(RECT * rcSnake, const RECT * rcFood)
{
	POINT ptTemp = {rcSnake->left + SNAKEWIDTH / 2, rcSnake->top + SNAKEWIDTH / 2};
	if (PtInRect(rcFood, ptTemp))
	{
		for (int i = iNum_Snake - 1; i > 0; i--)
			rcSnake[i] = rcSnake[i-1];
		rcSnake[0] = *rcFood;	
		return TRUE;
	}
	return FALSE;
	
}