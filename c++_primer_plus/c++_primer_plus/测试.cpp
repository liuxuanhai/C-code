#include <iostream>
using namespace std;
int main (void)
{
	cout << sizeof('A') << sizeof('AB') << sizeof('ABC') << sizeof('ABCD') << endl;
	enum aaa{he, shi, xiong};
	
	enum aaa a;
	a = he;
	a = (enum aaa)0;
	cout << a << endl;
	
	return 0;
}