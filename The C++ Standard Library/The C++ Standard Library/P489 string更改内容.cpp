// Modifiers --- 赋值
#include <iostream>
#include <string>
using namespace std;

int main(void)
{
	char * cstring = "othello";	// C语言把字面字符串表示为char *, C++表示为const char *, 但是为了支持向下类型转换, C++支持const char *到char *的隐式转换(备受争议)
	const string aString(cstring);	// aString[aString.length()] 可以 const string支持访问最后一个字符后边的第一个位置, 不属于aString的'\0'
	string s;	// s[s.length()] ERROR string不支持访问最后一个字符后边的第一个位置

	s = aString;		// assign "othello"
	cout << s << endl;
	s = "two\nlines";	// assign a C-string
	cout << s << endl;
	s = '.';			// assign a single character
	cout << s << endl;

	s.assign(aString);	// assign "othello"(equivalent to operator=)
	cout << s << endl;
	s.assign(aString, 1, 3);	// assign "the"
	cout << s << endl;
	s.assign(aString, 2, std::string::npos);	// assign "hello"
	cout << s << endl;

	s.assign("two\nlines");		// assign a C-string (equivalent to operator=)
	cout << s << endl;
	s.assign("nico", 5);	// assign the characterr array: 'n' 'i' 'c' 'o' '\0'
	cout << s << endl;
	s.assign(5, 'x');
	cout << s << endl;		// assign five characters: 'x' 'x' 'x' 'x' 'x'
	s.assign(aString.begin(), aString.begin() + 3);
	cout << s << endl;
	s.resize(2);	// 尾部字符被移出
	cout << s << endl;
}