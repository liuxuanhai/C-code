class Cd  // represents a CD disk
{
private:
	char performers[50];
	char label[20];  // 标签
	int selections;
	double playtime;
public:
	Cd(char * s1, char * s2, int n, double x);
	//Cd(const Cd & d);  // 复制构造函数  注意: 这里没有动态分配内存之类的东西, 所以默认的复制构造函数就可以实现了
	Cd();  // 默认构造函数
	virtual ~Cd();  // 析构函数
	virtual void Report() const;  // reports all CD data
	//virtual Cd & operator= (const Cd & d);  // 赋值函数  注意: 默认的就挺好
};

class Classic : public Cd
{
private:
	char best[100];
public:
	Classic(char * bes, char * s1, char * s2, int n, double x);
	Classic();
	//virtual ~Classic(); 这里的虚析构函数可以省略, 由于基类已经定义了虚析构函数, 所以这里会生成虚析构函数
	virtual void Report() const;
	//virtual Cd & operator=(const Cd & d);  // 这里既是是为派生类设计的也要使用基类参数引用????
};