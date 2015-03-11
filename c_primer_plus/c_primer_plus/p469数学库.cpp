// 程序清单 16.13 把直坐标转换为极坐标
#include <stdio.h>
#include <math.h>

#define RAD_TO_DEG (180 / (4 * atan ((double)1)))

typedef struct polar_v { // polar 极地的 两极的
	double magnitude;
	double angle;
} POLAR_V;              // 这里使用POLAR_V进行变量声明也行?!?!?!

typedef struct rect_v { // rect 成对出现的参数
	double x;
	double y;
} RECT_V;

POLAR_V rect_to_polar (RECT_V);

int main (void)
{
	RECT_V input;
	POLAR_V result;

	puts ("Enter x, y coordinates: q to qiut:");
	while (2 == scanf ("%lf %lf", &input.x, &input.y))
	{
		result = rect_to_polar (input);
		printf ("magnitude = %0.2f, angle = %0.2f\n",
			result.magnitude, result.angle);
	}
	puts ("bye");
	return 0;
}

POLAR_V rect_to_polar (RECT_V rv)
{
	POLAR_V pv;

	pv.magnitude = sqrt (rv.x * rv.y + rv.y * rv.y);
	if (pv.magnitude == 0)
		pv.angle = 0.0;
	else
		pv.angle = RAD_TO_DEG * atan2 (rv.y, rv.x);
	return pv;
}