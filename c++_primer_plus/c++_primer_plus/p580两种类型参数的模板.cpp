#include <iostream>
#include <string>
template <class T1, class T2>
class Pair
{
private:
	T1 a;
	T2 b;
public:
	Pair(const T1 & aval, const T2 & bval) : a(aval), b(bval) {}
	Pair() {}
	T1 & first();
	T2 & second();
	T1 first() const {return a;}
	T2 second() const {return b;}
};

// 显示具体化
template <class T1>
class Pair<T1, double>
{
private:
	T1 a;
	double b;
public:
	Pair(const T1 & aval, const double &bval): a(aval), b(bval) {};
	void first() {std::cout << "显示具体化: a = " << a << "  b = " << b << std::endl; }
};

template <class T1, class T2>
T1 & Pair<T1, T2>::first()
{
	return a;
}

template <class T1, class T2>
T2 & Pair<T1, T2>::second()
{
	return b;
}

//template <class T1>
//int & Pair<T1, int>::second()
//{
//	static int n = 0;
//	std::cout << "我是部分具体化哦: " << n++ << std::endl;
//	return b;
//}

int main()
{
	using std::cout;
	using std::endl;
	using std::string;

	Pair<int, double> aa(1, 1.1);
	aa.first();
	cout << endl;

	Pair<string, int> ratings[4] = 
	{
		Pair<string, int>("The Purpled Duck", 5),
		Pair<string, int>("Jaquie's Frisco AI Fresco", 4),
		Pair<string, int>("Cafe Souffle", 5),
		Pair<string, int>("Bertie's Eats", 3)
	};

	int joints = sizeof(ratings) / sizeof(Pair<string, int>);
	cout << "Rating:\t Eatery\n";
	for (int i = 0; i < joints; i++)
		cout << ratings[i].second() << ":\t "
		<< ratings[i].first() << endl;
	cout << "Oops! Revised rating:\n";
	ratings[3].first() = "Bertie's Fab Eats";
	ratings[3].second() = 6;
	cout << ratings[3].second() << ":\t "
		 << ratings[3].first() << endl;
	return 0;
}