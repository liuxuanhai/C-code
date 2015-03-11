#include "P093 Plotter.h"
#include <QApplication>

int main(int argc, char ** argv)
{
	QApplication App(argc, argv);

	Plotter P;
	P.show();

	return App.exec();
}