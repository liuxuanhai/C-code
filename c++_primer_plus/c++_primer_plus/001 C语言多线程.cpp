#include <iostream>
#include <process.h>
#include <string>
#include <windows.h>
using namespace std;

void thread0(void * pparams)
{
	string paramlocal = *(string *)pparams;
	cout << "thread0: " << paramlocal << endl;
	_endthread();
}

typedef struct
{
	string strParam;
	HANDLE handleParam;
} PARAM;

void thread1(void * pparams)
{
	PARAM temp = *(PARAM *)pparams;
	WaitForSingleObject(temp.handleParam, INFINITE);	// infinite
	cout << "Thread1: " << temp.strParam << endl;
}

int main()
{
	cout << "创建一个线程0: \n";
	string param = "我是主线程传到线程0的数据";
	_beginthread(thread0, 0, &param);

	HANDLE hEvent = CreateEvent(nullptr, false, false, nullptr);
	string strparam = "我是主线程传到事件线程1的数据";
	PARAM P = {strparam, hEvent};
	_beginthread(thread1, 0, &P);
	Sleep(2000);
	SetEvent(hEvent);

	Sleep(20);
}