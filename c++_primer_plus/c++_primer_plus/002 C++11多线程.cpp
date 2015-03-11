#include <iostream>
#include <thread>

void threadTask()
{
	std::cout << "hello thread\n";
}

int main()
{
	std::thread t(threadTask);
	t.join();
	std::cout << "hello main thread";
}