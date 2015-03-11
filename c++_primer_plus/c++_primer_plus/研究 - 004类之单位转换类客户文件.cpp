#include <iostream>
#include "研究 - 004类之单位转换类.h"
using std::cout;

int main(void)
{
/******************** 测试构造转换函数 **********************/

	{
	Stonewt myWeight = 25;	// 初始化的时候使用转换函数, 不会生成临时变量
	Stonewt sheWeight(285.7);	// 这个即使转换函数是explicit也能实现
	Stonewt itWeight(21, 15);

	cout << "我的重量: ";
	myWeight.show_stn();
	cout << "她的重量: ";
	sheWeight.show_stn();
	cout << "它的重量: ";
	itWeight.show_lbs();
	cout << "   ";
	itWeight.show_stn();

	myWeight	= 26;	// 因为转换函数是构造函数, 构造函数只有在生成对象的时候被调用, 所以这里肯定生成了一个对象, 那么就是先把26转换创建成一个Stonewt的临时变量, 然后把变量的值复制给等号左边;
	itWeight	= Stonewt(0, 1.1);	// 这样和上边的抓换函数本质是一样的, 只是这里得显式调用生成;
	sheWeight	= 325;
	cout << "吃完饭, 我的重量: ";
	myWeight.show_stn();
	cout << "吃完饭, 她的重量: ";
	sheWeight.show_stn();
	}

/********************** 测试类方法转换函数 *********************/
	Stonewt w = 52.6;
	cout << "\nStonewt => int: " << (int)w << std::endl;
	cout << "Stonewt => double: " << (double)w << std::endl;

	return 0;
}