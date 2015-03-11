// 创建: 2014-08-23 08:20:51
// 本程序列出来了仿函数的第一个优势, 状态优势
// for_each() 是一个模板函数, 对他的参数没有要求, 根据参数生成相应的版本定义, 第三个参数应该传入一个只有一个参数的"函数"是因为for_each()中有f(elem) 这样的使用, 这里是使用方法限定了参数的类型大致符合什么样的表现行为
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include "print.hpp"
using namespace std;
#define Version 1

#if Version == 1

// 对群集中的每个元素加上一个固定的值, 编译期就知道这个固定数
void add10(int & elem)
{
	elem += 10;
}
// 对群集的每个元素加上不同的固定值, 编译期就知道
template<int theValue>
void add(int & elem, int e)
{
	elem += theValue;
}

int main()
{
	vector<int> coll;
	for (int i = 0; i <= 9; ++i)
		coll.push_back(i);
	PRINT_ELEMENTS(coll, "init: ");
	for_each(coll.begin(), coll.end(), add10);
	PRINT_ELEMENTS(coll, "add10: ");

	for_each(coll.begin(), coll.end(), add<1>);
	PRINT_ELEMENTS(coll, "add<1>: ");
}

#elif 
// function object that adds the value with which it is initialized
class AddValue
{
private:
	int theValue;	// the value to add
public:
	// constructor initializes the value to add
	AddValue(int v) : theValue(v) {}
	// the "function call" for the element adds the value
	void operator()(int & elem) const { elem += theValue; }
};
int main()
{
	list<int> coll;
	// insert elements from 1 to 9
	for (int i = 0; i <= 9; ++i)
		coll.push_back(i);

	PRINT_ELEMENTS(coll, "initialized: ");

	// add value 10 to each element
	for_each(coll.begin(), coll.end(), 
		AddValue(10));	// 这里让他加的10, 这对于非仿函数来说简直是不可能的, 因为根据特征标他只能传入一个值, 而这个值是for_each添加的...
	PRINT_ELEMENTS(coll, "after adding 10: ");
	// add value of first element to each element
	for_each(coll.begin(), coll.end(), AddValue(*coll.begin()));
	PRINT_ELEMENTS(coll, "after adding first element: ");
}
#endif