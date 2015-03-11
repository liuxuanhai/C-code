#include <stdio.h>
#define V 9		// 顶点数

int main(void)
{
	int x, y, adj[V][V];

		// 邻接矩阵初始化
	for (y = 0; y < V; y++)
		for (x = 0; x < V; x++)
			adj[y][x] = 0;
	for (x = 0; x < V; x++)	// 国际惯例, 对角线值都是一
		adj[x][x] = 1;

		// 读取用户输入
	while (scanf("%d %d", &x, &y) == 2)
	{
		adj[x][y] = 1;
		adj[y][x] = 1;
	}

	return 0;
}