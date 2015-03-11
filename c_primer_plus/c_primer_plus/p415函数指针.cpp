// p415 程序清单 14.16
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char showmenu (void);
void eatline (void);     // 读至行末
void show (void (* fp) (char *), char * str);
void ToUpper (char *);   
void ToLower (char *);
void Transpose (char *); // 大小写转置
void Dummy (char *);     // 不改变字符串

int main (void)
{
	char line[81];
	char copy[81];
	char choice;
	void (* pfun) (char *);   // 指向一个函数, 该函数接受一个char *参数, 并且没有返回值

	puts ("输入一个字符串(空行退出):");
	while (gets (line) != NULL && line[0] != '\0')
	{
		while ((choice = showmenu ()) != 'n')
		{
			switch (choice)
			{
				case 'u' : pfun = ToUpper; break;
				case 'l' : pfun = ToLower; break;
				case 't' : pfun = Transpose; break;
				case 'o' : pfun = Dummy; break;
			}
			strcpy (copy, line);    // 为show()制作一份拷贝
			show (pfun, copy);      // 使用用户选择的函数
		}
		puts ("输入一个字符串(空行退出):");
	}
	puts ("ok!");

	return 0;
}

char showmenu (void)
{
	char ans;

	puts ("Enter menu choice:");
	puts ("u) uppercase            l) lowercase");
	puts ("t) transeposed case     o) original case");
	puts ("n) next string");
	ans = getchar ();		// 获取用户响应
	ans = tolower (ans);	// 转换为小写
	eatline ();				// 剔除行中剩余部分
	while (strchr ("ulton", ans) == NULL)   // 在字符串"ulton"中查找ans首先出现的位置并返回他的地址
	{
		puts ("Please enter a u, l, t, o, n:");
		ans = getchar ();   // 获取用户响应
		ans = tolower (ans);// 转换为小写
		eatline ();
	}

	return ans;
}

void eatline (void)
{
	while (getchar () != '\n')
		continue;
}

void ToLower (char * str)
{
	while (*str)
	{
		*str = tolower (*str);
		str++;
	}
}

void ToUpper (char * str)
{
	while (*str)
	{
		*str = toupper (*str);
		str++;
	}
}

void Transpose (char * str)
{
	while (*str)
	{
		if (islower (*str))
			*str = toupper (*str);
		else if (isupper (*str))
			*str = tolower (*str);
		str++;
	}
}

void Dummy (char *)
{
	// 不改变字符串
}

void show (void (* fp) (char *), char * str)
{
	(*fp) (str);  // 把用户选择的函数作用于str
	puts (str);
}