// 自己总结
// continue对于for和while的略微不同
// continue语句导致改程序跳过循环体的剩余部分但是不会跳过循环的更新表达式
#include <iostream>
int main()
{
	int i;
	for ( i = 0; i <= 10; i++)
		continue; // 直接跳到更行表达式处, 然后跳到测试表达式处
	std::cout << "for:" << i << std::endl;
	i = 0;
	while ( i < 10 )
	{
		static int b = 0;
		b++;
		if ( 20 == b )
			break;
		continue; // 直接跳到更新表达式处, 有可能跳过了测试表达式语句而导致错误
		i++;
	}
	std::cout << "while:" << i << std::endl;

	return 0;
}