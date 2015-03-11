#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define 表的二维数组

#ifdef 表的二维数组
	// point.h
typedef struct {float x; float y;} point;
float distance(point a, point b)
{
	float dx = a.x - b.x, dy = a.y - b.y;
	return sqrt(dx * dx + dy * dy);
}

typedef struct node *link;
struct node
{
	point	p;
	link	next;
};

link **malloc2d(int r, int c)
{
	int i;
	link **t = (link **)malloc(r * sizeof(int *));
	for (i = 0; i < r; i++)
		t[i] = (link *)malloc(c * sizeof(int));
	return t;
}

float randFloat()
{
	return (float)1.0 * rand() / RAND_MAX;
}

link **grid;
int G;
float d;
int cnt = 0;
void gridinsert(float x, float y)
{
	int i, j;
	link s;
	int X = (int)(x * G + 1);
	int Y = (int)(y * G + 1);
	link t = (link)malloc(sizeof *t);
	t->p.x = x;
	t->p.y = y;
	for (i = X - 1; i <= X+1; i++)
		for (j = Y - 1; j <= Y+1; j++)
			for (s = grid[i][j]; s != NULL; s = s->next)
				if (distance(s->p, t->p) < d)
					cnt++;
	t->next = grid[X][Y];
	grid[X][Y] = t;
}

int main(void)
{
	int i, j, N = 9;
	d = 0.3f;
	G = (float)(1 / d);
	grid = malloc2d(G+2, G+2);
	for (i = 0; i < G+2; i++)
		for (j = 0; j < G+2; j++)
			grid[i][j] = NULL;
	for (i = 0; i < N; i++)
		gridinsert(randFloat(), randFloat());
	printf("%d edges shorter than %f\n", cnt, d);
	return 0;
}
#else

// 平面上随机生成N个点, 统计距离小于d的点对的个数;

typedef struct
{
	float x;
	float y;
} point;

float distance(point a, point b);

float randFloat()
{
	return 1.0f * rand() / RAND_MAX;
}

int main(void)
{
	float d;
	printf("最短距离: ");
	scanf("%f", &d);
	int i, j, cnt = 0, N;
	printf("生成点的个数: ");
	scanf("%d", &N);

	point * a = (point *)malloc(N * (sizeof(*a)));

	for (i = 0; i < N; i++)
	{
		a[i].x = randFloat();
		a[i].y = randFloat();
	}
	for (i = 0; i < N; i++)
		for (j = i + 1; j < N; j++)
			if (distance(a[i], a[j]) < d)
				cnt++;
	printf("%d 个随机点对距离小于 %f\n", cnt, d);

	return 0;
}

float distance(point a, point b)
{
	float dx = a.x - b.x, dy = a.y - b.y;
	return sqrt(dx*dx + dy*dy);
}

#endif