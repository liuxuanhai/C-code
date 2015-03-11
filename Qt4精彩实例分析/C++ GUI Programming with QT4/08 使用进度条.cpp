#include "08 QProgressBar and QProgressDialog.h"
#include <QApplication>

int main(int argc, char ** argv)
{
	QApplication app(argc, argv);

	Progress p;

	p.show();
	return app.exec();
}