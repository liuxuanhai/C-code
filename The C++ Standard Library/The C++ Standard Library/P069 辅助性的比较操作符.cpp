// 创建: 2014-08-20 09:39:44
// 四个template functions, 分别定义了 != > <= >= 四个比较操作符, 他们都是利用 == 和 < 完成的
// 四个函数是在std::rel_ops::名称空间中定义的template, 只需定义<和== 操作符就可以使用她们了, 加上using namespace std::rel_ops, 上述四个比较操作符就自动获得了定义
#include <utility>	// for inline bool std::rel_ops::operator!= (const T & x, const T & y);
#include <iostream>
class A
{
private:
	int n;
public: 
	A(int nn) { n = nn; }
	bool operator== (const A & a) const { return n == a.n; }
	bool operator< (const A & a) const { return n < a.n; }
};

int main()
{
	A a(1);
	A b(2);

	std::cout << "a > b ? : " << std::rel_ops::operator>(a, b) << std::endl;
	using namespace std::rel_ops;
	std::cout << "a != c ? : " << (a != b) << std::endl;
}