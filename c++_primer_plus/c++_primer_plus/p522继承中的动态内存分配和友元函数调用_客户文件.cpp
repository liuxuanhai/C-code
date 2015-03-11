#include "p519继承中的动态内存分配和友元函数调用_头文件.h"
#include <iostream>
int main(void)
{
	using std::cout; 
	using std::endl;
	 
	hasDMA has;
	cout << has;

	//baseDMA shirt("Portabelly", 8);
	//lacksDMA balloon("red", "Blimpo", 4);
	//hasDMA map("Mercator", "Buffalo Keys", 5);
	//
	//cout << "BaseDMA: " << shirt << endl;
	//cout << "LacksDMA: " << balloon << endl;
	//cout << "HasDMA" << map << endl;

	//lacksDMA balloon2(balloon);  // 复制构造函数
	//cout << "LackDMA copy: " << balloon2 << endl;
	//
	//hasDMA map2;
	//map2 = map;  // 赋值函数
	//cout << "assignment hasDMA: \n" << map2 << endl;

	//cout << "Done!\n";
	return 0;
}
