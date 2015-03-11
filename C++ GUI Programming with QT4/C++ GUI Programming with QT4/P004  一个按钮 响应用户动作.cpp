#include <QApplication>
#include <QPushButton>
int main(int argc, char * argv[])
{
	QApplication App(argc, argv);
	QPushButton * button = new QPushButton("Quit");
	QObject::connect(button, SIGNAL(clicked()), &App, SLOT(quit()));	// 将一个用户的动作与一段代码连接起来
	button->show();
	return App.exec();
}