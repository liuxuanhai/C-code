// ´´½¨: 2014-08-28 14:42:19
#include <QApplication>
#include "07 tableWidget.h"

int main(int argc, char ** argv)
{
	QApplication app(argc, argv);
	TableWidget t;
	t.show();
	return app.exec();
}