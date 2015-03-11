
// 1. 创建窗口类, 并赋值    2. register窗口    3. 在内存Create窗口(返回窗口句柄)    4. 在显示器show窗口    5. update窗口

// MSG 消息结构 WNDCLASS 窗口类结构 PAINTSTRUCT 绘制结构 RECT 矩形结构
// HINSTANCE 实例句柄-程序本身 HWND 窗口句柄 HDC 设备环境句柄

#include <windows.h>
#pragma comment(lib, "WINMM.LIB")  // 保证PlaySound()正常执行 #pragma将编译器指令置于源代码中

// 窗口过程函数 这个函数将会处理所有作为其参数的窗口的所有消息, 这个窗口是窗口类创建的, 窗口类指定了窗口过程, 按此窗口类创建的多个窗口都是用这一个窗口过程;
// 窗口过程的前四个字段是与MSG结构的额前四个字段一一对应的
LRESULT /*等价于LONG*/ CALLBACK /*WndProc函数的类型*/ WndProc(HWND,  // 与MSG结构的第一个参数对应 接收消息的窗口的句柄, 它与CreatWindow函数返回的句柄相同
													  UINT,  // 与MSG结构的第二个参数message对应, 是一个标示消息的数字
													  WPARAM, LPARAM);  // 这两个参数用于提供该消息更加丰富的信息

int WINAPI /*WinMain函数的类型*/ WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, // PSTR 表示一个指向非宽字符串的指针, 即char*
				   int iCmdShow)  // 该参数决定着窗口在屏幕上初始显示的形式(正常/最大化/最小化)
{
	static TCHAR szAppName[] = TEXT("HelloWin");
	HWND       hwnd;
	MSG        msg;
	WNDCLASS   wndclass;  // 窗口类确定了处理窗口消息的窗口过程

	wndclass.style         = CS_HREDRAW | CS_VREDRAW;  // 无论何时窗口的水平尺寸(CS_HREDRAW)或垂直尺寸(CS_VREDRAW)被改变, 所有基于该窗口类的窗口都将被重新绘制 只要尺寸改变, 立马使 !整个窗口! 失效, 然后就发送WM_PAINT进行重绘
							// 这里当尺寸改变的时候不是使客户区无效而是使 !整个窗口无效!;

	// 基于该窗口类的所有窗口的窗口过程的地址
	wndclass.lpfnWndProc   = WndProc;  // lpfn(long pointer to a function 指向函数的长指针)
	
	wndclass.cbWndExtra    = 0;  // cb表示字节数, 这里表示这个变量可以被设置为一个"字节数"
	wndclass.cbClsExtra    = 0;
	wndclass.hInstance     = hInstance;  // 表示应用程序的实例句柄
	wndclass.hIcon         = LoadIcon(NULL, IDI_APPLICATION/*IDI(ID for an icon)*/);  // 为所有基于该窗口类的窗口设定一个图标 为了获取预定义图标的句柄, 需要调用函数LoadIcon, 并将函数的第一个参数设为NULL LoadIcon返回该图标的句柄
	wndclass.hCursor       = LoadCursor(NULL, IDC_ARROW);  // 加载鼠标光标, 以供程序使用
	wndclass.hbrBackground /*hbr表示"画刷的句柄"(handle to a brush)*/ = (HBRUSH)GetStockObject(WHITE_BRUSH);  // 获取一个图形对象. 这里是一个用来对窗口的背景进行重绘的画刷
	wndclass.lpszMenuName  = NULL;
	wndclass.lpszClassName = szAppName;  // 窗口类的名称

	if (!RegisterClass(&wndclass))  // 为应用程序的窗口注册一个窗口类
	{
		MessageBox(NULL, TEXT("This program requires Windows NT!"), szAppName, MB_ICONERROR);  // 显示消息框
		return 0;
	}

	// 基于窗口类创建一个窗口 CreatWindow()的返回值为一个指向所创建窗口的句柄 windows中每一个窗口都有一个句柄, 在程序中可以用句柄对窗口进行引用
	hwnd = CreateWindow(szAppName,   // window class name  窗口类名称 名称为szAppName, 即程序刚刚注册的窗口的名称. 我们所要创建的窗口正是通过这种方式与窗口类建立了关联
		TEXT("The Hello Program"),    // window caption(标题)
		WS_OVERLAPPEDWINDOW,          // window style  这里设置的是一个标准的窗口风格
		CW_USEDEFAULT,                // initial x position  指定了窗口左上角相对于屏幕左上角的初始位置
		CW_USEDEFAULT,                // initial y position
		CW_USEDEFAULT,                // initial x size
		CW_USEDEFAULT,                // initial y size
		NULL,                         // parent window handle  如果新建窗口为顶级窗口(例如应用程序窗口), 这里应该设置成NULL
		NULL,                         // window menu handle 
		hInstance,                    // program instance handle  程序实例句柄
		NULL);                        // creation parameters n. 参数；参量（parameter的复数） 创建参数 可以将该参数指向某些数据成员, 以便后续在程序中加以引用

	// 当CreatWindow调用返回时, 窗口已在Windows内部创建, windows已经分配了一块内存来保存CreatWindow调用中指定的窗口信息以及一些其他信息. windows可以通过句柄来获取这些信息
	// 但是, 要将窗口显示在屏幕上, 仅仅这样是不够的 

	// 在屏幕中显示窗口  此时显示的窗口是无效的, 因为应用程序未在客户区上绘制任何东西, UpdateWIndow会post消息WM_PAINT
	ShowWindow(hwnd,  // 第一个参数是CreatWindow在内存中创建的窗口的句柄
		iCmdShow);      // 第二个参数是WinMain函数所接受的iCmdShow值, 该参数决定着窗口在屏幕上初始显示的形式(正常/最大化/最小化), 如果是SW_SHOWNORMAL, 则窗口的客户区将在窗口类中指定的背景画刷擦除;

	// 如果ShowWindow()的第二个参数是SW_SHOWNORMAL, 则该窗口的客户区将被在窗口类中所指定的背景画刷擦除
	UpdateWindow(hwnd);  // 指示窗口对其自身进行重绘
	// 这是通过窗口过程发送一条WM_PAINT消息而完成的重绘

	while (GetMessage(&msg,  // 只有在GetMessage得到了一条消息, 他才会返回;
		NULL, 0, 0))  // NULL, 0, 0表明改程序希望获取由该程序创建的所有窗口的消息;
	{
		TranslateMessage(&msg);  // 翻译一些键盘消息
		DispatchMessage(&msg);  // 将msg结构返还给windows, 接下来 windows会将这条消息发送给合适的窗口过程来处理
		// 只有在窗口过程执行完了, DispatchMessage才会返回;
	}

	return msg.wParam;  // msg结构的wParam字段是传递给PostQuitMessage函数的值, 通常情况下为0, 该返回语句将从WinMain中退出来并结束程序
}

LRESULT CALLBACK WndProc(HWND hwnd,  // 通过hwnd可以知道是基于同一窗口类创建的多个窗口的那个窗口接收到了消息
						 UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC         hdc;    // 设备环境句柄
	PAINTSTRUCT ps;     // 绘图结构
	RECT        rect;   // 矩形结构

	switch (message)
	{
	// WM_CREATE 是WndProc处理的第一条消息 当windows在WinMain函数中处理CreatWindow函数调用的时候, WndProc将接受到该消息
	// 在程序调用CreateWindow时, windows完成其必须的操作, 在此过程中, windows对WndProc进行调用, 并将其第一个参数设置为该窗口的句柄, 并将第二个参数设置为WM_CREATE
	// 通常, 窗口过程会在WM_CREATE消息期间对窗口进行一次性的初始化;
	case WM_CREATE:
		//MessageBox(hwnd, TEXT("无法播放声音!"), TEXT("SoundError"), 0);
		PlaySound(TEXT("C:\\Users\\daxiong\\Desktop\\vs2012\\code\\Windows程序设计\\Windows程序设计\\p039创建一个窗口.wav"), NULL, // 只有当声音文件是一个资源时才有用;
			SND_FILENAME | SND_ASYNC);  // 第一个参数是一个文件名且该段声音是以异步方式播放的, 即当所指定的声音文件开始播放的时候PlaySound函数立即返回, 无需等待该文件播放结束;
		return 0;  // 当窗口过程对消息进行处理了以后应该返回0
	
	// 当窗口的部分或全部"无效"且必须"更新"的时候, 应用程序会得到此通知, 这也就意味着窗口必须重绘
	// 客户区变为无效的情况: 1. 当窗口被首次创建的时候, 整个客户区都是无效的, 因为此时应用程序尚未在该窗口上绘制任何东西   -- 第一条WM_PAINT消息在应用程序调用WinMain中的UpdateWindow时出现, 将指示窗口过程在窗口客户区进行重绘
						//	 2. 在调整窗口的尺寸的时候, 客户区也会变为无效  --  前面指示wndclass结构的style字段为CS_HREDRAM和CS_VREDRAM, 这就是指示windows当窗口尺寸发生变化的时候, !整个窗口! 都应宣布无效, 在此之后, 窗口过程将接收到一条WM_PAINT消息
						//   3. 最小化窗口, 然后将窗口恢复.  --  在图形环境中, 这种情况下要保存的东西太多了, 对此, windows采取的策略是宣布窗口无效, 窗口过程接收到WM_PAINT消息后, 会自行恢复窗口内容
						//   4. 在屏幕中拖动窗口导致窗口之间发生重叠时, 当被覆盖的区域再后来不再被遮挡时, ?窗口?被标记为无效, 窗口过程收到WM_PAINT
	// 如果窗口过程不对WM_PAINT消息进行处理, 则该类消息必须交给DefWindowsProc来处理, 而DefWindowsProc所做的只是简单的一次调用BeginPaint和EndPaint, 使得客户区变得有效
	case WM_PAINT:  // 对WM_PAINT消息的处理通常从调用BeginPaint函数开始, 从EndPaint函数结束
		// BeginPaint函数 1. 擦去无效区域的背景以便绘图(在WinMain初始化的时候, 用于注册窗口类的WNDCLASS结构中的hbrBackground字段指定了一个画刷, windows就使用这个画刷来擦除背景)    2. 填充ps结构的各个字段
		hdc = BeginPaint(hwnd, &ps);  // BeginPaint函数调用将使得整个客户区有效, 并返回一个"设备环境句柄" 设备环境句柄是指的物理输出设备(如显示器)及其驱动设备. 我们需要设备环境句柄以在窗口的客户区显示文本和图形 设备环境句柄无法在客户区以外的区域进行绘制
		
		GetClientRect(hwnd, &rect);  // 将窗口句柄的客户区宽度和高度信息传递给rect矩形结构

		DrawText(hdc, TEXT("Hello, the coding young man!"), -1/*表示文本字符串以0结尾*/, &rect,  // 在rect限制的矩形内显示
			DT_SINGLELINE | DT_CENTER | DT_VCENTER/*文本应该在rect限定的矩形区域单行显示, 并且水平和垂直居中*/);  // 显示一个文本字符串
		EndPaint(hwnd, &ps);  // EndPaint函数用于释放设备环境句柄, 使其无效
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);  // 将"WM_QUIT(退出)"消息插入消息队列 GetMessage函数对WM_QUIT消息返回0, 使得退出消息循环
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);  // 执行默认的消息处理 所有窗口过程不进行处理的消息都必须传给名称为DefWindowProc函数, 这个函数的返回值必须从窗口过程返回
}