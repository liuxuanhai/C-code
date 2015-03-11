// 程序清单 11.21 客户文件
#include <iostream>
#include "p411类型转换.h"

int main()
{
	using std::cout;
	Stonewt poppins(9, 2.8);  // 9 stone, 2.8 pounds
	double p_wt = poppins;  // implicit(隐式的) conversion
		// 隐式的使用转换函数
	cout << "Convert to double => ";
	cout << "Poppins: " << p_wt << " pounds.\n";
	cout << "Convert to int => ";
	cout << "Poppins: " << int (poppins) << " pounds.\n";
						// 显式的使用转换函数
	return 0;
}