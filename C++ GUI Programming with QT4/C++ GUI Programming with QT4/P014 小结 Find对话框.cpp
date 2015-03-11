// 由于FindDialog类的定义包含Q_OBJECT宏, 因而由qmake生成的makefile将会自动生成一些运行moc的规则, moc就是指Qt的元对象编译器, 即meta-object compiler
// 为了使moc能够正常运行, 必须把类定义从实现文件中分离出来并放到头文件中, 由moc生成的代码会包含这个头文件, 并且会添加一些特殊的C++代码
#include <QApplication>	// 每个Qt类都有一个与该类同名(且大写)的头文件
#include "P010 FindDialog.h"
int main(int argc, char * argv[])
{
	QApplication app(argc, argv);	// 创建一个QApplication对象, 用来管理整个应用程序所用到的资源
	FindDialog * dialog = new FindDialog;
	dialog->show();	// 使窗口部件可见, 创建窗口部件的时候, 标签通常是隐藏的, 这就允许我们可以先对其进行设置, 然后在显示他们, 从而避免了窗口部件的闪烁现象
	return app.exec();	// 将应用程序的控制权传递给Qt, 此时程序会进入时间循环状态, 这是一种等待模式, 程序会等候用户动作
}
//	Qt是非常灵活的, 以至于任意窗口部件都可以用作窗口