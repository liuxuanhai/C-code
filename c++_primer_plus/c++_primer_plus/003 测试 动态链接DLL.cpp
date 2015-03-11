// Build: 2014-10-5 19:01:10
// 动态链接不需要.lib和.h文件
#include <iostream>
#include <windows.h>
using namespace std;

int main()
{
	HINSTANCE hInst = LoadLibrary(TEXT("C++ DLL.dll"));	// 映射指定的可执行模块到一个调用进程的地址空间
		// 此函数可以加在动态库也可以加载可执行程序
		// 返回模块的句柄HMODULE, 可以与实例句柄通用

	typedef int (*ADDPROC)(int a, int b);
	//ADDPROC Add = (ADDPROC)GetProcAddress(hInst, "add");
	ADDPROC Add = (ADDPROC)GetProcAddress(hInst, MAKEINTRESOURCEA(1)); // 使用序号实现调用 MAKEINTERSOURCE(1)将序号转换成一个字符串
		// 获取指定的导出动态库函数的地址
		// 成功: 返回动态链接库的地址    失败: null
	
	if (!Add)
		MessageBox(nullptr, TEXT("获取函数地址失败"), nullptr, MB_OK);
	else
	{
		WCHAR buf[20];
		wsprintf(buf, TEXT("5 + 3 = %d"), Add(5, 3));
		MessageBox(nullptr, buf, nullptr, MB_OK);
	}
}