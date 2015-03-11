// 多源代码文件程序的编译
// c primer plus  程序清单 9.9 p231
// usehotel.c -- 旅馆房间收费程序
// 与程序清单 9.10 一起编译
#include <stdio.h>
#include "9__11hotel.h"
#include "9__10hotel.cpp"                // 双引号表示被包含的文件位于当前工作目录下(该目录下一般包含源代码)
int main (void)
{
	int nights;
	double hotel_rate;
	int code;

	while ((code = menu ()) != QUIT)
	{
		switch (code)
		{
			case 1: hotel_rate = HOTEL1;
			        break;
			case 2: hotel_rate = HOTEL2;
			        break;
			case 3: hotel_rate = HOTEL3;
			        break;
			case 4: hotel_rate = HOTEL4;
			        break;
			default: hotel_rate = 0.0;
				     printf ("Oops!\n");
					 break;
		}
		nights = getnights ();
		showprice (hotel_rate, nights);
	}
	printf ("Thank you and goodbye. ");
	
	return 0;
}