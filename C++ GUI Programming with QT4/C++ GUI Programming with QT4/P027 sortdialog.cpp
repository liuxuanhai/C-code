//#include <QtGui>
#include "P027 sortdialog.h"
SortDialog::SortDialog(QWidget * parent) : QDialog(parent)
{
	setupUi(this);	// 初始化窗体

	secondaryGroupBox->hide();	// 隐藏高级选项
	tertiaryGroupBox->hide();
	layout()->setSizeConstraint(QLayout::SetFixedSize);	// 固定对话框的大小 constraint 约束 fixed 固定的
		// 这样一来, 布局就会负责重定义对话框大小的职责, 并且会在显示或者隐藏窗口部件的时候自动重定义这个对话框的大小

	SetColumnRange('A', 'Z');	// 这个槽根据电子制表软件中选择的列初始化组合框内容
}

void SortDialog::SetColumnRange(QChar first, QChar last)
{
	primaryColumnCombo->clear();
	secondaryColumnCombo->clear();
	tertiaryColumnCombo->clear();

	secondaryColumnCombo->addItem(tr("None"));
	tertiaryColumnCombo->addItem(tr("None"));
	primaryColumnCombo->setMinimumSize(secondaryColumnCombo->sizeHint());	// sizeHint()函数返回布局系统试图认同的"理想"大小

	QChar ch = first;
	while (ch <= last)
	{
		primaryColumnCombo->addItem(QString(ch));
		secondaryColumnCombo->addItem(QString(ch));
		tertiaryColumnCombo->addItem(QString(ch));
		ch = ch.unicode() + 1;
	}
}