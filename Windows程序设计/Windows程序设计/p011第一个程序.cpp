#include <windows.h>
int WINAPI WinMain (  // WINAPI是一种函数调用约定, 表名如何!生成!在堆栈中放置函数调用参数的机器代码, 绝大多数windows函数调用被定义成WINAPI;
	HINSTANCE hInstance, // HINSTANCE(Instance Handle)  实例句柄: 程序里用它来标识某些东西, 这个例子这个句柄唯一标识了我们的这个程序
	HINSTANCE hPrevInstance,  // 前一个实例 可以通过查看这个参数知道是否还有其他实例正在运行 如果有 可以直接和那个共享代码和只读数据 但是这个在32位windows中已不再适用, 因此WinMain的参数通常是NULL
	PSTR szCmdLine,  // 用来运行程序的命令行, 有些程序在运行的时候用它来把文件装入内存;
					// 这里将LPSTR(Long Pointer String)改成了PSTR, 因为LP是16位windows的产物
	int iCmdShow)  // 这个参数用来指明最初程序如何显示(正常显示还是最大化等等) sz: 以零结束的字串 i: int
{
	// 显示短信息的对话框
	MessageBox (
		NULL,  // 窗口句柄 第三章介绍 
		TEXT ("Hello, MFC!"),  // 信息框中出现的文本字符串 这些字符串被打包在TEXT宏代码里面, 这样做把程序转换成Unicode时会方便很多
		TEXT ("First Program"),  // 标题栏上显示的文本
		0 | MB_ICONHAND);
	return 0;
}