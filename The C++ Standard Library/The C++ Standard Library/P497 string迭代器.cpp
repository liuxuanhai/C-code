#include <string>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <vector>
#include <locale>
using namespace std;

class bothWhiteSpaces
{
private:
	const locale & loc;		// locale 场所, 现场
public:
	// constructor
	// - save the locale object
	bothWhiteSpaces(const locale & l) : loc(l) {}
	// function call
	// - returns whether both characeters are whitespaces
	bool operator()(char elem1, char elem2)
	{
		return isspace(elem1, loc) && isspace(elem2, loc);
	}
};

bool nocase_compare(char c1, char c2)
{
	return toupper(c1) == toupper(c2);
}

int main()
{
			// 将string中的所有字符转换大小写

	// create a string
	string s("The zip code of Hondelage in Germany is 38108");
	cout << "original: " << s << endl;

	// lowercase all characters 
	transform(s.begin(), s.end(),	// source
		s.begin(),					// destination	将源转化后放到的地方
		tolower);					// operation
	cout << "lowered: " << s << endl;

	// uppercase all characters
	transform(s.begin(), s.end(), s.begin(), toupper);
	cout << "uppered: " << s << endl;

	cout << endl << endl << endl;

	string s1("This is a string");
	string s2("STRING");

			// 判断str1是不是与str2相等或者是不是str2的一个子串

	// compare case insensitive
	// equal()的调用者必须保证第二区间至少要和第一区间具有一样多的元素, 因此先比较字符串的大小是必要的
	if (s1.size() == s2.size() &&	// ensure same sizes
		equal(s1.begin(), s1.end(),	// first source string
		s2.begin(),					// second source stirng
		nocase_compare))			// comparison criterion
		cout << "the strings are equal " << endl;
	else
		cout << "the strings are not equal" << endl;

	// search case insensitive
	string::iterator pos;
	pos = search(s1.begin(), s1.end(),	// source stirng in which to serach
		s2.begin(), s2.end(),			// substring to search
		nocase_compare);				// comparison criterion
	if (pos == s1.end())
		cout << "s2 is not a substring of s1" << endl;
	else
		cout << '"' << s2 << "\" is a substirng of \""
			 << s1 << "\" (at index " << pos - s1.begin() << ")" << endl;

				// 逆序, 排序, 删除重复字符
	cout << endl << endl << endl;
	// create constant string
	const string hello("Hello, how are you?");	// const的string最后有一个多余的'\0'

	// initialize string s with all characters of string hello
	string s3(hello.begin(), hello.end());

	// iterate through all of the characters
	string::iterator pos3;
	for (pos3 = s3.begin(); pos3 != s3.end(); ++pos3)
		cout << *pos3;
	cout << endl;

	// reverse the order of all characters inside the string
	reverse(s3.begin(), s3.end());
	cout << "reverse: " << s3 << endl;
	// sort all characters insede the string
	sort(s3.begin(), s3.end());
	cout << "ordered: " << s3 << endl;
	// remove adjacent(邻近的) duplicates(复制)
	// - unique() reorders and returns new end	// unique 独特的 reorders 重订购, 重整理
	// - erase() shrinks(缩小) accordingly(因此, 于是, 相应的)
	s3.erase(unique(s3.begin(), s3.end()), s3.end());	// 将重复的字符删除
	cout << "no duplicates: " << s3 << endl;
	
	string s3Temp("123456789");
	vector<char> intv(s3Temp.begin(), s3Temp.end());
	for (vector<char>::iterator i = intv.begin(); i != intv.end(); ++i)
		cout << *i;
	cout << endl;
	reverse(intv.begin(), intv.end());
	for (vector<char>::iterator i = intv.begin(); i != intv.end(); ++i)
		cout << *i;
	cout << endl << endl << endl << endl;

				// 

	string contents;
	// don't skip leading whitespaces
	cin.unsetf(ios::skipws);
	// read all characters while compressing whitespaces
	unique_copy(istream_iterator<char>(cin),	// beginning of source
				 istream_iterator<char>(),		// end of source
				 back_inserter(contents),		// destination
				 bothWhiteSpaces(cin.getloc()));	// unique_copy()以bothWhiteSpaces为行为准则, 删除相邻重复空格
					// criterion for removing

	// process contents
	// - here: write it to the standard output
	cout << contents;
}