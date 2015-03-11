#include <QApplication>	// 每个Qt类都有一个同名头文件
#include <QLabel>
int main(int argc, char * argv[])
{
	QApplication app(argc, argv);	// 管理整个应用程序用到的资源
	QLabel * label = new QLabel("<h3>Hello <font size = 20 color = red>Qt!</font></h3>");	  // 创建一个窗口部件
	label->show();	// 使其可见, 创建的窗口部件默认是隐藏的
	return app.exec();	// 将应用程序的控制权传递给Qt, 此时程序进入事件循环状态, 等待用户动作
}