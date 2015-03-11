// 矩阵A与矩阵B相乘, 结果保存到矩阵C中
// 一维数组对应向量, 二维数组对应矩阵
#include <stdio.h>
#define N 3

int main(void)
{
	int A[N][N] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	int B[N][N] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
	int C[N][N];

	int i;
	for (int y = 0; y < N; y++)
		for (int x = 0; x < N; x++)
			for (i = 0, C[y][x] = 0; i < N; i++)
				//C[y][x] += A[y][i] * B[i][x];
				((int *)C)[y * N + x] += ((int *)A)[y * N + i] * ((int *)B)[i * N + x];
	for (int y = 0; y  < N; y++)
	{
		for (int x = 0; x < N; x++)
			printf("%3d ", C[y][x]);
		printf("\n");
	}
	printf("\n\n");

	return 0;
}