// 创建: 2014-08-23 12:37:05
// bind2nd(fn, arg)	template模板对类型没有要求, 但是fn的表现是他应该是一个"函数", 能够接受两个参数, 并且第二个参数的类型是public的, 能够让bind2nd读取, 从而设定arg的参数为fn要求的第二个参数应有的类型, 此时, 调用bind2nd(arg_left)的时候, bind2nd()就可以调用fn(arg_left, arg)了 
// bind2nd的返回类型是fn的返回类型, 结果就是fn的结果
#include <iostream>
#include <set>
#include <deque>
#include <algorithm>
#include <functional>
#include <iterator>
#include "print.hpp"
using namespace std;
bool f(int){return true;}
int main()
{
	set<int, greater<int> > coll1;	// 这里的greater<int>之所以不是greater<int>()是因为这里greater<int>是一个结构而不是一个类弄成的仿函数
	deque<int> coll2;
	// insert elements from 1 to 9
	for (int i = 1; i <= 9; ++i)
		coll1.insert(i);
	PRINT_ELEMENTS(coll1, "initialized: ");

	// transform all elements into coll2 by multiplying 10
	transform(coll1.begin(), coll1.end(), back_inserter(coll2), bind2nd(multiplies<int>(), 10));
		// 将coll1内的所有元素乘以10以后转移(安插)到coll2中, 这里使用配接器bind2nd
		// transform()期望他自己的第四个参数是个能接纳单一参数(也就是容器实际元素)的表达式, 然而我们却需要先把该元素乘以10
		// bind2nd(multiplies<int>(), 10) 使得进行multipies<int>运算时, 以群集的元素作为第一个参数, 10作为第二个参数
		// 具体过程: transform()将调用bind2nd(*pos), bind2nd()调用multiplies(*pos, 10)...

	PRINT_ELEMENTS(coll2, "transformed: ");

	// replace value equal to 70 with 42
	replace_if(coll2.begin(), coll2.end(), bind2nd(equal_to<int>(), 70), 42); 
	PRINT_ELEMENTS(coll2, "replaced: ");

	// remove all elements with value less than 50
	coll2.erase(remove_if(coll2.begin(), coll2.end(), bind2nd(less<int>(), 50)), coll2.end());
	PRINT_ELEMENTS(coll2, "removed: ");
}