#ifndef P060_SPREADSHEET_H
#define P060_SPREADSHEET_H

#include <QTableWidget>	// QTableWidget是一组格子, 可以有效表达二维数组, 用户在空单元格内输入的文本的时候, QTableWidget会自动创建一个用来存储这些文本的QTableWidgetItem
						// QTableWidget单元格的属性, 比如文本和文本对齐方式, 都存储在QTableWidgetItem中
						// QTableWidgetItem不同于QTableWidget, 它不是一个窗口部件, 而是一个纯粹的数据类
class Cell;	// 派生自QTableWidgetItem
class SpreadsheetCompare;

class Spreadsheet : public QTableWidget
{
	Q_OBJECT;

private:
	bool autoRecalc;	// 是否重新计算标识符

public:
	Spreadsheet(QWidget * parent = nullptr);

	bool autoRecalculate() const { return autoRecalc; } // 返回重新计算标识符的状态
	QString currentLocation() const;	// 返回当前单元格位置
	QString currentFormula() const;		// 返回当前单元格公式
	QTableWidgetSelectionRange selectedRange() const;
	void clear();
	bool readFile(const QString & fileName);
	bool writeFile(const QString & fileName);
	void sort(const SpreadsheetCompare & compare);

public slots:
	void cut(){};
	void copy(){};
	void paste(){};
	void del(){};
	void selectCurrentRow(){};
	void selectCurrentColumn(){};
	void recalculate(){};
	void setAutoRecalculate(bool recalc){};
	void findNext(const QString & str, Qt::CaseSensitivity cs){};

signals:
	void modified();	// 当用户在单元格写入东西的时候就会发射这个信号
private slots:
	void somethingChanged();	// 用户在单元格写入东西, Spreadsheet发射QTableWidget::itemChanged(QTableWidgetItem *), 然后Spreadsheet::somethingChanged()接收到
								// somethingChanged()在autoRecalc == true的时候自动计算公式的值, 然后发射Spreadsheet::modified()槽

private:
	enum { MagicNumber = 0x7F51C883, RowCount = 999, ColumnCount = 26 };

	Cell * cell(int row, int  column) const;
	QString text(int row, int column) const;	// 返回给定单元格中的文本
	QString formula(int row, int column) const;	// formula 公式
	void setFormula(int row, int column, const QString & formula);
};

#endif