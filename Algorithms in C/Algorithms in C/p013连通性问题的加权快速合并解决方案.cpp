					// 合并 - 查找算法 之 快速合并(较慢查找)的加权版本

// 实现思路是大树吃小树(大树的根作为新树的根)

#include <cstdio>
#define  N	10000

int main(void)
{
	int i, j, p, q, id[N];
	int sz[N];  // 用于存储每个树结构的元素的数量;
				// 每个树结构的根元素对应的数组偏移量(或其保存的值)对应的sz同位置保存了此树结构的元素数量;
	
	for (i = 0; i < N; i++)
	{
		id[i] = i;
		sz[i] = 1;
	}

	while (scanf("%d %d\n", &p, &q) == 2)
	{

			// 查找

		for (i = p; i != id[i]; i = id[i]);
		for (j = q; j != id[j]; j = id[j]);

				// 去除连通项
		if (i == j)
			continue;

			// 合并

				// 比较树的大小, 将小树的根更新为大树的;
		if (sz[i] < sz[j])
		{
			id[i] = j;
			sz[j] += sz[i];
		} 
		else
		{
			id[j] = i; 
			sz[i] += sz[j];
		}

			// 输出没连通的

		printf("\t\t%d %d\n", p, q);
	}

	return 0;
}