#include "P073 Cell.h"
#include "P060 Spreadsheet.h"

Spreadsheet::Spreadsheet(QWidget * parent) : QTableWidget(parent)
{
	autoRecalc = true;
	setItemPrototype(new Cell);	// 通常情况下, 用户在单元格输入一些文本的时候, QTableWidget将会自动创建一个QTableWidgetItem来保存这些文件, 我们想用Cell项代替QTableWidgetItem, 这可以通过在构造函数中调用setItemPrototype()来完成, 实际上QTableWidget会在每次需要新项的时候把传递的项以原型的形式克隆出来
	setSelectionMode(ContiguousSelection);	// 允许简单矩形选择框方法
	
	connect(this, SIGNAL(itemChanged(QTableWidgetItem *)), this, SLOT(somethingChanged()));
					// itemChanged是QTableWidget中的信号

	clear();	// 重新调整表格的尺寸大小并且设置列表题
}

void Spreadsheet::clear()
{
	setRowCount(0);
	setColumnCount(0);
	setRowCount(RowCount);
	setColumnCount(ColumnCount);

	for (int i = 0; i < ColumnCount; ++i)
	{
		QTableWidgetItem * item = new QTableWidgetItem;
		item->setText(QString(QChar('A' + i)));
		setHorizontalHeaderItem(i, item);
	}
	setCurrentCell(0, 0);
}

Cell * Spreadsheet::cell(int row, int column) const	// 根据指定的行和列返回一个Cell对象 他几乎和QTableWidget::item()函数一样, 只不过它返回一个Cell指针而不是一个QTableWidgetItem指针
{
	return static_cast<Cell *>(item(row, column));
}

QString Spreadsheet::text(int row, int column) const	// 返回给定单元格中的文本
{
	Cell * c = cell(row, column);
	if (c)
		return c->text();
	else
		return "";
}

QString Spreadsheet::formula(int row, int column) const
{
	Cell * c = cell(row, column);
	if (c)
		return c->formula();
	else
		return "";
}

void Spreadsheet::setFormula(int row, int column, const QString & formula)	// 设置用于给定单元格的公式
{
	Cell * c = cell(row, column);
	if (!c)	// 如果该单元格已经有了一个Cell对象, 那么直接使用它, 否则创建一个新的Cell对象并且调用QTableWidget::setItem()把它插入到表中
	{
		c = new Cell;
		setItem(row, column, c);
	}
	c->setFormula(formula);	// 调用单元格自己的setFormula()函数
}

QString Spreadsheet::currentLocation() const	// 返回当前单元格的位置
{
	return QChar('A' + currentColumn()) + QString::number(currentRow() + 1);
}

QString Spreadsheet::currentFormula() const	// 返回当前单元格公式
{
	return formula(currentRow(), currentColumn());
}

void Spreadsheet::somethingChanged()
{
	if (autoRecalc)	// 如果启用了"Auto-Recalculate"(自动重新计算), 那么somethingChanged()私有槽就会重新计算整个电子制表软件
		recalculate();
	emit modified();
}

#include <QFile>
#include <QMessageBox>
#include <QApplication>
bool Spreadsheet::writeFile(const QString & fileName)
{
	QFile file(fileName);	// 使用给定的文件名创建一个QFile对象
	if (!file.open(QIODevice::WriteOnly))	// 使用open()打开这个用于输出的文件
	{
		QMessageBox::warning(this, tr("Spreadsheet"), 
			tr("Cannot write file %1:\n%2")
			.arg(file.fileName()
			.arg(file.errorString())));
		return false;
	}
	QDataStream out(&file);	// 创建一个QDataStream对象, 由它操作file并且使用该对象输出数据	
							// QDataStream既可以支持C++基本类型, 也可以支持多种Qt类型, 该语法模仿了标准C++的<iostream>中的语法
	out.setVersion(QDataStream::Qt_4_3);	// 使用的是第九版二进制表示方法

	out << quint32(MagicNumber);	// 因为C++的基本类型在不同平台上可能会有不同大小, 这里把这些变量强制转换成了固定大小
		// Spreadsheet应用程序的文件格式以一个32位数字(MagicNumber, 0x7F51c883他是一个随机值)作为文件的开始, 由它确定文件的格式
		// 然后是连续的数据块, 每一个数据块都包含了用于一个单元格中的行, 列和公式
		// 这些数据的确切二进制表示方法由QDataStream决定

	QApplication::setOverrideCursor(Qt::WaitCursor);	// 输出数据之前, 把应用程序的光标改成等待光标
	for (int row = 0; row <RowCount; ++row)
	{
		for (int column = 0; column < ColumnCount; ++column)
		{
			QString str = formula(row, column);
			if (!str.isEmpty())
			{
				out << quint16(row) << quint16(column) << str;
			}
		}
	}
	QApplication::restoreOverrideCursor();	// 所有数据输出完毕, 恢复普通光标
	return true;	// 函数最后, 文件由QFile对象的析构函数自动关闭
}

bool Spreadsheet::readFile(const QString & fileName)
{
	QFile file(fileName);	// 读取一个文件
	if (!file.open(QIODevice::ReadOnly))	// 只读打开文件
	{
		QMessageBox::warning(this, tr("Spreadsheet"),
			tr("Cannot read file %1:\n%2.")
			.arg(file.fileName())
			.arg(file.errorString()));
		return false;
	}
	QDataStream in(&file);
	in.setVersion(QDataStream::Qt_4_3);

	quint32 magic;
	in >> magic;
	if (magic != MagicNumber)
	{
		QMessageBox::warning(this, tr("Spreadsheet"),
			tr("The file is not a Spreadsheet file."));
		return false;
	}
	clear();

	quint16 row;
	quint16 column;
	QString str;

	QApplication::setOverrideCursor(Qt::WaitCursor);
	while (!in.atEnd())
	{
		in >> row >> column >> str;
		setFormula(row, column, str);
	}
	QApplication::restoreOverrideCursor();
	return true;
}