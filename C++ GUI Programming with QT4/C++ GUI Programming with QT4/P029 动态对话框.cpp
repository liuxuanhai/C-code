#include <QApplication>
#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QtUiTools/QUiLoader>  
#include <QFile>
int main(int argc, char * argv[])
{
	QApplication app(argc, argv);
	/*QDialog dialog;
	QPushButton * okButton = new QPushButton;
	QVBoxLayout * VLayout = new QVBoxLayout;
	okButton->setText("Ok");
	okButton->setCheckable(true);
	VLayout->addWidget(okButton);
	dialog.setLayout(VLayout);*/

	// 装入ui文件 形成动态对话框
	QUiLoader uiLoader;
	QFile file("P020 GoToCell.ui");
	QWidget * sortDialog = uiLoader.load(&file);

	/*QObject::connect(okButton, SIGNAL());*/

	/*dialog.show();*/

	return app.exec();
}