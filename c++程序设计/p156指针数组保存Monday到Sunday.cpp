// p156 指针数组保存monday-sunday
#include <stdio.h>
#define SIZE 7

int main (void)
{
	char * week[SIZE] = {"Sunday",
					     "Monday", 
					     "Tuesday", 
					     "Wednesday",
						 "Thursday",
					     "Friday", 
					     "Saturday"};

	for (int i = 0; i < SIZE; i++)
		printf ("%s\n", week[i]);  // 这里应该写的是week[i]而不是*week[i] 因为用%s时给他的应该是一个指针而不是具体的值!!!

	return 0;
}