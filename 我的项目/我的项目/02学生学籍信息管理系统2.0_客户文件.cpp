#include "02学生学籍信息管理系统2.0_头文件.h"
#include <fstream>
#include <cstdlib>
#include <windows.h>

int getlet(const char *);  // 容错选择
int getMainMenu();  // 信息/成绩管理选择 
void showStuArray(const Student *);  // 显示Student数组信息
void coutNumAndName(const Student &, int = 0);
int getSQLmenu();  // 四大语句选择
void Add(Student *);  // 四大语句之增(基本信息)
int getNum(const Student *, int = 0);  // 选择学号
void SiDaYuJu(void (&)(Student *), Student *);  // 对四大语句函数的引用
void Delete(Student *);  // 四大语句之删(基本信息)
void Change(Student * s){cin >> *s;}  // 四大语句之改(基本信息)
void Find(Student * s){cout << *s;}  // 四大语句之查(基本信息)
void stuArrayDESC(Student *);  // 按学号从小到大排序

int main()
{
	const char * fileName = "02学生学籍信息管理系统2.0.txt";
	ifstream fin;
	Student stu[100];
	int choice;
	int i = 0;
	SetConsoleTitleA("学生信息管理系统2.0  by: 大雄");
// 读取模式打开文件
	fin.open(fileName);
	if (!fin.is_open())
	{
		cout << "无法打开文件: " << fileName << endl;
		cout << "程序将会退出.\n";
		exit(EXIT_FAILURE);
	}

// 将文件中的学生信息保存到stu数组中
	for (i = 0; fin >> stu[i]; i++);
	
// 选择管理
	while ('4' != (choice = getMainMenu()))
	{
		system("cls");
		// 类模式选择
		for (int i = 0; i < 100; i++)
			if (choice == '1')
				stu[i].mode = stu[i].Info;
			else if (choice == '2')
				stu[i].mode = stu[i].Gra;
			else if (choice == '3')
			{
				stu[i].mode = stu[i].Info_and_Gra;
				if (stu[i].is_info == stu[i].Full)
					cout << stu[i];
			}
		if (choice == '3')
			continue;
		// 显示基本信息/成绩信息
		showStuArray(stu);
		// 四大语句操作
		switch (getSQLmenu())
		{
		case '1':
			if (choice == '1')
				Add(stu);
			else if (choice == '2')
				SiDaYuJu(Add, stu);
			break;
		case '2': SiDaYuJu(Delete, stu);break;
		case '3': SiDaYuJu(Change, stu);break;
		case '4': SiDaYuJu(Find, stu);break;
		case '5': break;
		}
	}
// 保存到文件中去
	ofstream fout;
	fout.open(fileName);
	stuArrayDESC(stu);
	for (int i = 0; i < 100; i++)
		if (stu[i].is_info == stu[i].Full)
		{
			stu[i].mode = stu[i].Info_and_Gra;
			fout << stu[i];
		}

	return 0;
}

int getlet(const char * str)
{
	char choice;
	while (cin >> choice && strchr(str, choice) == NULL)  // char * strchr(const char * s, int c) 该函数返回一个指向字符串s中存放字符c的第一个位置的指针(标记结束的空字符是字符串的一部分, 因此也可以搜索到它). 如果没有找到该字符, 函数返回空指针NULL
		// cin >> '字符' 中不包括空白符
		cout << "请输入\""<< str << "\"中的一个字符." << endl;
	while (cin.get() != '\n')  // 做出干净的函数, 不要执行完留出一个'\n'字符在输入流中
		continue;
	return choice;
}

void coutNumAndName(const Student & s, int form)
{
	if (form == 0)
		std::cout << "~~~以下是可以进行所选操作的学生~~~~\n";
	cout << "------\nNo.: " << s.StuNum();
	cout << "  Name: " << s.StuName();
	cout << "\n------\n";
}

int getMainMenu()
{
	cout << "1> 学生基本信息管理   2> 学生成绩信息管理"
		"   3> 查看所有   4> 退出\n";
	cout << "-----------------------------------------------------\n";
	return getlet("1234");
}

void showStuArray(const Student * s)
{
	for (int i = 0; i < 100; i++)
		if (s[i].mode == s[i].Info &&
			s[i].is_info == s[i].Full)
			cout << s[i];
		else if (s[i].mode == s[i].Gra &&
			s[i].is_gra == s[i].Full)
		{
			cout << "--> No.: " << s[i].StuNum() 
				<< "   Name: " << s[i].StuName()  << endl;
			cout << s[i];
		}
}

int getSQLmenu()
{
	cout << "1> 增  2> 删  3> 改  4> 查  5> 返回\n";
	cout << "----------------------------------\n";
	return getlet("12345");
}

void Add(Student * s)
{
	int j = 0;
	if (s->mode == s->Info)
		for (int i = 0; i < 100; i++)
			while (s[i].is_info == s[i].Empty)
			{
				cin >> s[i];
				cout << "1> 继续添加  2> 停止添加\n";
				if ('2' == getlet("12"))
				{
					i = 100;
					break;
				}
			}
	else if (s->mode == s->Gra)
		for (int i = 0; i < 100; i++)
			while (s[i].is_info == s[i].Full 
				&& s[i].is_gra == s[i].Empty)
			{
				cin >> s[i];
				cout << "1> 继续添加  2> 停止添加\n";
				if (getlet("12") == '1')
				{
					for (j = i; j < 100; j++)
						if (s[i].is_info == s[i].Full &&  // 如果有等待添加学生成绩的人
							s[i].is_gra == s[i].Empty)
							break;
					if (j == 100)
					{
						cout << "!!!注意: 没有可以执行的对象了,"
							"自动选择为\"停止添加\"!!!\n";
						i = 100;  // 跳出外层for循环
						break;  // 跳出内层while循环
					}
				}
				else
				{
					i = 100;
					break;
				}
			}
}

int getNum(const Student * s, int form)  // form默认为0, 当它改变为1的时候进行的是gra增的学号选择
{
	int num[100];
	int num2[100] = {-1};
	int i = 0;
	int flag = 0;
	int temp;
	for (int j = 0; j < 100; j++)
		if (s[j].mode == s[j].Info   // 为info的删, 改, 查做准备, 只有模式是info, 有基本信息的时候才能进行这三项操作(学号才能被选择)
			&& s[j].is_info == s[j].Full)
		{
			coutNumAndName(s[j], flag++);
			num[i++] = s[j].StuNum();
		}
		else if (s[j].mode == s[j].Gra  // 为gra的增做准备, 只有模式是gra, 基本信息有了, 没有成绩信息的时候学号才可以被选择
			&& s[j].is_info == s[j].Full)
			if (s[j].is_gra == s[j].Empty && form == 1)  // gra增模式
			{
				coutNumAndName(s[j], flag++);
				num[i++] = s[j].StuNum();
			}
			else if (s[j].is_gra == s[j].Full && form == 0)  // gra 删改查 模式
			{
				coutNumAndName(s[j], flag++);
				num2[i++] = s[j].StuNum();  // # 1
			}
	if (num2[0] != -1)  // 判断 # 1 是否执行
		for (int i = 0; i < 100; i++)
			num[i] = num2[i];
	cout << "输入操作学生的学号: ";
	while (cin >> temp)
	{
		for (int i = 0; i < 100; i++)
		{
			if (temp == num[i])
				return temp;
		}
		cout << "不属于可操作学号, 请重新输入: ";
	}
	return 999;  // 不可能的返回值, 用来查错误
}

void SiDaYuJu(void (&yuju)(Student *), Student * s)
{
	int num;
	if (yuju == Add && s->mode == s->Gra)  // gra增模式
		num = getNum(s, 1);
	else
		num = getNum(s);
	for (; s->StuNum() != num; s++);  // 寻找选择学生的位置
	yuju(s);  // 执行选择的四大语句之一
	cout << "ok!\n";
}

void Delete(Student * s)
{
	if (s->mode == s->Info)
		s->is_info = s->Empty;
	else if (s->mode == s->Gra)
		s->is_gra = s->Empty;
}

void stuArrayDESC(Student * s)
{
	Student temp;
	for (int i = 0; i < 99; i++)
		for (int j = i; j < 100; j++)
			if (s[i].StuNum() > s[j].StuNum())
			{
				temp = s[i];
				s[i] = s[j];
				s[j] = temp;
			}
}