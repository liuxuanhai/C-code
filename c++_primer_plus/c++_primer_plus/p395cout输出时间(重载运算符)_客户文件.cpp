// 程序清单 11.12
#include <iostream>  // 从技术上说, 这里并不用包含头文件iostream, 因为在"p395cout输出时间(重载运算符).h"中已经包含了该文件, 然而, 作为Time类的用户, 您并不知道在类代码中包含了那些文件, 因此您应该负责的将您编写代码所需的头文件包含进来
#include "p395cout输出时间(重载运算符).h"

int main()
{
	using std::cout;
	using std::endl;
	Time aida(3, 35);
	Time tosca(2, 48);
	Time temp;

	cout << "Aida and Tosca: \n";
	cout << aida << "; " << tosca << endl;
	temp = aida + tosca;  // operator+
	cout << "Aida + Tosca: " << temp << endl;
	cout << aida << endl;
	temp = aida* 1.17;  // member operator*()
	cout << "Aida * 1.17: " << temp << endl;
	cout << "10.0 * Tosca: " << 10.0 * tosca << endl;  // 使用cout输出时间

	return 0;
}