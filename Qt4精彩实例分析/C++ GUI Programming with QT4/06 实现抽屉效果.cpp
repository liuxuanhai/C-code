// ´´½¨: 2014-08-27 13:39:49
#include <QApplication>
#include "06 toolBox.h"

int main(int argc, char ** argv)
{
	QApplication app(argc, argv);
	Drawer d;

	d.show();
	return app.exec();
}