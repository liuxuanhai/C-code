					// 合并 - 查找算法 之 带有等分路径压缩的加权快速合并算法

// 实现思路是每次输入新的对的时候, 两个元素对应的树枝都会被压缩, 压缩方法查看下边的详细解释;

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

			// 查找 将已经合并的, p, q元素所在树枝进行压缩

		for (i = p; i != id[i]; i = id[i])
			id[i] = id[id[i]];  // 比如2 → 5 → 6 → 1, 这个的效果就是在输入p: 2的时候, 将2 → 6, 然后由于1前面没有东西了, 所以6 → 1, 结果就是2 → 6 → 1;
		for (j = q; j != id[j]; j = id[j])
			id[j] = id[id[j]];

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