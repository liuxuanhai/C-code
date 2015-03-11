#ifndef CELL_H
#define CELL_H

#include <QTableWidgetItem>

class Cell : public QTableWidgetItem	// QTableWidgetItem不是从QObject派生而来, 不能有信号和槽
{
public:
	Cell();

	QTableWidgetItem * clone() const;
	void setData(int role, const QVariant & value);
	QVariant data(int role) const;
	void setFormula(const QString & formula);
	QString formula() const;
	void setDirty();
private:
	QVariant value() const;
	QVariant evalExpression(const QString & str, int & pos) const;
	QVariant evalTerm(const QString & str, int & pos) const;
	QVariant evalFactor(const QString & str, int & pos) const;

	mutable QVariant cachedValue;	// 把单元格的值缓冲为QVariant	之所以使用QVariant是因为有些单元格是double型值, 有些则是QString
	mutable bool cacheIsDirty;		// 如果缓冲的值不是最新的, cacheIsDirty设置为true
		// mutable 易变的 使用这个关键字使得可以在const函数中修改它
};

#endif