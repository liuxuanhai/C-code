#include <QApplication>
#include <QPushButton>
int main(int argc, char * argv[])
{
	QApplication app(argc, argv);
	QPushButton * button = new QPushButton("Quit");	// 应用程序的主窗口部件使用的是QPushButton而不是QLabel
	QObject::connect(button, SIGNAL(clicked()), &app, SLOT(quit()));	// 将用户的一个动作(单击按钮)与一段代码连接起来
																		// Qt的窗口部件通过发射信号(signal)来表明一个用户动作已经发生了或者是一个状态已经改变了
																		// 这里把这个按钮的clicked()信号与QApplication对象的quit()槽连接起来
	button->show();
	return app.exec();
}

// 说明如何响应用户的动作