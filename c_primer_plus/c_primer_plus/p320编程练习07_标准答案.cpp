// 编程练习 11.13 (7)
#include <stdio.h>
#include <string.h>
#define LEN 20
char * string_in(const char *, const char *);
int main(void)
{
	char orig[LEN] = "transportation";
	char * find;

	puts(orig);
	find = string_in(orig, "port");
	if (find)
		puts(find);
	else
		puts("No found");
	find = string_in(orig, "part");
	if (find)
		puts(find);
	else
		puts("No found");

	return 0;
}
char * string_in(const char * s1, const char * s2)
{
	int l2 = strlen(s2);
	int tries;  // maximum number of comparisons
	int nomatch = 1;  // set to 0 if match is found

	tries = strlen(s1) + 1 - l2; // 比较的次数, 如果两个字符一样长正好比较一次
	if (tries > 0)
		while ((nomatch = strncmp(s1, s2, l2)) && tries--)
			s1++;
	if (nomatch)
		return NULL;
	else
		return (char *) s1;  // cast const away
}