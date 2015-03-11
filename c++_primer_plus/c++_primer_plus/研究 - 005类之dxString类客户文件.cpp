#include <iostream>
#include "研究 - 005类之dxString类.h"
using std::cout;
using std::cin;

void callme1(dxString &);
void callme2(dxString);

int main(void)
{
	using std::endl;
{
		// 测试复制构造函数显示初始化的时候
	dxString temp("temp");
	dxString a(temp);
	dxString b = temp;				// # 1	这两个可能生成临时变量, 然后赋值初始化新对象
	dxString c = dxString(temp);	// # 2  但是本实现是直接使用复制构造转换函数, 不生成临时变量
	dxString * p = new dxString(temp);
	delete p;

	{
		cout << "在一个花括号中开始:\n";
		dxString headling1("我是headline1");
		dxString headling2("我是headline2");
		dxString sports("我是sports");
		puts("");

		cout << headling1 << endl;
		cout << headling2 << endl;
		cout << sports << endl;
		puts("");
		
		callme1(headling1);	// 引用传递, 不会导致对象被创建
		cout << headling1 << endl;
		callme2(headling2);	// 值传递, 新的对象被创建, 并且将参数对象的值 !初始化! 给新对象
								// 如果没有定义深度复制构造转换函数, 这里按默认的直接给每个数据赋值过去来进行, 这样, 临时参数失效的时候他的析构函数会把headling2指针指向的静态区字符串给释放了;
								// 返回对象同样会使用复制构造转换函数
								// 几个对象相加创建临时对象保存中间结果
								// 显示初始化的时候
		cout << headling2 << endl;
		puts("");

		cout << "将一个对象初始化给另一个:\n";
		dxString sailor = sports;	// 直接使用复制转换构造函数
		cout << sailor << endl;
		puts("");

		cout << "将一个对象赋值给另一个:\n";
		dxString knot;
		knot = headling1;	// 如果没有重载 = 的话, 这里会直接成员赋值
		cout << "knot: " << knot << endl;
		puts("");
		
		cout << "退出花括号\n";
	}

}
{
	cout << "\n\n\n\t\t测试dxString第二版\n\n";

	dxString name;
	cout << "输入你的名字: ";
	cin >> name;
	if (name == "何士雄")
		cout << "你的名字是" << name << endl;
}
	cout << "End of main()\n";

	return 0;
}

void callme1(dxString & rsb)
{
	cout << "字符串通过引用传递:\n";
	cout << "    \"" << rsb << "\"\n";
}

void callme2(dxString sb)
{
	cout << "字符串通过值传递:\n";
	cout << "    \"" << sb << "\"\n";
}