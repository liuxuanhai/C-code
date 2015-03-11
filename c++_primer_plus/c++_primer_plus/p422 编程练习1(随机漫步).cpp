#include <iostream>

	// 声明一个矢量类

class Vector
{
private:
	double x, y;	// 直角坐标表示
	double ang, dis;// 极坐标表示
	
	void Setxy();
	void Setangdis();
public:
	Vector(){x = y = ang = dis = 0.0;};

	void	SetXY(double x, double y){this->x = x; this->y = y; Setangdis();}
	void	SetAngDis(double ang, double dis){this->ang = ang; this->dis = dis; Setxy();}
	double	Getx(void) const {return x;}
	double	Gety(void) const {return y;}
};

#include <ctime>
#include <fstream>
int main(void)
{
	using std::cout;
	using std::endl;
	using std::cin;
	srand((unsigned long)time(0));

	double x = 0, y = 0, step, dis;
	Vector V;

	std::ofstream fcout;
	fcout.open("p422随机漫步数据.txt");

	cout << "输入步长: ";
	cin >> step;
	cout << "输入距离: ";
	cin >> dis;
	fcout << "步长: " << step << "距离: " << dis << endl;
	int i;
	for(i = 0; 1; i++)
	{
		V.SetAngDis(rand() % 360, step);
		x += V.Getx();
		y += V.Gety();
		fcout << i << ": (x, y) = (" << x << ',' << y << ")" << endl;
		if (sqrt(x * x + y * y) >= dis)
			break;
	}
	fcout << "经过 " << i << " 步, 最终走了 " << sqrt(x * x + y * y) << "的直线距离!\n";
	cout << "写入文件完成\n";
	return 0;
}

#include <cmath>
#define  TWOPIE		(2 * 3.1415926)
void Vector::Setxy()
{
	x = dis * cos(TWOPIE * ang / 360);
	y = dis * sin(TWOPIE * ang / 360);
}

void Vector::Setangdis()
{
	dis = sqrt(x * x + y * y);
	ang = atan2(y, x);
}