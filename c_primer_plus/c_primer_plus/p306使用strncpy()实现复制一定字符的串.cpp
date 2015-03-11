// p306 程序清单 11.23  
#include <stdio.h>
#include <string.h>
#define LIM 3
#define SIZE 7
#define CPYSIZE 

int main (void)
{
	char qwords[LIM][SIZE];
	char temp[40];
	int i = 0;
	char aaaaa[6] = "week";
	char te[20];

	gets (te);
	strncpy (aaaaa, te, 9);   // 这段代码说明用strncpy()时会擦除原内容然后进行复制
		// 第三个参数n>=源字符串(包含'\0'),则目标字符串会有'\0'否则没有, 但是一种情况除外, 就是aaa是初始化的时候有了值, 这时候空位值都是0, 这样如果n比他可容纳的小, 后面不受影响的位置还是0, 可以充当'\0'
	puts (aaaaa);

	puts ("输入3个以q开始要进行复制的字符串.");
	while (i < LIM && gets(temp))
	{
		if (temp[0] == 'q')
		{                           // SIZE - 1此处表示的是只能复制最多六个字符
			strncpy (qwords[i], temp, SIZE - 1);  // 分配数组时会在数组最后一个元素后面的元素上加一个'\0' 所以这里SIZE - 1写成SIZE也行但是写成比SIZE大的数不行????
			qwords[i][SIZE - 1] = '\0';
			i++;
		}
		else
		{
			puts ("你输入的不是以q开头的字符串,请重新输入:");
			// gets(temp);
		}
	}

	for (i = 0; i < LIM; i++)
		puts (qwords[i]);

	return 0;
}