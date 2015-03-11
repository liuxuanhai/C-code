// 创建: 2014-08-26 13:00:08

#include <QApplication>	// 包含Qt图形化应用程序的 各种资源, 基本设置, 控制流, 事件处理...
	// 若是Qt的非图形化应用程序, 则需要包含<QCoreApplication>

#include <QPushButton>

int main(int argc, char ** argv)	// 完成图形显示, 事件处理的工作
{
	QApplication app(argc, argv);
	QPushButton b("Hello World!");	// 这里没有指定按钮的父窗口, 因此以自己为主窗口

	b.show();
	QObject::connect(&b, SIGNAL(clicked()), &app, SLOT(quit()));
	return app.exec();
}