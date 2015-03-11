//c primer plus 程序清单 4.1
//talkback.c -- 一个能为你提供一些信息的对话程序
#include <stdio.h>
#include <string.h>  //提供string()函数的原型
#define DENSITY 62.4  //density 密度 //人的密度(单位是英镑/每立方英尺)
int main ()
{
	float weight,volume;  //volume 体积
	int size,letters;  //letter 字母
	char name[40];  // name 是一个有四十个字符的数组                //为name分配连续的40个字节

	printf ("Hi!What's your first name?\n");
	scanf ("%s",&name);
	printf ("%s,What's your weight in pounds?\n",name);
	scanf ("%f",&weight);
	size = sizeof name;
	letters = strlen (name);                                        //strlen()的返回值为字节数
	volume = weight/DENSITY;
	printf ("Well,%s,your volume is %2.2f cubic feet.\n",name,volume);
	printf ("Also,your first name have %d letters.\n",letters);
	printf ("and we have %d byte to store it in.\n",size);
	return 0;
}