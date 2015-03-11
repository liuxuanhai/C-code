// 程序清单 8.6
#include <iostream>
#include <string>
struct free_throws
{
	std::string name;
	int made;
	int attempts;
	float percent;
};

void display(const free_throws & ft);
void set_pc(free_throws & ft);
free_throws & accumulate(free_throws & target, const free_throws & source);

int  main()
{
	free_throws one = {"Ifelsa Branch", 13, 14}; // 这里没有初始化percent 所以其在初始化的过程中被设置为0
	free_throws two = {"Andor Knott", 10, 16};
	free_throws three = {"Minnie Max", 7, 9};
	free_throws four = {"Whily Looper", 5, 9};
	free_throws five = {"Long Long", 6, 14};
	free_throws team = {"Throwgoods", 0, 0};
	free_throws dup;

	set_pc(one);
	display(one);
	accumulate(team, one);
	display(team);
	// 使用return的引用结构变量
	display(accumulate(team, two));
	accumulate(accumulate(team, three), four);
	display(team);
	dup = accumulate(team, five); // 这里返回的是引用, 直接将temp赋值给了dup 如果返回的是结构值的话 那么accumulate()首先把返回值放在一个未命名的临时结构变量里面, 然后在把临时结构变量赋给dup效率低, 内存浪费
	std::cout << "Display team:\n";
	display(team);
	std::cout << "Display dup after assignment:\n";
	display(dup);

	set_pc(four);
	// 错误的赋值
	accumulate(dup, five) = four; // 如果这里返回的是结构变量的话赋值将会出错, 因为返回的结构变量储存在一个未命名的临时变量里面, 这里直接显示他的字面值比如5, 那么5=3是错误的---------(自己推测的不知道对不对)
	std::cout << "Display dup after ill-addvised assignment:\n";
	display(dup);

	return 0;
}

void display (const free_throws & ft)
{
	using std::cout;
	cout << "Name: " << ft.name << '\n';
	cout << "  Made: " << ft.made << '\t';
	cout << "Attempts: " << ft.attempts << '\t';
	cout << "Percent: " << ft.percent << '\t' << '\n';
}
void set_pc(free_throws & ft)
{
	if (ft.attempts != 0)
		ft.percent = 100.0f * float(ft.made) /
		float(ft.attempts);
	else
		ft.percent = 0;
}
free_throws & accumulate(free_throws & target, const free_throws & source)
{
	target.attempts += source.attempts;
	target.made += source.made;
	set_pc(target);
	return target;   // 返回引用的时候要注意的问题: 应该避免返回函数终止的时候不再存在的内存单元的引用, 如: free_throws & aaa = target; return aaa;函数执行完成后它将不再存在, 不存在的东西还怎么引用? 解决方法有两个: 1. 返回作为参数引用进来的变量, 如本例就是这样做的  2.使用new动态分配内存
}