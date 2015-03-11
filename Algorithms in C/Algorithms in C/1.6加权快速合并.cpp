// 快速查找 慢速合并
#include <stdio.h>

const int N = 10;

int main(void)
{
	int id[N];
	int sz[N];

	for (int i = 0; i < N; i++)
	{
		id[i] = i;
		sz[i] = 1;
	}

	int p, q;

	while (scanf("%d %d", &p, &q) == 2)
	{
		int i, j;
		for (i = p; i != id[i]; i = id[i]);
		for (j = q; j != id[j]; j = id[j]);
		if (j == i)
		{
			printf("\t\t数组内容同上!\n");
			continue;
		}
		if (sz[i] > sz[j])
		{
			sz[i] += sz[j];
			id[j]  = id[i];
		}
		else
		{
			sz[j] += sz[i];
			id[i]  = id[j];
		}
		printf("\t\tid数组的内容: ");
		for (i = 0; i < N; i++)
			printf("%d ", id[i]);
		printf("\n");
	}

	return 0;
}