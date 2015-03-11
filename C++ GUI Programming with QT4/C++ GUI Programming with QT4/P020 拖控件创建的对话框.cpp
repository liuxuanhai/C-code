#define V2

#if defined V1
#include <QApplication>
#include <QDialog>
#include "GeneratedFiles/ui_P020 GoToCell.h"	// qmake生成一个.pro文件和一个makefile文件, qmake非常智能, 它可以自动检测到用户界面文件P020 GoToCell.ui并且可以生成适当的makefile规则来调用Qt的用户界面编译器(user interface compiler, uic), uic工具会将P020 GoToCell.ui文件转换成C++并且将转换结果存储在ui_P020 GoToCell.h文件中
												// 生成的ui_P020 GoToCell.h文件中包含了Ui::GoToCellDialog的定义, 该类是一个与P020 GoToCell.ui文件等价的C++文件. 这个类声明了一些成员变量, 他们存储这窗体中的子窗口部件和子部局, 以及用于初始化窗体的setupUi()函数;
int main(int argc, char * argv[])
{
	QApplication app(argc, argv);

	Ui::GoToCellDialog ui;
	QDialog * dialog = new QDialog;
	ui.setupUi(dialog);	// 生成的类没有任何基类, 当在文件中使用该窗体时, 可以创建一个QDialog对象, 然后把它传递给setupUi函数
	dialog->show();

	return app.exec();
}

#elif defined V2

#include <QApplication>
#include "P020 GoToCell.h"

int main(int argc, char * argv[])
{
	QApplication app(argc, argv);
	GoToCellDialog * dialog = new GoToCellDialog;
	dialog->show();
	return app.exec();
}

#endif