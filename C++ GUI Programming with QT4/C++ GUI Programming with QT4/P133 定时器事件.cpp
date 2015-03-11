#include <QApplication>
#include "P131 Ticker.h"

int main(int argc, char ** argv)
{
	QApplication App(argc, argv);

	Ticker T;
	T.setText(" 123456789 ");
	T.show();

	return App.exec();
}