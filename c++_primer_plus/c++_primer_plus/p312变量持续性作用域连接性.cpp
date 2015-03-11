// 程序清单 9.5 (关联程序清单9.6)
#include <iostream>
static int i; // 由于9.6中已经声明了具有外部连接的int i所以这里直接声明int i将会被认为是二次定义, 但是声明为具有内部链接的全局变量是可以的, 并且会隐藏具有外部链接的同名变量
using namespace std;
// extern variable
double warming = 0.3;
// function prototypes
void update(double);
void local();

int main()
{
	cout << "Global warming is " << warming << " degrees.\n";
	update(0.1);
	cout << "Global warming is " << warming << " degrees.\n";
	local();
	cout << "Global warming is " << warming << " degrees.\n";

	return 0;
}
