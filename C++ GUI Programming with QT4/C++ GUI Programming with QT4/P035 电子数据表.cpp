#include "P036 MainWindow.h"
#include <QApplication>
#include <QSplashScreen>	// 在主窗口出现之前显示一个图片

int main(int argc, char * argv[])
{
	QApplication app(argc, argv);

	QSplashScreen * splash = new QSplashScreen;
	splash->setPixmap(QPixmap("images/begin.jpeg"));
	splash->show();

	Qt::Alignment topRight = Qt::AlignRight | Qt::AlignTop;
	splash->showMessage(QObject::tr("Setting up the main window..."), topRight, Qt::white);

	MainWindow * mainwindow = new MainWindow;

	splash->showMessage(QObject::tr("Loading modules..."));	// 加载模块列表...

	//loadModules();

	splash->showMessage(QObject::tr("Establishing connections..."), topRight, Qt::white);	// 建立链接...

	//establishConnections();

	mainwindow->show();
	splash->finish(mainwindow);
	delete splash;
	return app.exec();
}