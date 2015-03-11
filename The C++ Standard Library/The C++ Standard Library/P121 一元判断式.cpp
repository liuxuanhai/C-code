// 创建: 2014-8-22 09:33:44
// 判断式, predicate: 返回布尔值的函数, 通常被用来指定排序准则和搜寻准则, 可能有一个或两个操作数
// 一元判断式: unary predicate	二元判断式: binary predicate
// 一元判断式, 在区间中调用一个elem进行比较 find_if()	2.	二元判断式, 在区间中调用两个elem进行比较 sort()
// STL要求, 面对相同的值, predicate必须得出相同的值, 这将把"被调用时, 会改变自己内部状态"的函数清除;
// 程序: 寻找给出区间内的第一个质数
#include <iostream>
#include <list>
#include <algorithm>
#include <cstdlib>	// for abs()
using namespace std;

// predicate, which returns whether an integer is a prime number (质数)
bool isPrime(int number)
{
	// ignore negative sign
	number = abs(number);
	// 0 and 1 are prime numbers
	if (number == 0 || number == 1)
		return true;
	// find divisor(除数) that divides without a remainder(余数)
	int divisor;
	for (divisor = number / 2; number % divisor != 0; --divisor);
	// if no divisor greater than 1 is found, it is a prime number
	return divisor == 1;
}

int main()
{
	list<int> coll;
	// insert elements from 24 to 30
	for (int i = 24; i<= 30; ++i)
		coll.push_back(i);

	// search for prime number
	list<int>::iterator pos;
	pos = find_if(coll.begin(), coll.end(), isPrime);	// 在给定区间内寻找使"被传入一元判断式"运算结果为true的第一个元素, 如果没有找到, 返回第二个参数end
	if (pos != coll.end())
		cout << *pos << " is first prime number found \n";
	else
		cout << "no prime number found\n";
}