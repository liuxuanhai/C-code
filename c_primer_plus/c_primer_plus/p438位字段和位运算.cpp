// 程序清单 15.4
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
// 位运算中使用的常量
#define OPAQUE    0x1
#define FILL_BLUE 0x8
#define FILL_RED  0x2
#define FILL_GREEN 0x4
#define FILL_MASK 0xE
#define BORDER    0x100
#define BORDER_BLUE   0x800
#define BORDER_GREEN  0x400
#define BORDER_RED    0x200
#define BORDER_MASK   0xE00
#define B_SOLID       0
#define B_DOTTER      0x1000
#define B_DASHED      0x2000
#define STYLE_MASK    0x3000

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

union Views{
	struct box_props st_view;
	unsigned int ui_view;
};

void show_settings (const struct box_props * pb);
void show_settings1 (unsigned short);
char * itobs (int, char *);  // 把short值以二进制形式显示

int main (void)
{
	union Views box = {{YES, YELLOW, YES, GREEN, DASHED}};
	char bin_str [8 * sizeof (unsigned int) + 1];

	printf ("默认屏幕边框:\n");
	show_settings (&box.st_view);
	printf ("\n使用位运算后:\n");
	show_settings1 (box.ui_view);

	printf ("bits are %s\n", itobs (box.ui_view, bin_str));
	box.ui_view &= ~FILL_MASK;               // 把代表填充色的位清零
	box.ui_view |= (FILL_BLUE | FILL_GREEN); // 重置填充色
	box.ui_view ^= OPAQUE;                   // 转置指示是否透明的位
	box.ui_view |= BORDER_RED;               // 错误的方法
	box.ui_view &= ~STYLE_MASK;              // 清除样式位
	box.ui_view |= B_DOTTER;                 // 把样式设置为点

	printf ("\nModified(修改) box settings: \n");
	show_settings (&box.st_view);
	printf ("\n修改后使用位运算:\n");
	show_settings1 (box.ui_view);
	printf ("Bits are %s\n", itobs (box.ui_view, bin_str));
	
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

void show_settings1 (unsigned short us)
{
	printf ("Box is %s.\n",
		us & OPAQUE == OPAQUE ? "opaque" : "transparent");
	printf ("The fill color is %s.\n", colors[(us >> 1) & 07]);
	printf ("Border %s.\n", 
		us & BORDER == BORDER ? "shown" : "not shown");
	printf ("The border style is ");
	switch (us & STYLE_MASK)
	{
	case B_SOLID : printf ("solid.\n"); break;
	case B_DOTTER : printf ("dotted.\n"); break;
	case B_DASHED : printf ("dashed\n"); break;
	default: printf ("unknown type.\n"); break;
	}
	printf ("The border color is %s.\n", colors [(us >> 9 & 07)]);
}

// 把int转换成二进制字符串
char * itobs (int n, char * ps)
{
	int i;
	static int size = 8 * sizeof (unsigned int);

	for (i = size - 1; i >= 0; i--, n>>=1)
		ps[i] = (01 & n) + '0';
	ps[size] = '\0';
	return ps;
}