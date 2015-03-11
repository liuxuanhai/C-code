// Build: 2014-10-11 17:46:36
// system();	相当于直接在dos中写的命令
// WinExec最为简单，ShellExecute比WinExec灵活一些，CreateProcess最为复杂;

#include <iostream>
#include <windows.h>
using namespace std;

int main()
{
	system("\"010 Console 执行完输入回车.exe\"");
	cout << "执行 010 Console 执行完输入回车.exe 完毕\n";

	system("\"010 Console 执行完退出.exe\"");
	cout << "执行 010 Console 执行完退出.exe 完毕\n";

	system("大雄代码统计器.exe");
	cout << "执行 大雄代码统计器.exe 完毕\n\n";


	WinExec("\"010 Console 执行完输入回车.exe\"", SW_HIDE /*SW_SHOW*/);	 // 这个好像开辟了另外一个线程	 对于控制台 SW_HIDE SW_SHOW都一样, 都是在同一个控制台
	cout << "执行 010 Console 执行完输入回车.exe 完毕\n";

	WinExec("\"010 Console 执行完退出.exe\"", SW_SHOW);
	cout << "执行 010 Console 执行完退出.exe 完毕\n";

	WinExec("大雄代码统计器.exe", SW_SHOWMINIMIZED /*SW_HIDE*/ /*SW_SHOW*/);
}