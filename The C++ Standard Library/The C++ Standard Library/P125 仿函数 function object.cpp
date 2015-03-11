// 创建: 2014-08-23 07:42:21
// 给算法的函数参数不一定是函数, 也可以是行为类似函数("使用小括号传递参数, 藉以调用每个东西")的对象, 任何东西, 只要行为像个函数, 他就是个函数;
// 仿函数的优点:	1. 有自己的成员函数和变量, 这意味着仿函数拥有状态(state);
//					2. 一般函数, 唯有他们的特征标不同时, 才算性别不同, 仿函数有自己的型别, 可以将函数行为当作template参数来运用;	   
//					3. 仿函数通常速度比一般函数快, template的细节在编译初期已经确定, 通常可能进行更好的优化;
// for_each() 是一个模板函数, 对他的参数没有要求, 根据参数生成相应的版本定义, 第三个参数应该传入一个只有一个参数的"函数"是因为for_each()中有f(elem) 这样的使用, 这里是使用方法限定了参数的类型大致符合什么样的表现行为

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// simple function boject that prits the passed argument
class PrintInt
{
public:
	void operator() (int elem) const { cout << elem << ' '; }
};

int main()
{
	vector<int> coll;
	// insert elements from 1 to 9
	for (int i = 1; i < 10; i++)
		coll.push_back(i);

	// print all elements
	for_each(coll.begin(), coll.end(), 
		PrintInt());	// PrintInt()产生此类别的一个临时对象,当作for_each()算法的一个参数
						// template<class Iterator, class Operation> Operator for_each(Iterator act, Iterator end, Operation op) {while(act != end) {op(*act); ++act;} return op;}

	cout << endl;
}