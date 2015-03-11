#include <QApplication>
#include "P027 sortdialog.h"
int main(int argc, char * argv[])
{
	QApplication app(argc, argv);
	SortDialog * dialog = new SortDialog;
	dialog->SetColumnRange('C', 'F');
	dialog->show();
	return app.exec();
}