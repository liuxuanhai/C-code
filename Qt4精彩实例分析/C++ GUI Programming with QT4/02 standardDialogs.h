// 创建: 2014-08-26 13:13:16
#ifndef  STANDARDDIALOG_H
#define  STANDARDDIALOG_H

#include <QDialog>
#include <QLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>
#include <QColorDialog>
#include <QFontDialog>
class StandardDialogs : public QDialog
{
	Q_OBJECT
public:
	inline StandardDialogs(QWidget * parent, Qt::WindowFlags f = 0);
	inline ~StandardDialogs(){}
public:
	QGridLayout * layout;
	QPushButton * filePushButton;
	QPushButton * colorPushButton;
	QPushButton * fontPushButton;
	QLineEdit	* fileLineEdit;
	QLineEdit	* fontLineEdit;
	QFrame		* colorFrame;
private slots:
	inline void slotOpenFileDlg();
	inline void slotOpenColorDlg();
	inline void slotOpenFontDlg();
};

StandardDialogs::StandardDialogs(QWidget * parent, Qt::WindowFlags f): QDialog(parent, f)
{
	setWindowTitle(tr("Standard Dialogs"));

	layout = new QGridLayout(this);	// 创建布局的时候最好指定父窗口

	filePushButton = new QPushButton;
	filePushButton->setText(tr("File Dialog"));

	colorPushButton = new QPushButton(tr("Color Dialog"));

	fontPushButton = new QPushButton;
	fontPushButton->setText(tr("Font Dialog"));

	fileLineEdit = new QLineEdit;

	colorFrame = new QFrame;
	colorFrame->setFrameShape(QFrame::Box);
	colorFrame->setAutoFillBackground(true);	// true: setPalette(QPalette(color)) 才能够为其设定背景色

	fontLineEdit = new QLineEdit(tr("Hello World"));

	layout->addWidget(filePushButton, 0, 0);	
	layout->addWidget(fileLineEdit, 0, 1);	// 0, 1 第0行第1列 (y, x)
	layout->addWidget(colorPushButton, 1, 0);
	layout->addWidget(colorFrame, 1, 1);
	layout->addWidget(fontPushButton, 2, 0);
	layout->addWidget(fontLineEdit, 2, 1);

	layout->setMargin(150);	// 此部件距离边框的距离
	layout->setSpacing(50);	// 次部件内部的自部件之间的距离

	connect(filePushButton, SIGNAL(clicked()), this, SLOT(slotOpenFileDlg()));
	connect(colorPushButton, SIGNAL(clicked()), this, SLOT(slotOpenColorDlg()));
	connect(fontPushButton, SIGNAL(clicked()), this, SLOT(slotOpenFontDlg()));
}

void StandardDialogs::slotOpenFileDlg()
{
	QString s = QFileDialog::getOpenFileName(	// getOpenFileName() 静态函数, 返回文件名 或 ""(取消)
		this,					// 父窗口
		"open file dialog",		// 标题
		"/",					// 默认的目录 如果有文件名则是默认选中的文件
		"C++ files and Head files(*.cpp *.h);;C files(*c)"	// 对文件类型进行过滤	(*.cpp *.h)	显示两种, ";;" 隔离过滤器
		// QString * selectedFilter = 0,				// 用户选择的过滤器
		// Options options = 0
		);	
	fileLineEdit->setText(s.toLocal8Bit().constData());

			// QFileDialog 的静态函数
	// getOpenFileName	获得用户选择的文件名
	// getSaveFileName	获得用户保存的文件名
	// getExistingDirectory	获得用户选择的已存在的目录名
	// getOpenFileName		获得用户选择的文件名列表
}

void StandardDialogs::slotOpenColorDlg()
{
	QColor color = QColorDialog::getColor(Qt::blue);	// 静态函数, 返回颜色值	这里为什么未指定父窗口????
	if (color.isValid())	// 如果用户选择了取消, 则QColor::isValid()返回flase;
		colorFrame->setPalette(QPalette(color));
}

void StandardDialogs::slotOpenFontDlg()
{
	bool ok;
	QFont font = QFontDialog::getFont(&ok);	// 静态函数, 返回字体, 用户点Cancel, 返回默认字体, ok设为false
	if (ok)
		fontLineEdit->setFont(font);
}

#endif