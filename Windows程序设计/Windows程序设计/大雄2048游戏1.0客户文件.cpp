#include <windows.h>
#include "大雄2048游戏1.0.h"
#include <ctime>
#include <process.h>
#pragma comment(lib, "WINMM.LIB")  // 保证PlaySound()正常执行 #pragma将编译器指令置于源代码中

TCHAR	szAppName[]		= TEXT("大雄2048游戏1.0");	// 主窗口类及程序名
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
void	RandBox(Box DivBox[][4]);	// 随机显示一个Box

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	WNDCLASS	wndclass;

		// 主窗口类设置与注册

	wndclass.cbClsExtra			= 0;
	wndclass.cbWndExtra			= 0;
	wndclass.hbrBackground			= CreateSolidBrush(RGB(143, 146, 139));
	wndclass.hCursor				= LoadCursor(NULL, IDI_APPLICATION);
	wndclass.hIcon					= LoadIcon(NULL, IDC_ARROW);
	wndclass.hInstance				= hInstance;
	wndclass.lpfnWndProc			= WndProc;
	wndclass.lpszClassName			= szAppName;
	wndclass.lpszMenuName			= NULL;
	wndclass.style					= CS_HREDRAW | CS_VREDRAW;

	if(!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("注册主窗口类失败!"), TEXT("错误"), MB_ICONERROR);
		return 0;
	}

		// 创建主窗口

	HWND hwnd = CreateWindow(szAppName, szAppName, 
							  WS_OVERLAPPED |	// (重叠式窗口，该式样窗口带有一个标题栏和边框 ),
							  WS_CAPTION |		// (窗口具有标题栏（包含 WS_BODER)),
							  WS_SYSMENU,		// (具有 SYSTEM 菜单栏，还必须指定 WS_CAPTION 式样),
													// WS_THICKFRAM		(具有可调边框), 
							  //WS_MINIMIZEBOX,	// (具有最小化按钮),
													// WS_MAXIMIZEBOX	(具有最大化按钮)
							  200, 100, 300, 400,
							  NULL, NULL, hInstance, NULL);
	
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);
	
		// 消息循环

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

void PlayBackgroundMusic(void *)
{
	PlaySound(TEXT("大雄2048游戏1.0背景音乐.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC				hdc;
	PAINTSTRUCT		ps;
	static Box		BoxDiv[DIVISION][DIVISION];
	static int		cxClient, cyClient;
	static RECT		rcClient;
	bool			isMove = false;		// 用来标记是否在一次按键后有Box移动

	switch (message)
	{
	case WM_CREATE:

			// 创建所有的窗口(位置和大小未设定);

		for (int x = 0; x < DIVISION; x++)
			for (int y = 0; y < DIVISION; y++)
				BoxDiv[y][x].CreateBox(hwnd, y << 8 | x);
		
		PlaySound(TEXT("大雄2048游戏1.0开始音.wav"), NULL, SND_FILENAME | SND_SYNC);
		_beginthread(PlayBackgroundMusic, 0, nullptr);
		return 0;
	case WM_SIZE:
			
			// 给所有Box设置合适的大小和位置(默认不显示);

		GetClientRect(hwnd, &rcClient);
		for (int x = 0; x < DIVISION; x++)
		{
			for (int y = 0; y < DIVISION; y++)
			{
				BoxDiv[y][x].MoveBox(rcClient);
			}
		}

			// 随机显示一个Box, 数值 2 / 4 随机显示
		RandBox(BoxDiv);
		return 0;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
			for (int x = 0; x < DIVISION; x++)
				for (int y = 0; y < DIVISION; y++)
					if (BoxDiv[y][x].OffsetBox(BoxDiv, EnumLeft))
						isMove = true;
			break;
		case VK_UP:
			for (int x = 0; x < DIVISION; x++)
				for (int y = 0; y < DIVISION; y++)
					if (BoxDiv[y][x].OffsetBox(BoxDiv, EnumUp))
						isMove = true;
			break;
		case VK_RIGHT:
			for (int x = DIVISION - 1; x >= 0; x--)
				for (int y = DIVISION - 1; y >= 0; y--)
					if (BoxDiv[y][x].OffsetBox(BoxDiv, EnumRight))
						isMove = true;
			break;
		case VK_DOWN:
			for (int x = DIVISION - 1; x >= 0; x--)
				for (int y = DIVISION - 1; y >= 0; y--)
					if (BoxDiv[y][x].OffsetBox(BoxDiv, EnumDown))
						isMove = true;
			break;
		//case VK_SPACE:  // lParam: 373553 wParam: 32
		//	TCHAR szBuffer[100];
		//	wsprintf(szBuffer, TEXT("%d"), VK_SPACE);
		//	MessageBox(NULL, szBuffer, NULL, NULL);
			break;
		default: return 0;
		}
		PlaySound(TEXT("大雄2048游戏1.0按键音效.wav"), NULL, SND_FILENAME | SND_ASYNC);
		if (isMove)
			RandBox(BoxDiv);
		break;

		// 防止单击Box后由于Box有输入焦点而使得方向键失灵
	case WM_COMMAND:
		SetFocus(hwnd);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		for (int x = 0; x < DIVISION; x++)
			for (int y = 0; y < DIVISION; y++)
			{
				FrameRect(hdc, &BoxDiv[x][y].GetRcBoxPos(), (HBRUSH)GetStockObject(WHITE_BRUSH));
			}
		EndPaint(hwnd, &ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

void RandBox(Box DivBox[][4])
{
	int isHide[DIVISION * DIVISION] = {0};
	int Offset = 0;
		
		// 寻找没有显示的Box, 将其ID顺次放入isHide中

	for (int x = 0; x < DIVISION; x++)
		for (int y = 0; y < DIVISION; y++)
			if (DivBox[y][x].GetIsShow() == false)
				isHide[Offset++] = y << 8 |x;
	
		// 如果所有Box都显示了, 进行死亡判断

	if (0 == Offset)
	{
			// 判断是否上下Box有可以融合的
		for (int x = 0; x < DIVISION; x++)
			for (int y = 0; y < DIVISION - 1; y++)
				if (DivBox[x][y].GetBoxSumNum() == DivBox[x][y+1].GetBoxSumNum())
					return;

			// 判断是否左右Box有可以融合的
		for (int y = 0; y < DIVISION; y++)
			for (int x = 0; x < DIVISION - 1; x++)
				if (DivBox[x][y].GetBoxSumNum() == DivBox[x+1][y].GetBoxSumNum())
					return;

			// 如果没有可以合并的Box, 所有的Box又全部显示了, 游戏结束
		MessageBox(NULL, TEXT("大雄制作  QQ: 394899990  百度ID: 男儿志凌云"), TEXT("你输了"), NULL);
		SendMessage(GetParent(DivBox[0][0].GetBoxHwnd()), WM_DESTROY, 0, 0);
		return;
	}

		// 在没有显示的Box中随机挑选一个Box显示, 并将Box内的数随机设置一个2 / 4	

	srand((unsigned long)time(0));
	int yx = isHide[rand() % Offset];
	DivBox[yx >> 8][yx & 0xff].Show();
	srand((unsigned long)(time(0) + 25));
	DivBox[yx >> 8][yx & 0xff].SetBoxSumNum(rand() % 2 * 2 + 2);
}