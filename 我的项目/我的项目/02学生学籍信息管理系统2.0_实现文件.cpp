#include "02学生学籍信息管理系统2.0_头文件.h"
Student::Student()
{
	mode = Info;
	is_info = Empty;
	is_gra = Empty;
}

void Student::set_info()
{
	cout << "学号: ";
	cin >> Stu.stuInfo.number;
	cout << "姓名: ";
	cin >> Stu.stuInfo.name;
	cout << "性别: ";
	cin >> Stu.stuInfo.sex;
	cout << "电话: ";
	cin >> Stu.stuInfo.tel;
	cout << "宿舍: ";
	cin >> Stu.stuInfo.domNum;
	is_info = Full;
}

void Student::set_gra()
{
	if (is_info == Empty)
		cout << "请先输入学生的基本信息!\n";
	else
	{
		Stu.stuGra[0].courseName = "数学";
		Stu.stuGra[1].courseName = "英语";
		Stu.stuGra[2].courseName = "程序设计";
		for (int i = 0; i < courseNum; i++)
		{
			cout << Stu.stuGra[i].courseName << "成绩录入:\n";
			cout << "\t平时成绩: ";
			cin >> Stu.stuGra[i].triGrade;
			cout << "\t卷面成绩: ";
			cin >> Stu.stuGra[i].examGrade;
			Stu.stuGra[i].totalGrade = Stu.stuGra[i].triGrade * 0.3
				+ Stu.stuGra[i].examGrade * 0.7;
			is_gra = Full;
		}
	}
}

void Student::show_info(ostream & os) const
{
	if (is_info == Full)
	{
		os << "学号: " << Stu.stuInfo.number;
		os << "   姓名: " << Stu.stuInfo.name;
		os << "   性别: " << Stu.stuInfo.sex;
		os << "   宿舍: " << Stu.stuInfo.domNum;
		os << "   电话: " << Stu.stuInfo.tel << endl;
	}
	else if (is_info == Empty)
		os << "学生基本信息是空的.\n";

}

void Student::show_gra(ostream & os) const
{
	if (is_info == Empty)
		os << "学生基本信息为空, 无法显示成绩\n";
	else if (is_gra == Full)
		for (int i = 0; i < courseNum; i++)
		{
			os << Stu.stuGra[i].courseName << "成绩:\n";
			os << "   平时成绩: " << Stu.stuGra[i].triGrade;
			os << "   卷面成绩: " << Stu.stuGra[i].examGrade;
			os << "   综合成绩: " << Stu.stuGra[i].totalGrade << endl;
		}
	//else if (is_gra == Empty)
	//	os << "学生成绩为空.\n";
}

void Student::GetFileGra(istream & is, Student & s)
{
	string temp;
	if (is >> temp)  // 防止空文件执行s.is_info = Full;
	{
		is >> s.Stu.stuInfo.number;
		is >> temp;is >> s.Stu.stuInfo.name;
		is >> temp;is >> s.Stu.stuInfo.sex;
		is >> temp;is >> s.Stu.stuInfo.domNum;
		is >> temp;is >> s.Stu.stuInfo.tel;
		s.is_info = Full;
	}
	const string tt[courseNum] = {"数学", "英语", "程序设计"};
	for (int i = 0; is >> temp && temp != "----------------------------"; i++)
	{
		s.Stu.stuGra[i].courseName = tt[i];
		is >> temp;is >> s.Stu.stuGra[i].triGrade;
		is >> temp;is >> s.Stu.stuGra[i].examGrade;
		is >> temp;is >> s.Stu.stuGra[i].totalGrade;
		s.is_gra = Full;
		s.mode = Info_and_Gra;
	}
}

istream & operator>>(istream & is, Student & s)
{
	if (is == cin)
	{
		if (s.mode == s.Info)
			s.set_info();
		else if (s.mode == s.Gra)
			s.set_gra();
		else if (s.mode == s.Info_and_Gra)
		{
			s.set_info();
			s.set_gra();
		}
	}
	else
		s.GetFileGra(is, s);
	
	return is;
}

ostream & operator<<(ostream & os, const Student & s)
{
	if (s.mode == s.Info)
		s.show_info(os);
	else if (s.mode == s.Gra)
		s.show_gra(os);
	else if (s.mode == s.Info_and_Gra)
	{
		s.show_info(os);
		s.show_gra(os);
	}
	os << "----------------------------";  // 有区分读取块的重要作用
	os << '\n';
	return os;
}