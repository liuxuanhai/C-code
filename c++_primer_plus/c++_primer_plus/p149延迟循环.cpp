// 程序清单 5.14
#include <iostream>
#include <ctime>    // describes clock() function, clock_t type
int main()
{
	using namespace std;
	cout << "Enter the delay time in seconds: \n";
	float secs;
	cin >> secs;
	clock_t delay = secs * CLOCKS_PER_SEC; // convert(转变, 使转变) to clock ticks(记号)
		// CLOCKS_PER_SEC 每秒钟包含的系统时间单位数
		// clock_t delay 编译器会把它转换成long, unsigned int 或其他的适合系统的类型
		// secs * CLOCKS_PER_SEC 将会得到系统时间单位为单位的时间
		// clock_t clock()返回类型的别名
	cout << "starting\a\n";
	clock_t start = clock();
	while(clock() - start < delay)
		;
	cout << "done \a\n";

	return 0;
}
// ###### 改程序以系统时间单位为单位执行而不是以秒为单位执行, 这样避免了每次循环都把时间都转化成秒 #####