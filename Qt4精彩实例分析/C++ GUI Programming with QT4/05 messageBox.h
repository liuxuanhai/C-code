// 创建: 2014-08-27 12:07:45
// 七种消息框: 
//		1.	Question消息框, Information消息框, Warning消息框, Critical(严重警告)消息框
//			用法大同小异, 一般包含一个提示信息, 一个图标以及若干按钮
//		2.	About消息框, AboutQt消息框, Custom(自定义)消息框

#ifndef INFORMATIONBOX_H
#define INFORMATIONBOX_H

#include <QWidget>
#include <QPushButton>
#include <QLayout>
#include <QMessageBox>

class MessageBox: public QWidget
{
	Q_OBJECT
private:
	QPushButton * questionButton;
	QPushButton * informationButton;
	QPushButton * warningButton;
	QPushButton * criticalButton;
	QPushButton * aboutButton;
	QPushButton * aboutQtButton;
	QPushButton * customButton;
	QGridLayout * layout;
public:
	inline MessageBox();
private slots:
	inline void slotQuestion();
	inline void slotInformation();
	inline void slotAboutQt();
	inline void slotCustom();
};

MessageBox::MessageBox()
{
	questionButton		= new QPushButton("Question");
	informationButton	= new QPushButton("Information");
	warningButton		= new QPushButton("Warning");
	criticalButton		= new QPushButton("Critical");
	aboutButton			= new QPushButton("About");
	aboutQtButton		= new QPushButton("AboutQt");
	customButton		= new QPushButton("Custom");
	layout				= new QGridLayout(this);

	layout->addWidget(questionButton, 0, 0);
	layout->addWidget(informationButton, 0, 1);
	layout->addWidget(warningButton, 1, 0);
	layout->addWidget(criticalButton, 1, 1);
	layout->addWidget(aboutButton, 2, 0);
	layout->addWidget(aboutQtButton, 2, 1);
	layout->addWidget(customButton, 3, 0);

	connect(questionButton, SIGNAL(clicked()), this, SLOT(slotQuestion()));
	connect(informationButton, SIGNAL(clicked()), this, SLOT(slotInformation()));
	connect(aboutQtButton, SIGNAL(clicked()), this, SLOT(slotAboutQt()));
	connect(customButton, SIGNAL(clicked()), this, SLOT(slotCustom()));
}

void MessageBox::slotQuestion()
{
	auto okOrCancel = QMessageBox::question(
		this,		// 父窗口
		"Question",	// 标题栏
		tr("It's end of document, search from begin?"),	// 提示文字
		QMessageBox::Ok | QMessageBox::Cancel,			// 消息框中出现的按钮, 默认是QMessageBox::Ok
		QMessageBox::Ok);	// 消息框出现的时候, 焦点在Ok按钮上
}

void MessageBox::slotInformation()
{
	QMessageBox::information(this, "Information", tr("anything you want tell user"));
	return;
}

void MessageBox::slotAboutQt()
{
	QMessageBox::aboutQt(this, "AboutQt");
}

void MessageBox::slotCustom()
{
	QMessageBox customMsgBox;
	customMsgBox.setWindowTitle("Custom Message Box");
	QPushButton * lockButton	= customMsgBox.addButton(tr("Lock"), QMessageBox::ActionRole/*按钮类型的描述*/);
	QPushButton * unlockButton  = customMsgBox.addButton(tr("Unlock"), QMessageBox::ActionRole);
	QPushButton * cancelButton	= customMsgBox.addButton(QMessageBox::Cancel);	// 添加一个标准按钮
	customMsgBox.setIconPixmap(QPixmap("images/panda.png"));
	customMsgBox.setText("This is a custom message box");
	customMsgBox.exec();	// 调用exec()显示此自定义消息框

	if (customMsgBox.clickedButton() == lockButton);	// ...如果lock被点击了
}

#endif