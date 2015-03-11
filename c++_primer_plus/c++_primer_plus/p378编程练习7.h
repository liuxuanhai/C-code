// 编程练习 10.10 (7) 头文件

class Plorg
{
private:
	char name[20];
	int CI;
public:
	Plorg(const char * = "Plorga", int n = 0);
	void change(int);
	void show() const;
};