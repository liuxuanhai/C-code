#include <QApplication>	// 每个Qt类都有一个与该类同名(且大写)的头文件
#include <QLabel>
int main(int argc, char * argv[])
{
	QApplication app(argc, argv);	// 创建一个QApplication对象, 用来管理整个应用程序所用到的资源;
	QLabel *label = new QLabel("<h3><i>Hello </i> <font size = 20 color = red>Qt!</font></h3>");	// 创建一个显示"Hello Qt!"的QLabel窗口部件(widget: windows gadget(窗口配件)), 窗口部件就是用户界面中的一个可视化元素;
	label->show();	// 使得QLabel标签可见, 创建窗口部件的时候, 标签通常是隐藏的, 这就允许我们可以先对其进行设置, 然后再显示他们, 从而避免了窗口部件的闪烁现象;
	return app.exec();	// 将应用程序的控制权传递给Qt, 此时程序会进入事件循环状态, 这是一种等待模式, 程序会等候用户动作;
}
// QT是非常灵活的, 以至于任意窗口部件都可以用作窗口, 本例中, 用窗口部件QLabel作为应用程序的窗口;