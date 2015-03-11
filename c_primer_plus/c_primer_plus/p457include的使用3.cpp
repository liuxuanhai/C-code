// 程序清单 16.8
#include <stdio.h>
#include "p456include的使用1.h"
      // 还将连接p457include的使用2.h

int main (void)
{
	names candidate;
	get_names (&candidate);
	printf ("Let's welcome ");
	show_names (&candidate);
	printf (" to this program!\n");

	return 0;
}