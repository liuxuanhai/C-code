#include <iostream>
#include <cstdlib>
#include <ctime>
#include "研究 - 006类之队列类.h"
const int MIN_PER_HR = 60;

bool isNewCustomer(double x)	// 参数x为平均来一个顾客所需要的秒数
{
	return (std::rand() * x / RAND_MAX < 1);
}

int main(void)
{
	using std::cin;
	using std::cout;
	using std::endl;
	using std::ios_base;
	std::srand((unsigned long)std::time(0));

	cout << "队列的最大长度: ";
	int qs;
	cin >> qs;
	Queue line(qs);	// 创建一个队列

	cout << "输入模拟的小时数: ";
	int hours;
	cin >> hours;
	long cyclelimit = MIN_PER_HR * hours;	// 模拟的分钟数

	cout << "输入每小时平均有多少个顾客: ";
	double perhour;
	cin >> perhour;
	double min_per_cust;	// 平均每多少秒来一个顾客
	min_per_cust = MIN_PER_HR / perhour;

	Item temp;
	long turnaways = 0;	// 被拒绝的顾客数
	long customers = 0;	// 顾客的数量
	long served = 0;	// 接收完服务的数量
	long sum_line = 0;
	int wait_time = 0;	// 某位顾客的服务时间
	long line_wait = 0;	// 每位接收服务的顾客所等待时间的总和

		// 开始模拟

	for (int cycle = 0; cycle < cyclelimit; cycle++)
	{
			// 是否为队列增加长度

		if (isNewCustomer(min_per_cust))	// 如果有新顾客来了
		{
			if (line.isFull())
				turnaways++;
			else
			{
				customers++;
				temp.Set(cycle);	// 保存到来的时间
				line.isEnQueue(temp);	// 将顾客放入队列
			}
		}

			// 是否为队列减小长度

		if (wait_time <= 0 && !line.isEmpty())	// 如果本顾客接收完服务并且有人等待接收服务
		{
			line.isDeQueue(temp);	// 下一个顾客开始接受服务
			wait_time = temp.ptime();	// 记录本顾客接收服务的时间
			line_wait += cycle - temp.GetWhen();	// 保存从到来到开始接受服务之间的等待时间
			served++;
		}
		if (wait_time > 0)
			wait_time--;
		sum_line += line.iQueueCount();
	}

	if (customers > 0)
	{
		cout << "顾客数: " << customers << endl;
		cout << "接受了服务的顾客数: " << served << endl;
		cout << "被拒绝的顾客数: " << turnaways << endl;
		cout << "平均队列大小: ";
		cout.precision(2);
		cout.setf(ios_base::fixed, ios_base::floatfield);
		cout << (double)sum_line / cyclelimit << endl;
		cout << "顾客的平均等待时间: " << (double)line_wait / served << " minuties.\n";
	}
	else
		cout << "没有顾客.\n";
	cout << "Done!\n";

	return 0;
}