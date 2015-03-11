// 创建: 2014-08-26 17:05:05
// 标准输入对话框:		一个提示标签, 一个输入控件, 一个OK按钮和一个Cancel按钮
//		(1)	提供了四种类型数据的输入
//			字符串(QLineEdit)	int(QSpinBox)	double(QSpinBox)	下拉列表框(QComboBox)
#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QLayout>
#include <QLineEdit>
#include <QInputDialog>

class InputDlg: public QDialog
{
	Q_OBJECT
public:
	inline InputDlg();

public:
	QPushButton * nameButton;
	QPushButton * sexButton;
	QPushButton * ageButton;
	QPushButton * statureButton;

	QLabel * label1;
	QLabel * label2;
	QLabel * label3;
	QLabel * label4;
	QLabel * nameLabel;
	QLabel * sexLabel;
	QLabel * ageLabel;
	QLabel * statureLabel;
private slots:
	inline void slotName();
	inline void slotSex();
	inline void slotAge();
	inline void slotStature();
};

InputDlg::InputDlg()
{
	setWindowTitle(tr("InputDialog"));

	// 创建各个标签对象
	label1 = new QLabel(tr("Name: "));
	label2 = new QLabel(tr("Sex: "));
	label3 = new QLabel(tr("Age: "));
	label4 = new QLabel(tr("Stature: "));
	// 创建各个显示标签
	nameLabel = new QLabel("LiMing");
	nameLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
	sexLabel = new QLabel("male");
	sexLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
	ageLabel = new QLabel("26");
	ageLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
	statureLabel = new QLabel("175");
	statureLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
	// 创建各个修改按钮
	nameButton = new QPushButton;
	nameButton->setIcon(QIcon("images/edit.png"));
	sexButton = new QPushButton;
	sexButton->setIcon(QIcon("images/edit.png"));
	ageButton = new QPushButton;
	ageButton->setIcon(QIcon("images/edit.png"));
	statureButton = new QPushButton;
	statureButton->setIcon(QIcon("images/edit.png"));
	// 布局管理
	QGridLayout * layout = new QGridLayout(this);
	layout->addWidget(label1, 0, 0);
	layout->addWidget(nameLabel, 0, 1);
	layout->addWidget(nameButton, 0, 2);
	
	layout->addWidget(label2, 1, 0);
	layout->addWidget(sexLabel, 1, 1);
	layout->addWidget(sexButton, 1, 2);

	layout->addWidget(label3, 2, 0);
	layout->addWidget(ageLabel, 2, 1);
	layout->addWidget(ageButton, 2, 2);

	layout->addWidget(label4, 3, 0);
	layout->addWidget(statureLabel, 3, 1);
	layout->addWidget(statureButton, 3, 2);

	connect(nameButton, SIGNAL(clicked()), this, SLOT(slotName()));
	connect(sexButton, SIGNAL(clicked()), this, SLOT(slotSex()));
	connect(ageButton, SIGNAL(clicked()), this, SLOT(slotAge()));
	connect(statureButton, SIGNAL(clicked()), this, SLOT(slotStature()));
}

void InputDlg::slotName()
{
	bool ok;
	QString name = QInputDialog::getText(	// QInputDialog的标准字符串输入对话框
		this,				// 父窗口
		tr("User Name"),	// 标题
		tr("Please input new name: "),		// 提示标签显示内容
		QLineEdit::Normal,	// 指定QLineEdit控件的输入模式
		nameLabel->text(),	// QLineEdit中默认出现的文字		
		&ok);				// Ok => true, Cancel => false
	if (ok && !name.isEmpty())
		nameLabel->setText(name);
}

void InputDlg::slotSex()
{
	QStringList list;
	list << tr("male") << tr("female");
	bool ok;
	QString sex = QInputDialog::getItem(this, tr("Sex"),	// 条目选择对话框
		tr("Please select sex: "), 
		list,	// 指定QComboBox控件中显示的可选条目, 为一个QStringList对象
		0,		// 指定对话框弹出时QComboBox默认选择的条目序号
		false,	// 指定QComboBox控件中显示的文字是否可编辑
		&ok);
	if (ok)
		sexLabel->setText(sex);
}

void InputDlg::slotAge()
{
	bool ok;
	int age = QInputDialog::getInt(this, tr("UerAge"), 
		tr("Please input age: "), 
		ageLabel->text().toInt(),	// 指定QSpinBox控件的默认显示值
		0,		// 指定QSpinBox控件的最小值
		150,	// 最大值
		1,		// 步进值
		&ok
		//WindowFlags f = 0		// 指明标准输入对话框的窗体标识
		);
	if (ok)
		ageLabel->setText(QString(tr("%1")).arg(age));
}

void InputDlg::slotStature()
{
	bool ok;
	double d = QInputDialog::getDouble(this, tr("Stature"), 
		tr("Please input stature: "), 175.00,/*默认*/ 0, 230.00/*范围*/, 1.5/*步进值*/, &ok);
	if (ok)
		statureLabel->setText(QString(tr("%1")).arg(d));
}

#endif