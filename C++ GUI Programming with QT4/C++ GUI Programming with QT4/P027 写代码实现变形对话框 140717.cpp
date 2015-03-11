#include <QApplication>
#include "P027 SortDialog 140717.h"

int main(int argc, char * argv[])
{
	QApplication app(argc, argv);

	QDialog * dialog = new QDialog;
	Ui_SortDialog sortdialog;
	sortdialog.setupUi(dialog);
	dialog->show();

	return app.exec();
}