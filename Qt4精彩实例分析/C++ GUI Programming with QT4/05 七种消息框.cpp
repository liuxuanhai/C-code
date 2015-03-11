// ´´½¨: 2014-08-27 12:24:22
#include <QApplication>
#include "05 messageBox.h"
int main(int argc, char ** argv)
{
	QApplication app(argc, argv);
	MessageBox information;

	information.show();
	return app.exec();
}