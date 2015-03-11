#include <iostream>
#include <string>
using namespace std;
int main(void)
{
	string one("Lottery Winner!");  // ctor #1
	cout << one << endl;  // 重载<<
	string two(20, '$');  // ctor #2 创建一个包含20个元素的字符串, 每个字符串初始化为'$'
	cout << two << endl;
	string three(one);  // ctor #3 使用复制构造函数
	cout << three << endl;
	one += " Oops";  // 重载 +=
	cout << one << endl;
	two = "Sorry! That was ";
	three[0] = 'P';
	string four;  // actor #4  默认构造函数 创建一个长度为0的string对象
	four = two + three;
	cout << four << endl;
	char alls[] = "All's well that ends well";
	string five(alls, 20);  // ator #5 将string对象初始化为s指向的NBTS(以空字符结束的传统C字符串)的前n个字符串, 即使超过了NBTS结尾, 如果超过了会"烫烫烫烫烫"
	cout << five << "!\n";
	string six(alls+6, alls+10);  // ctor #6 从alls+6开始(包括), 到alls+10结束(不包括)
	cout << six << ", ";
	string seven(&five[6], &five[10]);  // ctor #6 again [begin, end)
				// 对象名字不会看做是对象的地址, 所以five+6是没有意义的
	cout << seven << "...\n";
	string eight(four, 7, 16);  // cotr #7  从位置7开始的n个字符或结尾(如果超过了'\0'则就是直接到结尾停止)
	cout << eight << " in motion!" << endl;

	return 0;
}