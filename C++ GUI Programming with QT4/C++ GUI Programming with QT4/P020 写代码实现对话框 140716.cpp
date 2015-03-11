#include "P020 GoToCell 140716.h"
#include <QApplication>
#include <QDialog>

int main(int argc, char * argv[])
{
	QApplication app(argc, argv);

	GoToCellDialog GoToCell;
	GoToCell.show();

	return app.exec();
}