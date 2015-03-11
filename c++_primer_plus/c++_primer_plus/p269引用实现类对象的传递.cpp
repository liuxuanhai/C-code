// 程序清单 8.7
#include <iostream>
#include <string>
using namespace std;
string version1(const string & s1, const string & s2);
const string & version2(string & s1, const string & s2);
const string & version3(string & s1, const string & s2);

int main()
{
	string input;
	string copy;
	string result;

	cout << "Enter a string: ";
	getline(cin, input);
	copy = input;
	cout << "Your string as entered: " << input << endl;
	result = version1(input, "★★★"); // 这里定义的是使用const string &参数但是实际传过来的是c风格的字符串, 原因: 1. string类定义了一种从char * 到string类的转换功能. 2. const引用形参有一个属性: 假设实参的类型与引用参数类型不匹配, 但是可以被转换成引用类型, 程序将会创建一个正确类型的临时变量, 使用转换后的实参值来初始化它, 然后 传递(??是不是说明变量是在传递前创建的所以不是专属被调函数的局部自动变量???) 一个指向该临时变量的引用.
	cout << "Your string enhanced: " << result << endl;
	cout << "Your original string: " << input << endl;

	result = version2(input, "###");   // 返回的是对s1的引用, 然后result不是引用类型, 这样就相当于直接将result = input了
									  // 另一方面, 由于这是返回的input的引用, 所以在对result进行赋值的时候input也会跟着变, 这有可能不会我们想要的
	cout << "Your string enhanced: " << result << endl;
	cout << "Your orginal string: "  << input << endl;

	cout << "Resultting orginal string:\n";
	input = copy;
	result = version3(input, "@@@");  // 返回的是对局部自动变量temp的引用, 然而temp在执行完version3后将会被销毁, 所以将会导致abort()类错误, 正确方式可以选择动态分配内存方式
	// 这里如果没有"result ="就不会报错了!!!   就是这句让程序发现他在引用已经释放的内存
	cout << "Your string enhanced: " << result << endl;
	cout << "Your original string: " << input << endl;

	return 0;
}

string version1(const string & s1, const string & s2) // “version1”: 不能将参数 2 从“const char [7]”转换为“std::string &” 这里如果不是const的话不会进行类型转换的
 {                                                   // “return”: 无法从“const std::string(这里不说成是const string &是不是因为这里说的不是不能把s2赋给他而是说的不能把"★★★"赋给它???)”转换为“std::string &” 在返回 值类型的设计上不能是string & 类型, 但是const string &是可以的
	string temp;

	temp = s2 + s1 + s2;
	return s2;
}

const string & version2(string & s1, const string & s2)
{
	s1 = s2 + s1 + s2;
	return s1;
}

const string & version3(string & s1, const string & s2)
{
	string temp;
	temp = s2 + s1 + s2;
	return temp;  // warning C4172: 返回局部变量或临时变量的地址
	/*string * temp = new string;
	*temp = s2 + s1 + s2;
	return *temp;*/
}