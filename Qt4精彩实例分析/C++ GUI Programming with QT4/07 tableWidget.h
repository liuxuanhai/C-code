// 创建: 2014-08-28 14:36:55
// QTableWidget可以嵌入编辑框或显示控件, 表格可以插入控件, 显示文本
#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H
#include <QTableWidget>
#include <QLabel>
#include <QDateTimeEdit>
#include <QComboBox>
#include <QSpinBox>

class TableWidget: public QTableWidget
{
private:
	QLabel				* LabelPixmap1;
	QTableWidgetItem	* TableWidgetItem1;
	QDateTimeEdit		* DateTimeEdit1;
public:
	TableWidget(QWidget * parent = nullptr);
};

TableWidget::TableWidget(QWidget * parent): QTableWidget(parent)
{
	setWindowTitle("07 The use of QTableWidget");

	// 设置表格的Cell数量
	setRowCount(5);
	setColumnCount(5);

	// 给表格加入图片 
	LabelPixmap1 = new QLabel();
	LabelPixmap1->setPixmap(QPixmap("images/panda.png"));	// 给Label加上图片
	setCellWidget(1, 0, LabelPixmap1);						// 将Label放入Cell

	// 给表格加入文本
	TableWidgetItem1 = new QTableWidgetItem(tr("Tom"));		// 给QTableWidgetItem加入文本
	setItem(1, 1, TableWidgetItem1);						// 将Item加入Cell	// 注意: 这里是setItem
	
	// 添加弹出日历控件
	DateTimeEdit1 = new QDateTimeEdit();
	DateTimeEdit1->setDateTime(QDateTime::currentDateTime());	// 设置默认显示
	DateTimeEdit1->setDisplayFormat("dd/M/yyyy");				// 设置显示格式
	DateTimeEdit1->setCalendarPopup(true);	// popup 弹出 calendar 日历
	setCellWidget(1, 2, DateTimeEdit1);		// 添加控件
	
	// 添加一个组合选择框
	QComboBox * ComboBoxWork1 = new QComboBox();
	ComboBoxWork1->addItem(tr("Worker"));
	ComboBoxWork1->addItem(tr("Farmer"));
	ComboBoxWork1->addItem(tr("Docter"));
	ComboBoxWork1->addItem(tr("Lawyer"));
	ComboBoxWork1->addItem(tr("Soldier"));
	setCellWidget(1, 3, ComboBoxWork1);

	QSpinBox * SpiBoxIncome1 = new QSpinBox();
	SpiBoxIncome1->setRange(1000, 10000);
	setCellWidget(1, 4, SpiBoxIncome1);
}
#endif