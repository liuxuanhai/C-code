// 编程练习 11.9 (1) 随机漫步
// ######## 创建一个类, 有极坐标, 直角坐标两种形态 ########
#include <iostream>
#include <cmath>
#include <time.h>
#include <fstream>
#include <cstdlib>

static const double XIAN_TO_JIAO = atan2(1, 1) / 45;
class Zuobiao
{
public:
	enum Choice {JI, ZHIJIAO, ALL};
private:
	double x;
	double y;
	double dis;
	double jiaodu;
	void set_ji();
	void set_zhijiao();
public:
	Zuobiao();
	Zuobiao(double, double = 0.0, Choice = ZHIJIAO);
	Zuobiao operator+(Zuobiao &) const;
	friend std::ostream & operator<<(std::ostream &, Zuobiao &);
	double showdis() const {return dis;}
	void show(int = ALL, std::ostream & = std::cout);
};

int main()
{
	using std::cout;
	using std::cin;
	using std::endl;

	double dis_onece;
	double dis_tot;
	double totDis = 0;
	int i = 0;

	Zuobiao jizuobiao;
	Zuobiao now;
	std::ofstream inFile;

	cout << "输入步长:\n";
	cin >> dis_onece;
	cout << "输入总长:\n";
	cin >> dis_tot;
	cout << "Target Distance: " << dis_tot << ", ";
	cout << "Step Size: " << dis_onece << endl;

	inFile.open("p422随机漫步数据.txt");

	if (!inFile.is_open())
	{
		cout << "无法打开数据文件:p422随机漫步数据.txt\n";
		exit(EXIT_FAILURE);
	}

	srand(time(0));
	
	while (now.showdis() < dis_tot)
	{
		jizuobiao = Zuobiao( dis_onece , rand() % 360, Zuobiao::JI );
		now = jizuobiao + now;
		
		cout << ++i << ": ";
		now.show(now.ZHIJIAO);
		cout << endl;

		inFile << i << ": ";
		now.show(Zuobiao::ZHIJIAO, inFile);
		inFile << endl;

		totDis += now.showdis();
	}
// 输出到显示器
	cout << "After " << i << " steps, the subject has the following location:\n";
	now.show(now.ZHIJIAO);
	cout << "\nor\n";
	now.show(now.JI);
	cout << "Average outward distance per step = " << totDis / i << endl;

	// !!!!!!!其实根本不用使用now.show(now.ZHIJIAO);将它与cou<<隔开!!!!!!!!!
	cout << endl << "其实根本不用使用now.show(now.ZHIJIAO);将它与cou<<隔开\n" << now << endl << endl;

// 输出到文件
	inFile << "After " << i << " steps, the subject has the following location:\n";
	now.show(now.ZHIJIAO, inFile);
	inFile << "\nor\n";
	now.show(now.JI, inFile);
	inFile << "Average outward distance per step = " << totDis / i << endl;
	
	return 0;
}

void Zuobiao::set_ji()
{
	dis = sqrt( x * x + y * y);
	jiaodu = atan2(y, x) / XIAN_TO_JIAO;
}

void Zuobiao::set_zhijiao()
{
	double temp  = jiaodu * XIAN_TO_JIAO;
	x = dis * cos(temp);
	y = dis * sin(temp);
}

Zuobiao::Zuobiao()
{
	x = y = 0;
	set_ji();
}

Zuobiao::Zuobiao(double x_, double y_, Choice form)
{
	if (ZHIJIAO == form)  // default
	{
		x = x_;
		y = y_;
		set_ji();
	}
	else if (JI == form)
	{
		dis = x_;
		jiaodu = y_;
		set_zhijiao();
	}
	else
		std::cout << "不能识别的模式." << std::endl;
}

Zuobiao Zuobiao::operator+(Zuobiao & z) const
{
	/*Zuobiao temp;
	temp.x = x + z.x;
	temp.y = y + z.y;
	temp.set_ji();
	return temp;*/

	return Zuobiao(x + z.x, y + z.y);  // 选用这种方法更简单
}

std::ostream & operator<<(std::ostream & o, Zuobiao & z)
{
	using namespace std;
	o << "(m, a) = (" << z.dis << ", " << z.jiaodu << ")";
	o << "(x, y) = (" << z.x << ", " << z.y << ")";
	return o;
}

void Zuobiao::show(int form, std::ostream & o)
{
	using namespace std;
	if (form != ZHIJIAO)
		o << "(m, a) = (" << dis << ", " << jiaodu << ")";
	if (form != JI)
		o << "(x, y) = (" << x << ", " << y << ")";

}