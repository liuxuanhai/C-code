#include <QtGui>
#include "P020 GoToCell.h"
GoToCellDialog::GoToCellDialog(QWidget * parent) : QDialog(parent)
{
	setupUi(this);	// 初始化窗体	创建了用户接口以后, setupUi()函数会自动将那些符合on_objectName_signalName()命名惯例的任意槽与相应的objectName的signalName()信号连接到一起, 这里有on_lineEdit_textChanged ↓

	QRegExp regExp("[A-Za-z][1-9][0-9]{0,2}");	// 这里设置了一个检验器来限制输入的范围: 允许一个大写或者小写的字母, 后边跟着一个范围为1-9的数字, 后边再跟0个1个或者2个0-9的数字;
												// Qt提供了三个内置的检验器类: QIntValidator, QDoubleValidator和QRegExpValidator.
	lineEdit->setValidator(new QRegExpValidator(regExp, this));	// 通过把this传递给QRegExpValidator的构造函数, 使它成为GoToCellDialog对象的一个子对象, 这样以后就不用担心有关删除QRegExpValidator的事情了, 当删除他的父对象时, 他也会自动删除
																// Qt的父-子对象机制是在QObject中实现的, 当利用一个父对象创建一个子对象(一个窗口部件, 一个检查器, 或是任意的其他类型)时, 父对象会把这个子对象添加到自己的子对象列表中, 当删除这个父对象的时候, 他会遍历子对象列表并且会删除每一个子对象, 然后, 这些子对象再去删除他们自己包含的子对象  而且对于窗口部件, 父对象还有另外一层含义: 子窗口部件会显示在他的父对象所在区域中, 当删除这个父对象部件时, 不仅子对象会从内存中消失, 而且它也会在屏幕上消失6

	connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));		// accept()关闭对话框, 将对话框返回的结果变量设置为QDialog::Accepted(其值等于1)
	connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));	// reject()关闭对话框, 返回值为QDialog::Rejected(其值为0)
}

void GoToCellDialog::on_lineEdit_textChanged()	// 这里样命名就意味着setUi()函数将会建立如下所示的信号-槽连接关系: connect(lineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(on_lineEdit_textChanged()));
{
	okButton->setEnabled(lineEdit->hasAcceptableInput());	// hasAcceptableInput()会使用在构造函数中设置的检查器来判断编译器中内容的有效性
}