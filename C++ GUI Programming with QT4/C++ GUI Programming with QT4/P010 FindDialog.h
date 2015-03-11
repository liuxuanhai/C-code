// 本来在这个头文件中简单的添加一个<QtGui>包含就行了, 这样就省去了包含<QDialog>和使用前置声明的麻烦, 但是, 在一个头文件中再包含一个那么大的头文件着实不是一种好的编程风格, 尤其对于比较大的工程项目更是如此
#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>	// 包含了QDialog的声明

// 前置声明一些用于这个对话框实现中的Qt类(前置声明会告诉C++编译程序类的存在, 而不用提供类声明的具体细节(通常放在他自己的头文件中))
class QCheckBox;
class QLabel;
class QLineEdit;
class QPushButton;

// 声明FindDialog, 并让它成为QDialog的子类
class FindDialog : public QDialog
{
	Q_OBJECT;	// 对于所有定义了信号和槽的类, 在类的开始处的Q_OBJECT宏都是必需的;
				// 由于类的声明包含了Q_OBJECT宏, 因而由qmake生成的makefile会自动包含一些运行moc的规则, moc是Qt的元对象编译器
				// 为了使moc能够正常运行, 必须把类声明从实现文件中分离出来, 并放到头文件中, 由moc生成的代码会包含这个头文件, 并且会添加一些特殊的C++代码
public:
	FindDialog(QWidget * parent = nullptr);	// 一个典型的Qt窗口部件的类构造函数声明, 默认该对话框没有父窗口
signals:	// 本部分声明了当用户单击Find按钮时对话框所发射的两个信号;
			// singnals实际上是一个宏, C++预处理器会在编译程序找到它之前把它转化成标准C++代码
	void findNext	 (const QString & str, Qt::CaseSensitivity cs);	// Qt::CaseSensitivity是一个枚举类型, 他有Qt::CaseSensitive和Qt::CaseInsensitive两个取值
	void findPrevious(const QString & str, Qt::CaseSensitivity cs);
private slots:	// 声明两个槽
				// slots是一个宏, 也可以扩展成C++编译程序可以处理的一种结构形式
	void findClicked();
	void enableFindButton(const QString & text);	// 这里传进text是为了判断此时LineEdit中的文本是空的还是非空的以用来控制Find按钮是否禁用
private:	// 这里使用前置类型声明是可行的, 因为他们都是指针, 而且没有必要在头文件中就去访问他们, 因而编译器就无需这些类的完整定义, 所以也不用包含这几个类的相关头文件(如<QCheckBox>, <QLabel>等等), 而是使用了一些前置声明, 这可以使得编译过程更快些
	QLabel		* label;
	QLineEdit	* lineEdit;
	QCheckBox	* caseCheckBox;
	QCheckBox	* backwardCheckBox;
	QPushButton	* findButton;
	QPushButton * closeButton;
};

#endif