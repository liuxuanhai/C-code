// 程序清单 4.24  关于vector模板类, array模板类和数组
// 比较数组, vector对象和array对象
#include <iostream>
#include <vector>
#include <array>         // c++11
int main()
{
	// ######### 声明, 赋值, 访问 ############

	using namespace std;
	double a1[4] = {1.2, 2.4, 3.6, 4.8};
	vector<double> a2(4);// creat a vector with 4 elements
	a2[0] = 1.0 / 3.0;
	a2[1] = 1.0 / 5.0;
	a2[2] = 1.0 / 7.0;
	a2[3] = 1.0 / 9.0;
	array<double, 4> a3 = {3.14, 2.72, 1.62, 1.41};
				         // array比数组更加安全方便
	array<double, 4> a4;
	a4 = a3;             // 数组之间是不能直接赋值的
	cout << "a1[2]: " << a1[2] << " at " << &a1[2] << "栈" << endl;
	cout << "a2[2]: " << a2[2] << " at " << &a2[2] << "堆" << endl;
	cout << "a3[2]: " << a3[2] << " at " << &a3[2] << "栈" << endl;
	cout << "a4[2]: " << a4[2] << " at " << &a4[2] << "栈" << endl;

	//############ 关于越界访问 #############
	
	// 数组
	a1[-2] = 20.2;       // 数组可以任意越界赋值, 安全性很低
	cout << "a1[-2]: " << a1[-2] << " at " << &a1[-2] << endl;
	cout << "a1[-1]: " << a1[-1] << " at " << &a1[-1] << endl; // 未初始化的任意值

	// vector对象
	//a2[-2] = 11.1;     // 这种会出现异常终止, 因为vector安全性比数组高
	//a2.at(-2) = 22.2;  // abort()类型的终止
	//cout << a2[-2];    // 异常终止
	//cout << a2.at(-2); // abort()类型的终止

	// array对象
	//a3[-2] = 11.1;     // 这种会出现异常终止, 因为array安全性比数组高
	//a3.at(-2) = 22.2;  // abort()类型的终止
	//cout << a3[-2];    // 异常终止
	//cout << a3.at(-2); // abort()类型的终止

	// ######### vector对象可以任意(尾部添加, 中间插入)增长 #####
	vector<int> vi;      // 声明了一个0长度的vector
		// 由于vector可以在插入和添加值的时候自动调整长度, 所以这里可以先设置一个零长度的vector对象
		// 调整vector对象的长度需要使用vector包中的各种方法, 这里先不介绍

	return 0;
}