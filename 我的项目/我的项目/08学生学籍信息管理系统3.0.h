// 创建: 2014-08-19 20:44:41
#ifndef STUDENT_H

#include <string>
#include <vector>
#include <map>

#define NAMESPACE_DATA_BEGIN	namespace data{
#define NAMESPACE_END			};

NAMESPACE_DATA_BEGIN	// 限定名称空间data, 这是纯数据类
using std::string;
class StuBaseInfo		// 学生基本信息类
{
private:
	int		number;		// 学号
	int		dormNum;	// 宿舍号
	string	name;		// 姓名
	string	sex;		// 型别
	string	tel;		// 电话
	string	label;		// 标签

public:
	StuBaseInfo() {}
	virtual ~StuBaseInfo() {}

	// 获取私有数据
	const int number()  const	{ return number; }
	const int dormNum() const	{ return dormNum; }
	const string &	name()	const	{ return name; }
	const string &	sex()	const	{ return sex; }
	const string &	tel()	const	{ return tel; }
	const string &	label() const	{ return label; }
	// 设置私有数据
	void setNumber(const int n)	{ number = n; }
	void setDormNum(const int n){ dormNum = n; }
	void setName(const string & s)	{ name = s; }
	void setSex(const string & s)	{ sex = s; }
	void setTel(const string & s)	{ tel = s; }
	void setLabel(const string & s)	{ label = s; }
};

class Stu	// 添加学生成绩
{
private:
	typedef struct
	{
		int ordinaryGrade;	// 平时成绩
		int examGrade;		// 卷面成绩
		double totalGrade;	// 综合成绩
	} GradeDataType;
	typedef std::map<string, GradeDataType> GradeType;
private:
	StuBaseInfo baseData;	// 学生基本资料
	std::pair<string, GradeDataType> tempGrade;	// 临时区
	GradeType	grades;		// 存储成绩数据

public:
	Stu() {}
	virtual ~Stu() {}

	// 获取
	const StuBaseInfo & baseData() const { return baseData; }
	const GradeType & grades() const { return grades; }
	// 设置

};

NAMESPACE_END	// namespace data

#endif