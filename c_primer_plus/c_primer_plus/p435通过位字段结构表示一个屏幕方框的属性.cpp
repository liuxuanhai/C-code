// 程序清单 15.3
#include <stdio.h>
// 是否透明和是否可见
#define YES      1
#define NO       0
// 边框的样式
#define SOLID    0  // 实心的, 固体
#define DOTTED   1  // 有点的
#define DASHED   2  // 虚线
// 三原色
#define BLUE     4
#define GREEN    2
#define RED      1
// 混合颜色
#define BLACK    0
#define YELLOW   (RED | GREEN)
#define MAGENTA  (RED | BLUE)   // 紫红的, 洋红的
#define CYAN     (GREEN | BLUE) // 青色, 蓝绿色
#define WHITE    (RED | GREEN | BLUE)

const char * colors[8] = {"black", "red", "green", "yellow", 
	"blue", "magenta", "cyan", "white"};
struct box_props {
	unsigned int opaque        : 1;
	unsigned int fill_color    : 3;
	unsigned int               : 4;
	unsigned int show_border   : 1;
	unsigned int border_color  : 3;
	unsigned int border_style  : 2;
	unsigned int               : 2;
};

void show_settings (const struct box_props * pb);

int main (void)
{
	// 创建和初始化box_props结构
	struct box_props box = {YES, YELLOW, YES, GREEN, DASHED};
	puts ("通常的屏幕边框:");
	show_settings (&box);

	box.opaque = NO;
	box.fill_color = WHITE;
	box.border_color = MAGENTA;
	box.border_style = SOLID;
	puts ("屏幕边框模型:");
	show_settings (&box);

	return 0;
}

void show_settings (const struct box_props * pb)
{
	printf ("Box is %s.\n", 
		pb->opaque == YES ? "opaque" : "transparent");
	printf ("The fill color is %s.\n",
		colors[pb->fill_color]);
	printf ("Border %s.\n",
		pb->show_border == YES ? "shown" : "not shown");
	printf ("The border color is %s.\n",
		colors[pb->border_color]);
	printf ("The border style is ");
	switch (pb->border_style)
	{
		case SOLID  : printf ("solid.\n"); break;
		case DOTTED : printf ("dotted.\n"); break;
		case DASHED : puts ("dashed."); break;
		default     : puts ("无法识别的边框种类.");
	}
}