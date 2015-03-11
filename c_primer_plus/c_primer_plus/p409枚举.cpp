// p409 程序清单 14.15
// 不能再同一个作用域中出现两个enum中的同样的标记, 两个enum中的相互不影响, 都可以是从0开始赋值
#include <stdio.h>
#include <string.h>          // strcmp()
// #include <stdbool.h>		 // c99特性
#define LEN 30

enum sprctrum {red, orange, yellow, green, blue, violet};
const char * colors[] = {"red", "orange", "yellow", "green",
						 "blue", "violet"};

int main (void)
{
	char choice[LEN];
	int color;// c++   ...   enum sprctrum color;// c
	bool color_is_found = false;

	puts ("输入一个颜色(空行退出):");
	while (gets (choice) != NULL && choice[0] != '\0')
	{
		for (color = red; color <= violet; color++)
			if (strcmp (choice, colors[color]) == 0)
			{
				color_is_found = true;
				break;
			}
		if (color_is_found)
			switch (color)
			{
				case red    : puts ("Roses are red.");
						      break;
				case orange : puts ("Poppies are orange.");
						      break;
				case yellow : puts ("Sunflowers are yellow.");
							  break;
				case green  : puts ("Grass is green.");
							  break;
				case blue   : puts ("Bluebells are blue.");
							  break;
				case violet : puts ("Violents are violent.");
							  break;
			}
		else
			puts ("无法识别的颜色!");
		color_is_found = false;
		puts ("输入一个颜色(空行退出):");
	}
	puts ("ok!");

	return 0;
}