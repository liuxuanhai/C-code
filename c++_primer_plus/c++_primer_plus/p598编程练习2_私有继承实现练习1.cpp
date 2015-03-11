#include <iostream>
#include <string>
#include <valarray>
//valarray<int> temp (0, 5)  有一个int类型的temp, 类型为valarray, 他的所有元素初始化为0, 一共有5个元素
// int a[3] = {0, 1, 2};
// valarray<int> temp2(a, 3); 把a复制给了temp2
using namespace std;

template<class T, class T1>
class Pair
{
private:
	T t;
	T1 t1;
public:
	Pair() {}
	Pair(const T & _t, const T1 & _t1) : t(_t), t1(_t1) {}
	T & first(){ return t;}
	T1 & second(){return t1;}
	T first() const {return t;}
	T1 second() const {return t1;}
};

typedef valarray<int> ArrayInt;

class Wine : private Pair<ArrayInt, ArrayInt>, private string
{
private:
	int yearsNum;
public:                               // 注意pair是怎么初始化的
	Wine() : string("none"), yearsNum(0), Pair(ArrayInt(), ArrayInt()){}
	Wine(const char * l, int y, const int yr[], const int bot[]);
	Wine(const char * l, int y) : string(l), yearsNum(y), Pair(ArrayInt(0, y), ArrayInt(0, y)){}
	void GetBottles(void);					// !!!!!!!  这里的初始化不要忘了加上, 以给ArrayInt分配足够的空间
	void Show(void);
	const string & Label(void) const {return (const string &)(*this);}  // 这里返回的私有继承的string用的方法!!!!!!!!!!!!!!!!!!!!
	int sum(void) const {return Pair::second().sum();}
};

Wine::Wine(const char * l, int y, const int yr[], const int bot[]) : string(l), yearsNum(y), Pair(ArrayInt(yr, y), ArrayInt(bot, y))
{                                                                                 // !!!!!!!!!! 同样这里也别忘了加上
	/*for (int i = 0; i < yearsNum; i++)
	{
		data.first()[i] = yr[i];
		data.second()[i] = bot[i];
	}*/
}

void Wine::GetBottles(void)
{
	if (yearsNum < 1)
	{
		cout << "No space allocated for data\n";
		return;
	}

	cout << "Enter " << (const string &)(*this) << " data for " << yearsNum << " year(s): \n";
	for (int i = 0; i < yearsNum; i++)
	{
		cout << "Enter year: ";
		cin >> Pair::first()[i];
		cout << "Enter bottles for that year: ";
		cin >> Pair::second()[i];
	}
}

void Wine::Show(void)
{
	cout << "Wine: "<< (const string &)(*this) <<"\n\tYear\tBottles\n";
	for (int i = 0; i < yearsNum; i++)
		cout << "\t" << Pair::first()[i] << "\t" << Pair::second()[i] << endl;
}

int main(void)
{
	using std::cin;
	using std::cout;
	using std::endl;

	cout << "Enter name of wine: ";
	char lab[50];
	cin.getline(lab, 50);
	cout << "Enter number of years: ";
	int yrs;
	cin >> yrs;

	Wine holding(lab, yrs);
	holding.GetBottles();
	holding.Show();

	const int YRS = 3;
	int y[YRS] = {1993, 1995, 1998};
	int b[YRS] = {48, 60, 72};
	Wine more("Gushing Grape Red", YRS, y, b);
	more.Show();
	cout << "Total bottle for " << more.Label() << ": " << more.sum() << endl;

	return 0;
}