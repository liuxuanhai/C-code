// p396 程序清单 14.10
#include <stdio.h>
#include <stdlib.h>          // malloc() free()
#include <string.h>          // strcpy() strlen()

struct namect {
	char * fname;
	char * lname;
	int letter;
};

void getinfo (struct namect *);         // 分配内存
void makeinfo (struct namect *);
void showinfo (const struct namect *);
void cleanup (struct namect *);         // 用完后释放内存

int main (void)
{
	struct namect person;

	getinfo (&person);
	makeinfo (&person);
	showinfo (&person);
	cleanup (&person);

	return 0;
}

void getinfo (struct namect * pst)
{
	char temp[81];
	puts ("First name:");
	gets (temp);
	pst -> fname = (char *) malloc (strlen (temp) + 1);  // 动态分配内存 把分配的地址给结构内的字符串指针
	strcpy (pst -> fname, temp);
	puts ("Last name:");
	gets (temp);
	pst -> lname = (char *) malloc (strlen (temp) + 1);  // 动态分配内存 把分配的地址给结构内的字符串指针
	strcpy (pst -> lname, temp);
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

void cleanup (struct namect * pst)
{
	free (pst -> fname);
	free (pst -> lname);
}