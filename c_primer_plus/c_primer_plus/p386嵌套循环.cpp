// p386 程序清单 14.3 
#include <stdio.h>
#define LEN 20

const char * msgs[5] = {
	"    Thank you for the wonderful evening, ",
	"you certainly prove that a ",
	"is a special kind of guy. We must get together ",
	"over a delicious ",
	" and have a few laughs"
}; 
struct names {
	char first[LEN];
	char last[LEN];
};
struct guy {
	struct names handle;        // 嵌套结构
	char favfood[LEN];
	char job[LEN];
	float income;
};

int main (void)
{
	struct guy fellow = {
		{"He","Shixiong"},
		"grilled salmon",
		"personality coach",
		58112.00
	};
	printf ("Dear %s, \n\n", fellow.handle.first);
	printf ("%s%s.\n", msgs[0], fellow.handle.last);
	printf ("%s%s\n", msgs[1], fellow.job);
	printf ("%s\n", msgs[2]);
	printf ("%s%s%s", msgs[3], fellow.favfood, msgs[4]);
	if (fellow.income > 15000.0)
		puts ("!!");
	else if (fellow.income > 7500.0)
		puts ("!");
	else
		puts (".");
	printf ("\n%40s%s\n", " ", "See you soon,");
	printf ("%40s%s\n", " ", "HR from tencent");
	
	return 0;
}