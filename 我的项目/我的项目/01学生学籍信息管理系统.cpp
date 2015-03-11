// 学生学籍信息管理系统1.0 by: 何士雄 电气8班 2012484119
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define NAMELEN     20    // 学生或课程等名字长度
#define SEX         4     // 性别长度
#define STUNUM      20   // 学生个数
#define SCORE_TABLE 3     // 科目数 
#define FILENAME    "01StuInfo.dat"
#define FILENAME1   "01StuGraInfo.dat"

struct StuInfo {
	int number;
	char name[NAMELEN];
	char sex[SEX];
	int domNum;
	char tel[NAMELEN];
};
struct StuGraInfo {
	char courseNum;
	char courseName[NAMELEN];
	int creditHour;        // 学分
	struct {
		int number;
		int triGrade;      // 平时成绩
		int examGrade;     // 卷面成绩
		float totalGrade;  // 综合总评成绩
	}score_table[STUNUM];
}s;

int getmenu (struct StuGraInfo * [], struct StuInfo * []);        // 提供操作选择
	int getlet (const char *); // 以一个字符串为参数,返回其中的一个字符
	int menuinfo (void);           // 提供具体的增加删除修改查看选项
	int menugra (void);
int showinfo (struct StuInfo * [], int);         
						  // 基本信息查看模块 返回文件内学生个数
void addinfo (struct StuInfo * [], int n);
						  // 基本信息增加模块
void deleteinfo (struct StuInfo * [], int num);
						  // 基本信息删除模块
void changeinfo (struct StuInfo * [], int num);
						  // 基本信息修改模块
void searchinfo (struct StuInfo * []);
						  // 基本信息查找模块
void initializeGra (struct StuGraInfo * [], struct StuInfo * []);
						  // 根据学生基本信息初始化成绩信息
void readGra (struct StuGraInfo * []);
						  // 将学生成绩信息保存到结构数组里
void showgrade (struct StuGraInfo * [], struct StuInfo * []);
						  // 成绩信息查看模块
void showDESC (struct StuGraInfo * [], struct StuInfo * []);
						  // 降序排列显示gra
void addgrade (struct StuGraInfo * [], struct StuInfo * [], int n);
						  // 成绩信息增加模块
void deletegra (struct StuGraInfo * [], struct StuInfo * [], int n);
void changegra (struct StuGraInfo * [], struct StuInfo * [], int n);

int main (void)
{
	int choice, i;
	struct StuInfo info[STUNUM];
						 // 学生基本信息结构数组
	struct StuGraInfo grade[SCORE_TABLE];
						 // 学生成绩信息结构数组
	struct StuInfo * infoPtr[STUNUM];
						 // 学生基本信息结构指针数组
	struct StuGraInfo * gradePtr[SCORE_TABLE];
						 // 学生成绩信息结构指针数组
	
	printf ("%45s", "学生成绩管理系统\n");
	printf ("%55s", "by 电8大雄\n\n");

	// 把各个结构的指针赋给指针数组
	for (i = 0; i < STUNUM; i++)
		infoPtr[i] = &info[i];
	for (i = 0; i < SCORE_TABLE; i++)
		gradePtr[i] = &grade[i];
	// 成绩信息的初始化
	initializeGra (gradePtr, infoPtr);

	// 选择具体操作
	choice = getmenu (gradePtr, infoPtr);
	
	switch (choice)
	{
		case '0' : showinfo (infoPtr, 0); 
				   break;
		case '1' : addinfo (infoPtr, showinfo (infoPtr, 1)); 
				   break;
		case '2' : deleteinfo (infoPtr, showinfo (infoPtr, 0)); 
				   break;
		case '3' : changeinfo (infoPtr, showinfo (infoPtr, 0)); 
			       break;
		case '4' : searchinfo (infoPtr); 
			       break;
		case '5' : showDESC (gradePtr, infoPtr); 
			       break;
		case '6' : readGra (gradePtr); 
			       addgrade (gradePtr, infoPtr, showinfo (infoPtr, 0)); 
				   break;
		case '7' : readGra (gradePtr); 
			       deletegra (gradePtr, infoPtr, showinfo (infoPtr, 0)); 
				   break;
		case '8' : readGra (gradePtr); 
			       changegra (gradePtr, infoPtr, showinfo (infoPtr, 0)); 
				   break;
		case '9' : exit (EXIT_SUCCESS);
		default  : puts ("switch出错!"); 
			       break;
	}
	system ("pause");
	return 0;
}

int getmenu (struct StuGraInfo * p [], struct StuInfo * ptr [])
{
	int choice;

	puts ("a) 学生基本信息操作    b) 学生成绩信息操作"
		"       c) 退出");
	choice = getlet("abc");
	switch (choice)
	{
		case 'a' : choice = menuinfo (); break;
		case 'b' : showgrade (p, ptr); choice = 5 + menugra (); break;
		case 'c' : exit (EXIT_SUCCESS); break;
		default  : puts ("switch 错误!"); break;
	}

	return choice;
}

int getlet (const char * str)
{
	char ch;
	
	ch = getchar ();
	while (NULL == strchr (str, ch))
							// strchr();返回ch在*str中第一次出现的指针
	{
		puts ("请输入以下列表中的一个字符:");
		puts (str);
		while (getchar () != '\n')
			continue;
		ch = getchar ();
	}
	while (getchar() != '\n')
			continue;

	return ch;
}

int menuinfo (void)
{
	int choice;

	puts ("0) 查看    1) 增加    2) 删除");
	puts ("3) 修改    4) 查找");
	choice = getlet("01234");

	return choice;
}

int menugra (void)
{
	int choice;

	puts ("0) 按学号降序排列    1) 录入成绩    2) 删除成绩");
	puts ("3) 修改成绩          4) 退出");
	choice = getlet("01234");

	return choice;
}

int showinfo (struct StuInfo * ptr[], int n)
{
	int num = 0; 
	FILE * name;
	if (NULL == (name = fopen (FILENAME, "rb")))
	{
		printf ("无法打开学生基本信息文件%s.", FILENAME);
		system ("pause");
		exit (EXIT_FAILURE);
	}
	if (0 == fread (ptr[0], sizeof (struct StuInfo), 1, name) && 1 != n)
	{
		puts ("暂时还没有学生基本信息录入文件.");
		system ("pause");
		exit (EXIT_FAILURE);
	}
	else
	{
		rewind (name);  // 回到文件起始位置!!!很重要
		for (num = 0; 0 != fread (ptr[num], sizeof (struct StuInfo), 1, name); num++)
		{
			if (ptr[num]->name[0] == '\0')
				printf ("学号: %-3d   此学生已经退学(休学).\n", ptr[num]->number);
			else
				printf ("学号: %-3d 姓名: %-10s 性别: %-4s 宿舍: %-4d 电话: %-11s\n",
				ptr[num]->number, ptr[num]->name, ptr[num]->sex, ptr[num]->domNum,
				ptr[num]->tel);
		}
	}
	fclose (name);
	return num;
}

void addinfo (struct StuInfo * ptr[], int n)
{	
	puts ("姓名(空行退出):"); 
	FILE * name;

	while (NULL != gets (ptr[n]->name) && ptr[n]->name[0] != '\0')
	{
		ptr[n]->number = n + 1;
		puts ("性别: ");
		gets (ptr[n]->sex);
		puts ("宿舍号: ");
		while (1 != scanf ("%d", &ptr[n]->domNum))
		{
			puts ("输入错误!宿舍号:");
			scanf ("%*s");
		}
		while (getchar () != '\n')
			continue;
		puts ("电话: ");
		gets (ptr[n]->tel);
		puts ("姓名(空行退出):");
		n++;
	}
	if (NULL == (name = fopen(FILENAME, "wb")))
	{
		printf ("无法打开学生基本信息文件%s.", FILENAME);
		system ("pause");
		exit (EXIT_FAILURE);
	}
	fwrite (ptr[0], sizeof (struct StuInfo), n, name);
	puts ("数据已经成功加入进去.");
	fclose (name);
}

void deleteinfo (struct StuInfo * ptr[], int n)
{
	int i, in;
	FILE * name;
	
	puts ("输入想要删除学生的学号:");
	while (1 != scanf ("%d", &in) || in <= 0 || in > n)
	{
		printf ("请输入1 - %d的数字.", n);
		puts ("输入想要删除学生的学号:");
	}
	for (i = 0; i < n; i++)
		if (ptr[i]->number == in)
			ptr[i]->name[0] = '\0';
	if (NULL == (name = fopen(FILENAME, "wb")))
	{
		printf ("无法打开学生基本信息文件%s.", FILENAME);
		system ("pause");
		exit (EXIT_FAILURE);
	}
	fwrite (ptr[0], sizeof (struct StuInfo), n, name);
	puts ("删除成功!");
	fclose (name);
}

void changeinfo (struct StuInfo * ptr[],  int n)
{
	int i, in;
	FILE * name;

	puts ("输入想要修改学生的学号:");
	while (1 != scanf ("%d", &in) || in <= 0 || in > n)
	{
		while (getchar () != '\n')
				continue;
		printf ("请输入1 - %d的数字.", n);
		puts ("输入想要修改学生的学号:");
	}
	while (getchar () != '\n')
				continue;
	for (i = 0; i < n; i++)
		if (ptr[i]->number == in)
		{
			puts ("姓名(空行退出):");
			gets (ptr[i]->name);
			puts ("性别: ");
			gets (ptr[i]->sex);
			puts ("宿舍号: ");
			scanf ("%d", &ptr[i]->domNum);
			while (getchar () != '\n')
				continue;
			puts ("电话: ");
			gets (ptr[i]->tel);
			break;
		}
	if (NULL == (name = fopen("StuInfo.dat", "wb")))
	{
		printf ("无法打开学生基本信息文件%s.", "StuInfo.dat");
		system ("pause");
		exit (EXIT_FAILURE);
	}
	fwrite (ptr[0], sizeof (struct StuInfo), n, name);
	puts ("修改成功.");
	fclose (name);
}

void searchinfo (struct StuInfo * ptr[])
{
	int num, in;
	FILE * name;

	if (NULL == (name = fopen(FILENAME, "rb")))
	{
		printf ("无法打开学生基本信息文件%s.", FILENAME);
		system ("pause");
		exit (EXIT_FAILURE);
	}
	for (num = 0; 0 != fread (ptr[num], sizeof (struct StuInfo), 1, name); num++);
	if (0 == num)
	{
		puts ("请至少添加一条学生基本信息再进行查找.");
		system ("pause");
		exit (EXIT_FAILURE);
	}
	printf ("输入要查询学生的学号(1-%d):\n", num);
	while (1 != scanf ("%d", &in) || in > num || in <= 0)
	{
		while (getchar () != '\n')
			continue;
		printf ("请输入1-%d的数字:\n", num);
	}
	rewind (name);
	in -=1;
	for (num = 0; 0 != fread (ptr[num], sizeof (struct StuInfo), 1, name); num++)
		if (num == in)
		{	
			if (ptr[in]->name[0] == '\0')
				printf ("学号: %-3d   此学生已经退学(休学).\n", ptr[in]->number);
			else
				printf ("学号: %-3d 姓名: %-10s 性别: %-4s 宿舍: %-4d 电话: %-11s\n",
				ptr[in]->number, ptr[in]->name, ptr[in]->sex, ptr[in]->domNum,
				ptr[in]->tel);
		}
	fclose (name);
}

void initializeGra (struct StuGraInfo * p[], struct StuInfo * ptr[])
{
	FILE * name, * name1;
	int i, j, num;

	if (NULL == (name = fopen (FILENAME, "rb")))
	{
		
		fclose (fopen (FILENAME, "wb")); // 创建文件
		if (NULL == (name = fopen (FILENAME, "rb")))
		{	
			printf ("无法打开文件%s.\n", FILENAME);
			exit (EXIT_FAILURE);
		}
	}
	// 在还没有学生信息的时候进行初始化
	if (0 == fread (ptr[0], sizeof (struct StuInfo), 1, name))
	{   // 课程编号, 课程名和学分的添加
		for (i = 0; i < SCORE_TABLE; i++)
			p[i]->courseNum = 'A' + i;
		for (i = 0; i < SCORE_TABLE; i++)
			p[i]->creditHour = i + 4;
		strcpy (p[0]->courseName, "数学");
		strcpy (p[1]->courseName, "英语");
		strcpy (p[2]->courseName, "程序设计");
		// 成绩信息的初始化
		for (j = 0; j < SCORE_TABLE; j++)
			for (i = 0; i < STUNUM; i++)
			{
				p[j]->score_table[i].number     = i + 1;
				p[j]->score_table[i].examGrade  = -1;
				p[j]->score_table[i].triGrade   = -1;
				p[j]->score_table[i].totalGrade = -1;
			}
		if (NULL == (name1 = fopen (FILENAME1, "wb")))
		{
			printf ("无法打开学生成绩信息文件%s.", FILENAME1);
			exit (EXIT_FAILURE);
		}
		fwrite (p[0], sizeof (struct StuGraInfo), SCORE_TABLE, name1);
		puts ("初始化学生成绩成功(当您添加第一条学生信息的之前我会进行初始化).");
		fclose (name1);
	}

	fclose (name);
	//showgrade (p, ptr);
}

void readGra (struct StuGraInfo * ptr [])
{
	FILE * name1;

	if (NULL == (name1 = fopen (FILENAME1, "rb")))
	{
		printf ("无法打开学生成绩信息文件%s.", FILENAME1);
		exit (EXIT_FAILURE);
	}
	fread (ptr[0], sizeof (struct StuGraInfo), SCORE_TABLE, name1);
	fclose (name1);
}

void showgrade (struct StuGraInfo * p[], struct StuInfo * ptr [])
{
	int i, j, num;
	FILE * name1;
	FILE * name;

	if (NULL == (name = fopen(FILENAME, "rb")))
	{
		printf ("无法打开学生基本信息文件%s.", FILENAME);
		system ("pause");
		exit (EXIT_FAILURE);
	}
	if (0 == fread (ptr[0], sizeof (struct StuInfo), 1, name))
	{
		puts ("学生基本信息为空, 请先填入至少一个学生的基本信息.");
		system ("pause");
		exit (EXIT_FAILURE);
	}
	rewind (name);
	for (num = 0; 0 != fread (ptr[num], sizeof (struct StuInfo), 1, name); num++);
	
	
	if (NULL == (name1 = fopen (FILENAME1, "rb")))
	{
		printf ("无法打开学生成绩信息文件%s.", FILENAME1);
		system ("pause");
		exit (EXIT_FAILURE);
	}
	fread (p[0], sizeof (struct StuGraInfo), SCORE_TABLE, name1);
	for (j = 0; j < SCORE_TABLE; j++)
	{
		printf ("%s(课程号:%c 学分:%d)的成绩如下:\n", 
		p[j]->courseName, p[j]->courseNum, p[j]->creditHour);
		for (i = 0; i < num; i++)
		{	
			if (ptr[i]->name[0] == '\0')
				printf (" 学号: %3d   此学生已经退学(休学).\n", ptr[i]->number);
			else if (p[j]->score_table[i].triGrade == -1)
				printf (" 学号: %3d       成绩还没有录入\n", p[j]->score_table[i].number);
			else if (p[j]->score_table[i].triGrade == -2)
				printf (" 学号: %3d       成绩被删除了\n", p[j]->score_table[i].number);
			else
				printf (" 学号: %3d 平时成绩: %3d 卷面成绩: %3d 综合成绩: %.2f\n",
				p[j]->score_table[i].number, p[j]->score_table[i].triGrade, 
				p[j]->score_table[i].examGrade, p[j]->score_table[i].totalGrade);
		}
	}
	fclose (name);
	fclose (name1);
	
	
}

void showDESC (struct StuGraInfo * p[], struct StuInfo * ptr [])
{
	int i, j, num;
	FILE * name1;
	FILE * name;

	if (NULL == (name = fopen(FILENAME, "rb")))
	{
		printf ("无法打开学生基本信息文件%s.", FILENAME);
		system ("pause");
		exit (EXIT_FAILURE);
	}
	for (num = 0; 0 != fread (ptr[num], sizeof (struct StuInfo), 1, name); num++);
	
	
	if (NULL == (name1 = fopen (FILENAME1, "rb")))
	{
		printf ("无法打开学生成绩信息文件%s.", FILENAME1);
		system ("pause");
		exit (EXIT_FAILURE);
	}
	fread (p[0], sizeof (struct StuGraInfo), SCORE_TABLE, name1);
	for (j = 0; j < SCORE_TABLE; j++)
	{
		printf ("%s(课程号:%c 学分:%d)的成绩如下:\n", 
		p[j]->courseName, p[j]->courseNum, p[j]->creditHour);
		for (i = num - 1; i >= 0; i--)
		{	
			if (ptr[i]->name[0] == '\0')
				printf (" 学号: %3d   此学生已经退学(休学).\n", ptr[i]->number);
			else if (p[j]->score_table[i].triGrade < 0)
				printf (" 学号: %3d       成绩还没有录入\n", p[j]->score_table[i].number);
			else
				printf (" 学号: %3d 平时成绩: %3d 卷面成绩: %3d 综合成绩: %.2f\n",
				p[j]->score_table[i].number, p[j]->score_table[i].triGrade, 
				p[j]->score_table[i].examGrade, p[j]->score_table[i].totalGrade);
		}
	}
	fclose (name);
	fclose (name1);
}

void addgrade (struct StuGraInfo * p[], struct StuInfo * ptr[], int n)
{
	int i, in, index;
	FILE * name1;
	
	puts ("输入想要添加成绩的学生的学号:");
	while (1 != scanf ("%d", &in) || in <= 0 || in > n)
	{
		printf ("请输入1 - %d的数字.", n);
		puts ("输入想要添加成绩的学生的学号:");
	}
	
	for (i = 0; i < n; i++)
	{
		if (ptr[i]->number == in)
		{	
			if (ptr[i]->name[0] == '\0')
			{
				puts ("此学生已经退学(休学), 不能添加成绩!");
				system ("pause");
				exit (EXIT_FAILURE);
			}
			else
			{
				printf ("下面进行对%s(学号:%d)的成绩进行录入:\n", 
					ptr[i]->name, ptr[i]->number);
				for (index = 0; index < SCORE_TABLE; index++)
				{
					if (p[index]->score_table[i].triGrade > 0)
					{
						puts ("此学生的成绩已经录入了.");
						system ("pause");
						exit (EXIT_FAILURE);
					}
					printf ("\n  %s成绩录入:\n", p[index]->courseName);
					printf ("    平时成绩:");
					while (1 != scanf ("%d", &p[index]->score_table[i].triGrade)
						|| p[index]->score_table[i].triGrade < 0 
						|| p[index]->score_table[i].triGrade > 100)
					{
						printf ("请输入1 - 100的数字.", n);
						printf ("    平时成绩:");
					}
					printf ("    卷面成绩:");
					while (1 != scanf ("%d", &p[index]->score_table[i].examGrade)
						|| p[index]->score_table[i].triGrade < 0 
						|| p[index]->score_table[i].triGrade > 100)
					{
						printf ("请输入1 - 100的数字.", n);
						printf ("    卷面成绩:");
					}
					p[index]->score_table[i].totalGrade = 0.3 * p[index]->score_table[i].triGrade
						+ 0.7 * p[index]->score_table[i].examGrade;
				}
			}
		}
	}
	if (NULL == (name1 = fopen (FILENAME1, "wb")))
	{
		printf ("无法打开学生成绩信息文件%s.", FILENAME1);
		system ("pause");
		exit (EXIT_FAILURE);
	}
	fwrite (p[0], sizeof (struct StuGraInfo), SCORE_TABLE, name1);
	puts ("添加成功!");
}

void deletegra (struct StuGraInfo * p[], struct StuInfo * ptr[], int n)
{
	int i, in, index;
	FILE * name1;
	
	puts ("输入想要删除成绩的学生的学号:");
	while (1 != scanf ("%d", &in) || in <= 0 || in > n)
	{
		printf ("请输入1 - %d的数字.", n);
		puts ("输入想要删除成绩的学生的学号:");
	}
	
	for (i = 0; i < n; i++)
	{
		if (ptr[i]->number == in)
		{	
			if (ptr[i]->name[0] == '\0')
			{
				puts ("此学生已经退学(休学), 没有成绩!");
				system ("pause");
				exit (EXIT_FAILURE);
			}
			else
			{
				for (index = 0; index < SCORE_TABLE; index++)
				{
					if (p[index]->score_table[i].triGrade == -1)
					{
						puts ("此学生的成绩本来就没有录入.");
						system ("pause");
						exit (EXIT_FAILURE);
					}
					else if (p[index]->score_table[i].triGrade == -2)
					{
						puts ("此学生的成绩已经被删除了.");
						system ("pause");
						exit (EXIT_FAILURE);
					}
					else
					{
						p[index]->score_table[i].triGrade  =  -2;
						p[index]->score_table[i].examGrade  = -1;
				        p[index]->score_table[i].totalGrade = -1;
					}
				}
			}
		}
	}
	if (NULL == (name1 = fopen (FILENAME1, "wb")))
	{
		printf ("无法打开学生成绩信息文件%s.", FILENAME1);
		system ("pause");
		exit (EXIT_FAILURE);
	}
	fwrite (p[0], sizeof (struct StuGraInfo), SCORE_TABLE, name1);
	puts ("成功删除!");
}

void changegra (struct StuGraInfo * p[], struct StuInfo * ptr[], int n)
{
	int i, in, index;
	FILE * name1;
	
	puts ("输入想要修改成绩的学生的学号:");
	while (1 != scanf ("%d", &in) || in <= 0 || in > n)
	{
		printf ("请输入1 - %d的数字.", n);
		puts ("输入想要修改成绩的学生的学号:");
	}
	
	for (i = 0; i < n; i++)
	{
		if (ptr[i]->number == in)
		{	
			if (ptr[i]->name[0] == '\0')
			{
				puts ("此学生已经退学(休学), 不能修改成绩!");
				system ("pause");
				exit (EXIT_FAILURE);
			}
			else
			{
				printf ("下面进行对%s(学号:%d)的成绩进行修改:\n", 
					ptr[i]->name, ptr[i]->number);
				for (index = 0; index < SCORE_TABLE; index++)
				{
					printf ("\n  %s成绩修改:\n", p[index]->courseName);
					printf ("    平时成绩:");
					while (1 != scanf ("%d", &p[index]->score_table[i].triGrade)
						|| p[index]->score_table[i].triGrade < 0 
						|| p[index]->score_table[i].triGrade > 100)
					{
						printf ("请输入1 - 100的数字.", n);
						printf ("    平时成绩:");
					}
					printf ("    卷面成绩:");
					while (1 != scanf ("%d", &p[index]->score_table[i].examGrade)
						|| p[index]->score_table[i].triGrade < 0 
						|| p[index]->score_table[i].triGrade > 100)
					{
						printf ("请输入1 - 100的数字.", n);
						printf ("    卷面成绩:");
					}
					p[index]->score_table[i].totalGrade = 0.3 * p[index]->score_table[i].triGrade
						+ 0.7 * p[index]->score_table[i].examGrade;
				}
			}
		}
	}
	if (NULL == (name1 = fopen (FILENAME1, "wb")))
	{
		printf ("无法打开学生成绩信息文件%s.", FILENAME1);
		system ("pause");
		exit (EXIT_FAILURE);
	}
	fwrite (p[0], sizeof (struct StuGraInfo), SCORE_TABLE, name1);
	puts ("修改成功!");
}