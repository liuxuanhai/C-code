// p336 程序清单 12.9 (二)
// 使用ANSI C的可移植算法
static unsigned long int next = 1;

int rand1 (void)
{
	next = next * 1103515245 + 12345;

	return (unsigned int)(next / 65536) % 32768;
}

void srand1 (unsigned int seed)
{
	next = seed;

	return;
}