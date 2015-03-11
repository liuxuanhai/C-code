// 当二级线程结束后, 他们需要通知主线程, 或者, 有时主线程也需要通知二级线程终止运行, 下面的内容就展示了如何实现主线程和二级线程之间的交互
// 在客户区单击鼠标, 窗口过程把iStatus设置成STATUS_WORKING, 并初始化PARAMS的两个字段, hwnd字段被设置为窗口句柄, bContinue被设置为TRUE, 接着窗口过程调用_beginthread()函数(而不是直接在WM_CREATE的时候调用这个函数)
// KillThread函数只有在正常退出没法实现的时候才使用, 这主要是为了防止资源(比如分配的内存)无法释放, 如果内存在退出时没有被释放, 他就会一直占据那块内存, 线程不是进程: 因为同一进程里分配的资源会被所有线程共享, 所以线程退出时资源不会被自动释放, 好的程序设计要求线程在结束时释放由它分配的资源
#include <windows.h> 
#include <math.h> 
#include <process.h> 
#define REP      1000000	// 100W
#define STATUS_READY		0
#define STATUS_WORKING      1 
#define STATUS_DONE			2 
#define WM_CALC_DONE		(WM_USER + 0)	// 成功进行100W次计算
#define WM_CALC_ABORTED     (WM_USER + 1)	// 在进行计算的时候被主线程(用户的右键操作)终止
typedef struct	// 定义一个静态结构用来在窗口过程和二级线程之间共享数据
{ 
	HWND hwnd ; 
	BOOL bContinue ;	// 用来指示线程是否应该继续运算
} PARAMS, *PPARAMS ; 
LRESULT APIENTRY	WndProc (HWND, UINT, WPARAM, LPARAM) ; 
int		WINAPI		WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) 
{ 
	static TCHAR	szAppName[] = TEXT ("BigJob1") ; 
	HWND			hwnd ; 
	MSG				msg ; 
	WNDCLASS		wndclass ; 
	
	wndclass.style				= CS_HREDRAW | CS_VREDRAW ; 
	wndclass.lpfnWndProc		= WndProc ; 
	wndclass.cbClsExtra			= 0 ; 
	wndclass.cbWndExtra			= 0 ; 
	wndclass.hInstance			= hInstance ; 
	wndclass.hIcon				= LoadIcon (NULL, IDI_APPLICATION) ; 
	wndclass.hCursor			= LoadCursor (NULL, IDC_ARROW) ; 
	wndclass.hbrBackground		= (HBRUSH) GetStockObject (WHITE_BRUSH) ; 
	wndclass.lpszMenuName		= NULL ; 
	wndclass.lpszClassName		= szAppName ; 

	if (!RegisterClass (&wndclass)) 
	{ 
		MessageBox (  NULL, TEXT ("This program requires Windows NT!"), szAppName, MB_ICONERROR) ; 
		return 0 ; 
	} 
	hwnd = CreateWindow (	szAppName, TEXT ("Multithreading Demo"), 
							WS_OVERLAPPEDWINDOW, 
							CW_USEDEFAULT, CW_USEDEFAULT, 
							CW_USEDEFAULT, CW_USEDEFAULT, 
							NULL, NULL, hInstance, NULL) ; 
	ShowWindow (hwnd, iCmdShow) ; 
	UpdateWindow (hwnd) ; 
	while (GetMessage (&msg, NULL, 0, 0)) 
	{ 
		TranslateMessage (&msg) ; 
		DispatchMessage (&msg) ; 
	} 
	return msg.wParam ; 
} 
void Thread (PVOID pvoid) 
{ 
	double		A = 1.0 ; 
	INT			i ; 
	LONG		lTime ; 
	volatile    PPARAMS pparams ;	// 使用volatile指明该变量会在正常执行之外被修改(比如通过另一个线程), 否则编译器优化可能会跳过在每个循环中检查bContinue的代码因为他在循环内没有被修改, volatile防止这种优化
	pparams	=	(PPARAMS) pvoid ; 
	lTime	=	GetCurrentTime () ;	// 以毫秒为单位获取当前时间

	for (i = 0 ; i < REP && pparams->bContinue ; i++)	// 循环100W次计算, 期间只能通过主线程的对bContinue的更改来终止计算
		A = tan (atan (exp (log (sqrt (A * A))))) + 1.0 ; 
	if (i == REP)	// 如果完成了100W次计算
	{ 
		lTime = GetCurrentTime () - lTime ;	// 再次调用GetCurrentTime()计算经过的时间 
		SendMessage (pparams->hwnd, WM_CALC_DONE, 0, lTime) ;	// 计算完成消息
	} 
	else 
		SendMessage (pparams->hwnd, WM_CALC_ABORTED, 0, 0) ;	// 计算被终止消息
	_endthread () ; 
} 
LRESULT CALLBACK WndProc (  HWND  hwnd,  UINT  message,  WPARAM  wParam,  LPARAM lParam) 
{ 
	static    INT		iStatus ; 
	static    LONG      lTime ; 
	static    PARAMS	params ; 
	static    TCHAR *	szMessage[]  =  {  TEXT  ("Ready  (left  mouse  button begins)"), TEXT ("Working (right mouse button ends)"), TEXT ("%d repetitions in %ld msec") } ; 
	HDC					hdc ; 
	PAINTSTRUCT			ps ; 
	RECT				rect ; 
	TCHAR				szBuffer[64] ; 
	switch (message) 
	{ 
	case    WM_LBUTTONDOWN: 
		if (iStatus == STATUS_WORKING) 
		{ 
			MessageBeep (0) ; 
			return 0 ; 
		} 
		iStatus				= STATUS_WORKING ; 
		params.hwnd			= hwnd ; 
		params.bContinue	= TRUE ; 
		_beginthread (Thread, 0, &params) ;	// 在用户单击客户区以后开始执行二级线程
			// 每次执行蛮力计算的时候都创建一个新的线程, 并在结束的时候终止这个线程, 显然, 我们需要一种更加有效的线程使用方式
				// 1.	一种思路是在程序的整个生命周期只创建一并保持一个计算线程, 并在需要的时候才调用这个线程, 这正是 "事件" 的用武之地;
				// 2.	一个事件对象有两种状态: 已被触发(设置)或未被触发(复位)
				// 3.	创建一个事件对象: hEvent = CreateEvent(&sa, fManula, fInitial, pszName);
					// &sa, 一个指向SECURITY_ATTRIBUTES结构的指针, pszName只在事件对象在进程间共享时才有意义, 在一个进程中, 这些参数通常被设置为NULL. fManula指示事件的触发状态
					// setEvent(hEvent) 触发一个已有事件的对象 ResetEvent(hEvent)接触一个事件对象的触发状态 WaitForSingleObject(hEvent, dwTimeout) 等待一个事件被触发, 如果事件对象已经被触发, 函数立即返回, 否则, 函数就会等待dwTimeout毫秒, dwTimeOut被设置成INFINITE, 函数就会一直到事件对象被触发才返回, 如果最开始CreateEvent函数的fManual参数被设置成false, 那么函数在WaitForSingleObject返回后, 事件对象的状态会被自动设置为未触发, 这样就不用调用ResetEvent函数去重置事件对象状态

		InvalidateRect (hwnd, NULL, TRUE) ; 
		return 0 ; 
	
	case    WM_RBUTTONDOWN: 
		params.bContinue = FALSE ; 
		return 0 ; 
	
	case    WM_CALC_DONE: 
		lTime	= lParam ; 
		iStatus = STATUS_DONE ; 
		InvalidateRect (hwnd, NULL, TRUE) ; 
		return 0 ; 
	
	case    WM_CALC_ABORTED: 
		iStatus = STATUS_READY ; 
		InvalidateRect (hwnd, NULL, TRUE) ; 
		return 0 ; 
	
	case    WM_PAINT: 
		hdc = BeginPaint (hwnd, &ps) ; 
		GetClientRect (hwnd, &rect) ; 
		wsprintf (szBuffer, szMessage[iStatus], REP, lTime) ; 
		DrawText (hdc, szBuffer, -1, &rect, 
		DT_SINGLELINE | DT_CENTER | DT_VCENTER) ; 
		EndPaint (hwnd, &ps) ; 
		return 0 ; 
	
	case    WM_DESTROY: 
		PostQuitMessage (0) ; 
		return 0 ; 
	} 
	return DefWindowProc (hwnd, message, wParam, lParam) ; 
}