#include "p560MI深度学习_头文件.h"
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

// ============ Worker ===========
Worker::~Worker() {}

void Worker::Data() const
{
	cout << "Name: " << fullname << endl;
	cout << "Employee ID: " << id << endl;
}

void Worker::Get()
{
	getline(cin, fullname);
	cout << "Enter Worker's ID: ";
	cin >> id;
	while (cin.get() != '\n')
		continue;
}

void Worker::Set()
{
	cout << "Enter worker's name: ";
	getline(cin, fullname);
	cout << "Enter worker's ID: ";
	cin >> id;
	while (cin.get() != '\n')
		continue;
}

void Worker::Show() const
{
	cout << "Name: " << fullname << "\n";
	cout << "Employee ID: " << id << "\n";
}

// ============ Waiter =============
void Waiter::Set()
{
	/*Worker::Set();
	cout << "Enter waiter's panache rating: ";
	cin >> panache;
	while (cin.get() != '\n')
		continue;*/
	cout << "Enter waiter's name: ";
	Worker::Get();
	Get();
}

void Waiter::Show() const
{
	//cout << "Catetory: waiter\n";
	//Worker::Show();
	//cout << "Panache rating: " << panache << "\n";
	cout << "Catetory: waiter\n";
	Worker::Data();
	Data();
}

void Waiter::Data() const
{
	cout << "Panache rating: " << panache << "\n";
}

void Waiter::Get()
{
	cout << "Enter waiter's panache rating: ";
	cin >> panache;
	while (cin.get() != '\n')
		continue;
}

// ============= Singer =============

char * Singer::pv[] = {"other", "alto", "contralto", "soprano", "bass", "baritone", "tenor"};
void Singer::Set()
{
	cout << "Enter singer's name: ";
	Worker::Get();
	Get();
	/*Worker::Set();
	cout << "Enter number for singer's vocal range:\n";
	int i;
	for (i = 0; i < Vtypes; i++)
	{
		cout << i << ": " << pv[i] << "    ";
		if (i % 4 == 3)
			cout << endl;
	}
	if (i % 4 != 0)
		cout << endl;
	while (cin >> voice && (voice < 0 || voice >= Vtypes))
		cout << "Please enter a value >= 0 and < " << Vtypes << endl;
	while (cin.get() != '\n')
		continue;*/
}

void Singer::Show() const
{
	cout << "Category: singer\n";
	//Worker::Show();
	//cout << "Vocal range: " << pv[voice] << endl;
	Worker::Data();
	Data();
}

void Singer::Data() const
{
	cout << "Vocal range: " << pv[voice] << endl;
}

void Singer::Get()
{
	cout << "Enter number for singer's vocal range:\n";
	int i;
	for (i = 0; i < Vtypes; i++)
	{
		cout << i << ": " << pv[i] << "    ";
		if (i % 4 == 3)
			cout << endl;
	}
	if (i % 4 != 0)
		cout << endl;
	while (cin >> voice && (voice < 0 || voice >= Vtypes))
		cout << "Please enter a value >= 0 and < " << Vtypes << endl;
	while (cin.get() != '\n')
		continue;
}

void SingingWaiter::Data() const
{
	Singer::Data();
	Waiter::Data();
}

void SingingWaiter::Get()
{
	Waiter::Get();
	Singer::Get();
}

void SingingWaiter::Set()
{
	cout << "Enter singing waiter's name: ";
	Worker::Get();
	Get();
}

void SingingWaiter::Show() const
{
	cout << "Category: singing waiter\n";
	Worker::Data();
	Data();
}