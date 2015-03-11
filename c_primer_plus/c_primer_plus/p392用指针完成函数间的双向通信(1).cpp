// p392 程序清单 14.8 用指针传递结构, 完成函数间的通信
#include <stdio.h>
#include <string.h>
#define LEN 20

struct namect {
	char fname[LEN];
	char lname[LEN];
	int letter;
};

void getinfo (struct namect *);
void makeinfo (struct namect *);
void showinfo (const struct namect *);

int main (void)
{
	struct namect person;

	getinfo (&person);
	makeinfo (&person);
	showinfo (&person);

	return 0;
}

void getinfo (struct namect * pst)
{
	puts ("First name:");
	gets (pst -> fname);
	puts ("Last name:");
	gets (pst -> lname);
}

void makeinfo (struct namect * pst)
{
	pst -> letter = strlen (pst -> fname) + 
					strlen (pst -> lname);
}

void showinfo (const struct namect * pst)
{
	printf ("%s%s, your name have %d letters!\n", pst -> fname, pst -> lname, pst -> letter);
}