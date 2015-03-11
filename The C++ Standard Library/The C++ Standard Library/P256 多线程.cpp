#include <QApplication>
#include "P255 Thread.h"

int main(int argc, char ** argv)
{
	QApplication app(argc, argv);
	ThreadDialog td;

	td.show();
	return app.exec();
}