// 创建: 2014-08-28 08:38:16

#include "08Student.h"
#include <algorithm>
Student::Student(std::string str)
{
	baseinfo["name"] = str;
}

// 一个作为排序规则的二元判断式
bool cmp(const std::pair<std::string, std::string> & s1, const std::pair<std::string, std::string> & s2)
{
	return s1.first < s2.first;
}
const Student & operator<<(std::ostream & os, const Student & stu)
{
	std::sort(const_cast<Student &>(stu).baseinfo.begin() + 1, const_cast<Student &>(stu).baseinfo.end(), cmp);
	for (auto pos = const_cast<Student &>(stu).baseinfo.cbegin(); pos != const_cast<Student &>(stu).baseinfo.cend(); ++pos)
		std::cout << pos->first << ": " << pos->second << "  ";
	return stu;
}

const Student & operator>>(std::istream & os, Student & stu)
{
	using namespace std;
	cout << "输入字段信息, 比如: Sex = female 输入 Ctrl + Z 结束\n";
	string temp, t;
	while (cin >> temp >> t)
	{
		if (t != "=")
		{
			cout << "请按格式: Sex = female 输入:\n";
			while (getchar() != '\n');	// 清空缓冲
			continue;
		}
		cin >> t;
		stu.baseinfo[temp] = t;
		cout << "\b\b   √\n";
	}
	cin.clear();
	return stu;
}