//		QQ		:	394899990
//		百度ID	:	男儿志凌云
#include <windows.h>
#include <fstream>

struct DataTag
	{
		TCHAR	szLastFileName[100];	// 最后一个读取的文件的名字
		int     iFileNum;	// 包含的文件个数
		int		iCntChar;	// 字符数(不显示的回车除外, 注释除外, 空白符(空格, tap)除外)
		int		iCntLetter;	// 字母数((不显示的回车除外, 注释除外))
		int     iCntFuHao;	// 符号数(, ; / * () {} & ...)
		int		iCntRow;	// 行数
		int		iDigit;		// 阿拉伯数字个数
		int		iCnHalf;	// 非注释中文个数(字符串, 或者手贱定义的宏(#define 测试), 或者...)
		int		iCnHalfAnt;	// 注释中文个数
		int		iCntCharAnt;// 注释字符个数(回车符除外, 包含空白符(空格, tap算一个字符)
	} Data = {0};
DataTag temp = {0};
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, 
				    HINSTANCE hPrevInstance, 
				    PSTR szCmdLine, int iCmdShow)
{
	TCHAR		szAppName[] = TEXT("大雄代码统计器");
	WNDCLASS	wndclass;
	HWND		hwnd;
	MSG			message;

	wndclass.cbClsExtra			= 0;
	wndclass.cbWndExtra			= 0;
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

	while (GetMessage(&message, NULL, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	return message.wParam;
}
void ScanFile(TCHAR * FILENAME, DataTag & Data);
void ShowData(HWND hwnd, DataTag & Data, int x = 0, int y = 0);

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT		ps;
	HDC				hdc;
	static HWND		hwndList;
	static int		cxClient, cyClient;
	TCHAR			szBuffer[MAX_PATH + 1];  // 用于保存当前目录或文件名或目录加文件名等等

	switch (message)
	{
	case WM_CREATE:

			// 创建列表框

		hwndList = CreateWindow(TEXT("listbox"), NULL, WS_CHILDWINDOW | WS_VISIBLE | LBS_STANDARD/*显示的文件的属性*/,
			0, 0, 0, 0,
			hwnd, (HMENU)'L', (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
		
			// 将文件目录列表(子目录和磁盘驱动器)写入列表框

		SendMessage(hwndList, LB_DIR, DDL_READWRITE/*文件属性*/, (LPARAM)TEXT("*.h"));  // lParam参数是指向文件限定字符串例如("*.*")的指针, 该文件限定不影响列表框中包含的子目录;
		SendMessage(hwndList, LB_DIR, DDL_READWRITE/*文件属性*/, (LPARAM)TEXT("*.c"));  // lParam参数是指向文件限定字符串例如("*.*")的指针, 该文件限定不影响列表框中包含的子目录;
		SendMessage(hwndList, LB_DIR, DDL_READWRITE/*文件属性*/, (LPARAM)TEXT("*.cpp"));  // lParam参数是指向文件限定字符串例如("*.*")的指针, 该文件限定不影响列表框中包含的子目录;

			// 开始统计
		for (int i = 0; ; i++)
		{
			if (LB_ERR == SendMessage(hwndList, LB_GETTEXT, i, (LPARAM)szBuffer))
				break;
			ScanFile(szBuffer, Data);
		}
		return 0;
	
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);

		MoveWindow(hwndList, 0, 0, cxClient / 4, cyClient, TRUE);

		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		ShowData(hwnd, Data);	// 显示文件夹下的所有文件数据总和
		if (temp.iFileNum == 1)
		{
			TextOut(hdc, cxClient / 4 + 30, 245, temp.szLastFileName, lstrlen(temp.szLastFileName));
			ShowData(hwnd, temp, 0, 250);	// 显示选中文件的数据
		}
		GetCurrentDirectory(MAX_PATH + 1, szBuffer);
		lstrcat(szBuffer, TEXT("  统计结束..."));
		TextOut(hdc, cxClient / 4 + 30, 0, szBuffer, lstrlen(szBuffer));
		EndPaint(hwnd, &ps);
		return 0;

	case WM_COMMAND:
		int		iSelect;
		if (LOWORD(wParam) == 'L' && HIWORD(wParam) == LBN_DBLCLK)
		{
				// 获取当前选中项的索引值 如果没有选中项, 函数返回LB_ERR(-1)

			if (LB_ERR == (iSelect = SendMessage(hwndList, LB_GETCURSEL, 0, 0)))
				break;

				// 将当前选中项的变量名保存进szBuffer  (比如点的是p328.txt, 那么szBuffer中保存的是"p328.txt", 并不包含目录)

			SendMessage(hwndList, LB_GETTEXT, iSelect, (LPARAM)szBuffer);

			std::ifstream fin;
			fin.open(szBuffer);
			if (!fin.is_open())
			{
				MessageBox(hwnd, TEXT("无法打开文件!"), szBuffer, MB_ICONERROR | MB_OK);
				return 0;
			}
			DataTag t = {0};
			temp = t;
			ScanFile(szBuffer, temp);
			InvalidateRect(hwnd, NULL, TRUE);
			UpdateWindow(hwnd);
		}
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

void ScanFile(TCHAR * FILENAME, DataTag & Data)
{
	char	ch;				// 临时保存每个读取的字符
	enum annotation{ifAnt, isAnt, notAnt, isAnt2};
	annotation	Ant = notAnt;	// 注释判断
		
	
		// 打开文件, 错误检查

	std::ifstream fin;	// 文件输入对象
	fin.open(FILENAME);
	if (!fin.is_open())
	{
		MessageBox(NULL, TEXT("出现文件打开错误, 程序异常退出!"), TEXT("Error"), MB_ICONERROR | MB_OK);
		exit(EXIT_FAILURE);
	}

		// 开始统计

	lstrcpy(Data.szLastFileName, FILENAME);
	Data.szLastFileName;
	Data.iFileNum++;
	ch = fin.get();	
	int chNum = 0;
	while (fin.good())
	{
			// 处理死循环

		if (chNum++ >= 100000)
		{
			MessageBox(NULL, TEXT("文件统计出错, 请确认文件是标准的c/c++/h文件!"), FILENAME, MB_ICONERROR | MB_OK);
			exit(EXIT_FAILURE);
		}
			// 中文处理

		if ((ch > 255 || ch < 0) 
			&& isAnt != Ant && isAnt2 != Ant)	// 排除中文注释
		{
			ch = fin.get();
			Data.iCnHalf++;
			continue;
		}

			// 统计行数
		if (ch == '\n')
			Data.iCntRow++;

			// 处理注释 "//"
		if ('/' == ch && notAnt == Ant)	// "//" ? "/" ? "/*" ? "*/"
			Ant = ifAnt;
		else if ('/' == ch && ifAnt == Ant)
			Ant = isAnt;
		else if (isAnt == Ant)
		{
			int flag = 0;
			do{	// 使用do-while使得 "//"后边的第一个字符也能接受判断
				if (ch == EOF)
				{
					flag = 1;
					break;
				}
				if (ch < 0 || ch > 255)
					Data.iCnHalfAnt++;
				else
					Data.iCntCharAnt++;
			}while('\n' != (ch = fin.get()));	// 吃掉注释
			Data.iCntCharAnt += 2;	// "//"符号也算两个注释字符
			if (flag)
				break;
			Data.iCntRow++;	// 吃了这行的注释, 但是行数还是得加上
			Ant = notAnt;
		}

			// 处理注释 "/* */"
		else if ('*' == ch && ifAnt == Ant)
			Ant = isAnt2;
		else if (isAnt2 == Ant)
		{
			Ant = notAnt;
			int flag = 0;	// 寻找 "*/" 的标记
				
				// 一直删除注释, 直到注释结束
			
			do{	// 防止/*后边的第一个字符被忽视, 而且不用do-while的话, /**/会出错
				if (ch < 0 || ch > 255)
					Data.iCnHalfAnt++;
				else if ('*' == ch)
				{
					flag = 1;
					Data.iCntCharAnt++;
				}
				else if (flag && '/' == ch)
					break;
				else
				{
					if ('\n' == ch)	// 注释的行数也算行数, 但是不算注释字符
						Data.iCntRow++;
					else
						Data.iCntCharAnt++;
					flag = 0;
				}
			} while (ch = fin.get());
			Data.iCntCharAnt += 3;	// "/*", '/'
		}

			// 统计字符, 字母个数
		else if (isgraph(ch))	// 字符
		{
			Ant = notAnt;
			Data.iCntChar++;
			if (isalpha(ch))	// 字母个数
				Data.iCntLetter++;
			else if (ispunct(ch))	// 符号数量
				Data.iCntFuHao++;
			else if (isdigit(ch))	// 数字个数
				Data.iDigit++;	
		}
		ch = fin.get();
	}
	Data.iCntRow++;
}

#define TEXTOUT TextOut(hdc, (rcClient.right - rcClient.left) / 4 + 30 + x, i++ * 20 + y, szBuffer, lstrlen(szBuffer))

void ShowData(HWND hwnd, DataTag & Data, int x, int y)
{
		// 进行输出显示
	static HDC	hdc = GetDC(hwnd);	// 这里的GetDC产生的hdc就不用releaseDC释放了, 程序执行完在自己释放吧, 就一个, 也不占多少内存
	SelectObject(hdc, GetStockObject(SYSTEM_FIXED_FONT));

	int i = 1;
	TCHAR		szBuffer[512];
	RECT		rcClient;
	GetClientRect(hwnd, &rcClient);
	wsprintf(szBuffer, TEXT("统计 %d 个文件完毕..."), Data.iFileNum);
	TEXTOUT;
	wsprintf(szBuffer, TEXT(" 行数 : %d"), Data.iCntRow);
	TEXTOUT;
	wsprintf(szBuffer, TEXT("总字符: %d"), Data.iCntChar + Data.iCnHalf / 2 + Data.iCntCharAnt + Data.iCnHalfAnt / 2);
	TEXTOUT;
	wsprintf(szBuffer, TEXT("    非注释字符数: %d"),Data.iCntChar + Data.iCnHalf / 2);
	TEXTOUT;
	wsprintf(szBuffer, TEXT("        字母数: %d"), Data.iCntLetter);
	TEXTOUT;
	wsprintf(szBuffer, TEXT("        符号数: %d"), Data.iCntFuHao);
	TEXTOUT;
	wsprintf(szBuffer, TEXT("        数字数: %d"), Data.iDigit);
	TEXTOUT;
	wsprintf(szBuffer, TEXT("        中文数: %d"), Data.iCnHalf / 2);
	TEXTOUT;
	wsprintf(szBuffer, TEXT("    注释字符数: %d"), Data.iCntCharAnt + Data.iCnHalfAnt / 2);
	TEXTOUT;
	wsprintf(szBuffer, TEXT("        中文数: %d"), Data.iCnHalfAnt / 2);
	TEXTOUT;
	wsprintf(szBuffer, TEXT("        字符数: %d"), Data.iCntCharAnt);
	TEXTOUT;
	
	/*cout << "\n统计文件 "		<< FILENAME						<< " 完毕...\n";
	cout << " 行数 : "			<< ++Data.iCntRow					<< endl;
	cout << "总字符: "			<< Data.iCntChar + Data.iCnHalf / 2 + Data.iCntCharAnt + Data.iCnHalfAnt / 2 << endl;
	cout << "\t非注释字符数: "	<< Data.iCntChar + Data.iCnHalf / 2		<< endl;
	cout << "\t\t字母数: "		<< Data.iCntLetter					<< endl;
	cout << "\t\t符号数: "		<< Data.iCntFuHao					<< endl;
	cout << "\t\t数字数: "		<< Data.iDigit						<< endl;
	cout << "\t\t中文数: "		<< Data.iCnHalf / 2					<< endl;
	cout << "\t注释字符数: "	<< Data.iCntCharAnt + Data.iCnHalfAnt / 2	<< endl;
	cout << "\t\t中文数: "		<< Data.iCnHalfAnt / 2				<< endl;
	cout << "\t\t字符数: "		<< Data.iCntCharAnt					<< endl;*/
}