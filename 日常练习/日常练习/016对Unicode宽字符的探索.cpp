#include <string.h>
#include <stdio.h>

int main(void)
{
	printf("char - strlen: %d\n", strlen("123456"));
	printf("wchar - strlen: %d\n", strlen((char *)(L"123456")));  // 因为这里吧第二个字符的00当成了'\0' 所以显示为一个字符
	printf("wchar - wcslen: %d\n", wcslen(L"123456"));  // 成功执行了 这里的L必须加上去才行

	return 0;
}