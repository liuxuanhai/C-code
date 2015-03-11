#include <string>
#include <iostream>
using namespace std;
class Student
{
public:
	enum show{Info, Gra, Info_and_Gra};
	show mode;
	enum is{Full, Empty};
	is is_info, is_gra;
private:
	const static int courseNum = 3;
	struct
	{
		struct
		{
			int number;
			string name;
			string sex;
			string tel;
			int domNum;
		}stuInfo;
		struct
		{
			string courseName;
			int triGrade;  // 平时成绩
			int examGrade;  // 卷面成绩
			double totalGrade;  // 综合成绩
		}stuGra[courseNum];
	}Stu;
	void set_info();
	void set_gra();
	void show_info(ostream &) const;
	void show_gra(ostream &) const;
	void GetFileGra(istream &, Student  &);
	
public:
	Student();
	friend istream & operator>>(istream &, Student &);
	friend ostream & operator<<(ostream &, const Student &);
	int StuNum() const {return Stu.stuInfo.number;}
	std::string StuName() const {return Stu.stuInfo.name;}
};