// 自己总结
#include <stdio.h>
#include <stdlib.h> // 为atoi()提供原型
int main(void)
{
	char * str1 = "12";
	char * str2 = "34heshixiong";
	char * str3 = "he56shixiong";
	char * str4 = "he7shixio8ng";
	char * str5 = "heshixiong";

	printf("%d\n", atoi(str1) * 2); // . int atoi(const char *);
	printf("%d\n", atoi(str2) * 2); // 如果参数是"34heshixiong"返回的是34
	printf("%d\n", atoi(str3) * 2); // 返回值为0, 但是标准c规定上述行为是未定义的
	printf("%d\n", atoi(str4) * 2); // 返回值为0, 但是标准c规定上述行为是未定义的
	printf("%d\n", atoi(str5) * 2); // 返回值为0, 但是标准c规定上述行为是未定义的

	return 0;
}