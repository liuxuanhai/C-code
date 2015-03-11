typedef char Item;

#define MAXSTACK 100

typedef struct stack
{
	Item items[MAXSTACK];
	int top;  // 栈中元素个数, 也是下一个空白位置的索引??
}Stack;

void Ini(Stack * ps){ps->top = 0;}
bool StackIsFull(const Stack * ps){return ps->top == MAXSTACK;}
bool StackIsEmpty(const Stack * ps){return ps->top == 0;}
bool Push(Item, Stack *);
bool Pop(Item *, Stack *);

#include <stdio.h>
#define SLEN 81

int main(void)
{
	Stack stch;
	char temp[SLEN];
	int i;
	char ch;

	Ini(&stch);
	printf("Enter a line (an empty line to quit):\n");
	while (gets(temp) && temp[0] != '\n')
	{
		i = 0;
		while (temp[i] != '\0' && !StackIsFull(&stch))
			Push(temp[i++], &stch);
		while (!StackIsEmpty(&stch))
		{
			Pop(&ch, &stch);
			putchar(ch);
		}
		puts("");
		printf("Enter a line (an empty line to quit):\n");
	}
	puts("Done!");
	return 0;
}

#include <stdlib.h>

bool Push(Item item, Stack * ps)
{
	if (StackIsFull(ps))
		return false;
	ps->items[ps->top++] = item;
	return true;
}

bool Pop(Item * pitem, Stack * ps)
{
	if (StackIsEmpty(ps))
		return false;
	*pitem = ps->items[--ps->top];  // !!!!!!!!
	return true;
}