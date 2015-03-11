// 编程练习 9.6 (1) 标准答案(头文件)
const int Len = 40;
struct golf
{
	char fullname[Len];
	int handicap;
};

void setgolf(golf & g, const char * name, int hc);

int setgolf(golf & g);

void handicap(golf & g, int hc);

void showgolf(const golf & g);