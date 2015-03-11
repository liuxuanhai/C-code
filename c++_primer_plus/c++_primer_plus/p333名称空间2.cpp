// 程序清单 9.13 文件3
#include <iostream>
#include "p331名称空间示例.h"
void other(void);
void another(void);
int main(void)
{
	using debts::Debt;
	using debts::showDebt;  // 只给出了函数的名称, 因此, 如果函数被重载, 则一个using声明将导入所有的版本
		// 虽然Debt和showDebt都使用了Person类型, 但是不必导入任何Person名称, 因为debt名称空间有一条包含pers名称空间的using编译指令

	Debt golf = {{"Benny", "Goatsniff"}, 120.0};
	showDebt(golf);
	other();
	another();

	return 0;
}
void other(void)
{
	using std::cout;
	using std::endl;
	using namespace debts;  // 这是一种不太好的方法, 他用一条编译指令导入整个名称空间 
		// 由于debts中的using编译指令导入了pers名称空间, 因此other()函数可以使用Person类型和showPerson()函数
	Person dg = {"Doodles", "Glister"};  // debts空间中包含了pers, pers中声明了Person
	showPerson(dg);
	cout << endl;
	Debt zippy[3];
	int i;
	for (i = 0; i < 3; i++)
		getDebt(zippy[i]);

	for (i = 0; i < 3; i++)
		showDebt(zippy[i]);
	cout << "Total debt: $" << sumDebts(zippy, 3) << endl;
	return;
}
void another(void)
{
	using pers::Person;
	Person collector = {"Milo", "Rightshift"};
	pers::showPerson(collector);
	std::cout << std::endl;
}