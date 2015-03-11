// 快速查找 慢速合并
#include <stdio.h>

const int N = 10;

int main(void)
{
	int id[N];

	for (int i = 0; i < N; i++)
		id[i] = i;

	int p, q;

	while (scanf("%d %d", &p, &q) == 2)
	{
		if (id[p] == id[q])
			continue;

		int i;
		for (i = 0; i < N; i++)
			if (id[i] == id[p])
				id[i] = id[q];

		printf("\t\t%d %d 访问数组次数: %d\n\t\t", p, q, i);
		for (i = 0; i < N; i++)
			printf("%d ", id[i]);
		printf("\n");
	}

	return 0;
}