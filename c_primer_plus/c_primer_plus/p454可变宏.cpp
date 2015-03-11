// 程序清单 16.5 参数数量不定的可变宏
// 注意: 如果使用了c语言的宏执行了类似函数的功能, 那么应该考虑将他们转换为c++的内联函数, c++的内联函数都是默认内部链接的, 可以用extern声明为外部链接, 他是值传递而不是宏那样的文本传递
#include <stdio.h>
#include <math.h>
#define PR(x, ...) printf("Message" #x ": " __VA_ARGS__);
#define Min(x, y) ((x) < (y) ? (x) : (y))
//#define EVEN_GT(x, y) ((x)%2 == 0 ? ((x)>(y) ? 1 : 0) : 0)  // 在x为偶数并且大于y的时候返回0
#define EVEN_GT(x, y) ((x)>(y) && (x) % 2 == 0 ? 1 : 0)
#define PRINT2(x, y) printf(#x " is  %d and " #y " is %d\n", x, y)  // 定义一个宏函数, 用于打印两个整数表达式及其值
#define WRITE_IN(x) printf("可以用这种方法轻松定位文本, 比如这里(" #x "), 看成功了\n")
int main(void)
{
	double x = 48;
	double y;

	y = sqrt(x);
	PR(1, "x = %g\n", x);
	PR(2, "x = %.2f, y = %.2f\n", x, y);
	printf("5 和 2 中较小的是 %d\n", Min(2, 5));
	printf("..%d..\n", EVEN_GT(6, 7));
	printf("..%d..\n", EVEN_GT(6, 5));
	printf("..%d..\n", EVEN_GT(7, 6));
	PRINT2(2, 3 * 4);
	`ZWRITE_IN(heshixiong);  // 但是这里只能放置常量, 在预处理阶段打理一切


	return 0;
}