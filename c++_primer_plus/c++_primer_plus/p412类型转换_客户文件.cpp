// 程序清单 11.18 客户文件
#include <iostream>
using std::cout;
#include "p411类型转换.h"
void display(const Stonewt & st, int n);
int main()
{
	Stonewt incognito = 275;  // uses constructor to initialize
	Stonewt wolfe(285.7);  // same as Stonewt wolfe = 285.7
		// 只有接受一个参数的构造函数才能作为转换函数, 下面的构造函数
	Stonewt taft(21, 8);

	cout << "The celebrity weighted ";
	incognito.show_stn();
	cout << "The detective weighed ";
	wolfe.show_stn();
	cout << "The President weighed ";
	taft.show_lbs();
	incognito = 276.8;  // uses constructor for conversion
	taft = 325;  // same as taft = Stonewt(325); use Stonewt(325) to convert(转换, 使转换) 325 to Stonewt
		// 程序将使用构造函数Stonewt(double)来创建一个临时的Stonewt对象, 并将19.6作为初始化值, 随后 采用逐成员赋值方式将该临时对象内容复制到taft中, 这一过程称为隐式转换, 因为他是自动进行的, 不需要显示强制类型转换
	cout << "After dinner, the celebrity weighed ";
	incognito.show_stn();
	cout << "After dinner, the President weighed ";
	taft.show_lbs();
	display(taft, 2);
	cout << "The wrestler weighed even more.\n";
	display(422, 2);
	cout << "No stone left unearned\n";

	return 0;
}

void display(const Stonewt & st, int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << "Wow! ";
		st.show_stn();
	}
}