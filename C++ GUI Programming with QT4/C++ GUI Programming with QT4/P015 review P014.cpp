#include <QApplication>
#include "P015 review P014.h"

int main(int argc, char * argv[])
{
	QApplication app(argc, argv);	// 创建一个QApplication对象, 用来管理整个应用程序所用到的资源
	FindDialog * dialog = new FindDialog;
	dialog->show();	// 使窗口部件可见, 创建窗口部件的时候, 标签通常是隐藏的, 这就允许我们可以先对其进行设置, 然后在显示他们, 从而避免了窗口部件的闪烁现象
	return app.exec();	// 将应用程序的控制权传递给Qt, 此时程序会进入时间循环状态, 这是一种等待模式, 程序会等候用户动作
}