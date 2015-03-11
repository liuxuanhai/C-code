#include <QApplication>
#include "P010  FindDialog.h"
int main(int argc, char * argv[])
{
	QApplication App(argc, argv);
	FindDialog * dialog = new FindDialog;
	dialog->show();
	return App.exec();
}