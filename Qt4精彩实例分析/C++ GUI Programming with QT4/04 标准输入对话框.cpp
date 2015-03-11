// ´´½¨: 2014-08-26 17:29:33
#include <QApplication>
#include "04 inputDialog.h"

int main(int argc, char ** argv)
{
	QApplication app(argc, argv);
	InputDlg inputDlg;

	inputDlg.show();
	return app.exec();
}