// 20130710
// 学生成绩录入读取
#include <stdio.h>
#include <stdlib.h>
#define STUNUM 100
#define NAMENUM 20
#define SCOREFILE "001SutGra.txt"

typedef struct student {
	int num;
	char name[NAMENUM];
	int math;
	int chinese;
}stu;

int main(void)
{
	stu st[STUNUM];
	int i, j;
	FILE * stu_file;
	char str[1000];
	
	if(NULL == (stu_file = fopen(SCOREFILE, "r")))
	{
		printf("Can't read the %s file!", SCOREFILE);
		exit(EXIT_FAILURE);
	}
	rewind(stu_file);
	while (1 == ( i = fscanf(stu_file, "%s", str)))
		// 这里不能写成 0 != 因为当fscanf()不能读入的时候
		// 会一直停在那里尝试读入而不是放弃返回0
	{
		puts(str);
	}
	fclose(stu_file);

	for(i = 0; i <= 100; i++)
	{
		puts("Name:");
		gets(st[i].name);
		if('\0' == st[i].name[0])
			break;
		st[i].num = i + 1;
		puts("Math Score:");
		scanf("%d", &st[i].math);
		puts("Chinese Score:");
		scanf("%d", &st[i].chinese);
		getchar();
	}

	if(NULL == (stu_file = fopen(SCOREFILE, "w")))
	{
		printf("Can't open the %s file!", SCOREFILE);
		exit(EXIT_FAILURE);
	}
	for(j = 0; j < i; j++)
	{
		fprintf(stu_file, "%03d %15s %5d %5d\n",
			st[j].num, st[j].name, st[j].math, st[j].chinese);
	}
	fclose(stu_file);

	return 0;
}