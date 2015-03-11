// 程序清单 3.6
// cout.put();和cout对字符的识别输出
#include <iostream>
int main()
{
	using namespace std;
	char ch = 'M';
	int i = ch;
	cout << ch << "的ascll编码为: " << i << endl;
	cout << "加上一以后:" << endl;
	ch = ch + 1;
	i = ch;
	cout << ch << "的ascll编码为: " << i << endl;

	cout << "使用cout.put()函数输出字符:" << endl;
	cout.put(ch); // 句点被称为成员运算符
	cout.put('|');
	cout << endl << "---------" << 'm' << "-------------" << endl;
	// 此时输出的是'm'而不是m的asill码的值, 但是早期的c把'm'常量储存在
	// int中, 对于cout来说, 他只认识8位的char而不认识32位的int, 所以他把他当做int输出而不是当早
	// 字符输出, 所有就诞生了cout.put(), 但是后来的c都实现了把字符常量m储存在char当中, 所以即使
	// 不用cout.put()也能输出了
	cout << sizeof('m') << endl;

	cout << endl << "Done!" << endl;
	// cout << "Let them eat g\u00E2teau." << endl;
	// 查看是否支持拓展字符集     不支持

	return 0;
}