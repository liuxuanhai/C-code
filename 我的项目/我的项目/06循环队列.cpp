#include "06—≠ª∑∂”¡–.h"
int main(void)
{
	SqQueue Q;
	InitQueue(&Q);
	ShowQueue(&Q);
	EnQueue(&Q, 3);
	ShowQueue(&Q);
	EnQueue(&Q, 2);
	ShowQueue(&Q);
	QElemType t;
	DeQueue(&Q, &t);
	ShowQueue(&Q);
	for (int i = 0; i < 100; i++)
	{
		static int flag = 0;
		if (!flag && !EnQueue(&Q, i))
			flag = 1;
		if (flag && !DeQueue(&Q, &i))
			flag = 0;
		ShowQueue(&Q);
	}

	return 0;
}