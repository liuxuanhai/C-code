// 复习: 2014 08 15
// 复习: 2014 08 18 # 1 运行的时候莫名其妙的不刷新时间了

// 自写软件
#include <iostream>
#include <ctime>
#include <windows.h>
#include <process.h>
#pragma comment(lib, "winmm.lib")	// 保证PlaySound()的执行
bool isStop = false;
void playsound(void *)
{
	if (!isStop)
		PlaySound(L"C:\\Users\\daxiong\\desktop\\VS2012\\Code\\Windows程序发布\\Windows程序发布\\大雄2048游戏1.0背景音乐.wav", NULL, SND_FILENAME | SND_ASYNC);
	else
		PlaySound(nullptr, nullptr, SND_FILENAME | SND_ASYNC);
	_endthread();	// # 1
}
int main()
{
	using namespace std;
	cout << "请输入要延迟的时间(秒):\n";
	float input;
	while (cin >> input)
	{
		isStop = true;
		_beginthread(playsound, 0, nullptr);
		clock_t delay = static_cast<clock_t>(input * CLOCKS_PER_SEC);
		clock_t start;
		start = clock();
		int i = 1;
		//int c;
		clock_t temp;
		while((temp = clock() - start) < delay)
		{
			if ((clock() - start) / CLOCKS_PER_SEC > i )	// 这样可以防止极少发生的在整个1s中都没有执行这个语句一条引起的i永远无法跟新跟上 clock() - start # 1    -- 这个是导致不更新的原因吗? 
			//if (clock() - start == i * CLOCKS_PER_SEC)// ???????????为什么不可以???	// 因为相等的这个情况可能在执行别的语句的时候错过了 # 1
			{
				system("cls");
				cout << --input << "\n";
				i++;
			}
		}
		cout << "时间到了!\a\a\a\a\a\n";
		isStop = false;
		_beginthread(playsound, 0, nullptr);
		cout << "请输入要延迟的时间(秒):\n";
	}

	return 0;
}