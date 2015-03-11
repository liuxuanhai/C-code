#include <QtGui>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include "P010 FindDialog.h"

FindDialog::FindDialog(QWidget * parent) : QDialog(parent)
{
	label = new QLabel(tr("<font color = blue>Find &what:</font>"));	// tr()函数调用是把他们翻译成其他语言的标记, 在每个QObject对象以及包含有Q_OBJECT宏的子类中都有这个函数的声明
	lineEdit = new QLineEdit;	// 本来应该将主窗口传递给他们的构造函数, 以说明这两个窗口部件的父对象都是这个窗口, 但是这里没有必要, 因为布局系统将会自行得出这一结果并为其设置正确的父对象
	label->setBuddy(lineEdit);	// 设置行编译器作为标签的伙伴, 伙伴(buddy)就是一个窗口部件, 他可以在按下标签的快捷键时接收焦点, 所以, 当用户按下ALt + W的时候, 焦点就会移动到这个行编译器(该标签的伙伴)上
								// 如果没有设置的话, 那么Find &what显示出"&"符号来

	caseCheckBox = new QCheckBox(tr("Match &case"));	// "&"用来表示快捷键, 这里用户可以使用Alt + C快捷键来激活它, &可以用来控制焦点
	backwardCheckBox = new QCheckBox(tr("Search &backword"));

	findButton = new QPushButton(tr("&Find"));
	findButton->setDefault(true);	// 让Find按钮成为对话框的默认按钮
	findButton->setEnabled(false);	// 禁用Find按钮, 当禁用一个窗口部件的时候, 它通常会显示为灰色

	closeButton = new QPushButton(tr("Close"));

	// 将用户的动作与一段代码连接起来
	// Qt的窗口部件通过发射信号来表明一个用户动作已经发生或者是一个状态已经改变了
	// 如果信号的参数比他所连接的槽的参数多, 那么多余的参数将会被忽略掉
	// 参数类型不匹配, 信号或者槽不存在, 信号和槽的名字中包含了参数名, Qt都不能正常连接两个对象
	connect(lineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(enableFindButton(const QString &)));	// 只要编译器中的文本发生变化, 就会调用私有槽enableFindButton(const QString &)
	connect(findButton, SIGNAL(clicked()), this, SLOT(findClicked()));	// 当用户单击Find按钮时, 会调用findClicked()私有槽
	connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));		// 当用户单击Close时, 对话框会关闭, close()槽是从QWidget中继承而来的, 并且他的默认行为就是把窗口部件从用户的视野中隐藏起来(而无需将其删除);
																		// 由于QObject是FindDialog的父对象之一, 所以可以省略connect()函数前面的QObject::前缀
	QHBoxLayout * topLeftLayout = new QHBoxLayout;
	topLeftLayout->addWidget(label);
	topLeftLayout->addWidget(lineEdit);

	QVBoxLayout * leftLayout = new QVBoxLayout;
	leftLayout->addLayout(topLeftLayout);
	leftLayout->addWidget(caseCheckBox);
	leftLayout->addWidget(backwardCheckBox);

	QVBoxLayout * rightLayout = new QVBoxLayout;
	rightLayout->addWidget(findButton);
	rightLayout->addWidget(closeButton);
	rightLayout->addStretch();	// 生成分隔符("伸展器"), 用它来占据Find按钮和Close按钮所余下的空白区域, 这样可以确保这些按钮完全占用在他们所在布局的上部空间

	QHBoxLayout * mainLayout = new QHBoxLayout;
	mainLayout->addLayout(leftLayout);	// 当将子布局对象添加到父布局对象中时, 子布局对象会自动重定义自己的父对象
	mainLayout->addLayout(rightLayout);
	setLayout(mainLayout);	// 在窗口上安装布局控制器	从软件的底层实现上来看, 安装了布局的窗口部件会自动成为布局内的部件的父对象, 正是基于这种原因, 当创建一个需要放进某个布局中的窗口部件的时候, 就没有必要为其显示指定父对象了

	setWindowTitle(tr("Find"));	// 设置标题内容
	setFixedHeight(sizeHint().height());	// 让窗口具有一个固定的高度, QWidget::sizeHint()函数可以返回一个窗口部件所理想的尺寸的大小
}

// 对话框中所用到的槽
void FindDialog::findClicked()	// 当用户单击Find按钮的时候, 就会调用findClicked()槽, 该槽将会发射findPrevious()或者findNext()信号;
{
	QString text = lineEdit->text();
	Qt::CaseSensitivity cs = caseCheckBox->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive;
	if (backwardCheckBox->isChecked())
	{
		emit findPrevious(text, cs);	// emit(发出)是Qt中得关键字, 像其他Qt扩展一样, 他也会被C++预处理器转换成标准的C++代码
	}
	else
	{
		emit findNext(text, cs);
	}
}

void FindDialog::enableFindButton(const QString & text)	// 只要用户改变了行编辑器中的文本, 就会调用enableFindButton()槽, 如果在行编译器中有文本, 该槽就会启用Find按钮, 否则他就会禁用Find按钮
{
	findButton->setEnabled(!text.isEmpty());	// enable	使能, 激活		这里是说如果没有文本, 就不激活, 否则激活Find按钮
}