#include <iostream>
using namespace std;
int main()
{
	void ToUpper(char *);
	int a;
	void ToLower(char *);
	void (*pf)(char *);

	ToUpper("a");
	(*ToUpper)("a");
	pf = ToUpper;
	(*pf)("a");
	pf("a");
	pf = ToUpper;
	(*pf)("a");
	pf("a");
	cout << "ToUpper: " << ToUpper << "    &ToUpper: " << &ToUpper <<"  *ToUpper: " << *ToUpper << endl;
	cout << "pf:      " << pf << "    &pf     : "<< &pf << "   *pf :     " << *pf << endl;
	cout << &a << endl;
	
	pf = &ToUpper;
	(*pf)("a");
	pf("a");
	cout << "ToUpper: " << ToUpper << "    &ToUpper: " << &ToUpper <<"  *ToUpper: " << *ToUpper << endl;
	cout << "pf:      " << pf << "    &pf     : "<< &pf << "   *pf :     " << *pf << endl;
	cout << &a << endl;
	
	int arr[2] = {96, 111};
	cout << "arr : " << arr << "   &arr : " << &arr <<"   *arr: "<< *arr << endl;
	printf("%d\n", *arr);
	cout << "arr[0] : " << arr[0] << "   &arr[0] : " << &arr[0] << "   *arr[0] : " << "*arr[0]error" << endl;

	return 0;
}

void ToUpper (char * a)
{
	cout << "up" << endl;
}

void ToLower(char *)
{
	cout << "lower" << endl;
}