#include "P073 Cell.h"
Cell::Cell()
{
	setDirty();	// 将缓存设置为dirty
		// 这里没有必要传递父对象, 因为setItem()把单元格插入到一个QTableWidget中的时候, QTableWidget将会自动对齐拥有所有权
}

QTableWidgetItem * Cell::clone() const	// 当QTableWidget需要创建一个新的单元格的时候, 例如, 当用户在一个以前没有使用过的空白单元格中开始输入数据时, 他就会调用clone()函数 传递给QTableWidget::setItemPrototype()中的实例就是需要克隆的项, 但是对于Cell来讲, 成员级的复制已经足以满足需要, 所以这里只需要依靠C++自动创建的默认复制构造函数就可以创建新的Cell实例了
{
	return new Cell(*this);
}

void Cell::setFormula(const QString & formula)	// 设置单元格中的公式
{
	setData(Qt::EditRole, formula);	// Qt::EditRole 编辑角色用在哪些需要编辑的数据上, Qt::DisplayRole 显示数据用在哪些需要显示的数据上 通常情况下两者的数据都是一样的, 但是在Cell类中, 编辑角色对应于单元格的公式, 显示角色对应于单元格的值(对公式求值后的结果);
}

QString Cell::formula() const	// 重新获得该项的EditRole数据
{
	return data(Qt::EditRole).toString();
}

void Cell::setData(int role, const QVariant & value)	// 如果有新的公式, 就可以把cacheIsDirty设置为true, 以确保在下一次调用text()的时候可以重新计算该单元格 尽管对Cell实例中的Spreadsheet::text()调用了text(), 但是在Cell中没有定义text()函数, 这个text()函数是一个由QTableWidgetItem提供的简便函数相当于调用data(Qt::DisplayRole).toString()
{
	QTableWidgetItem::setData(role, value);
	if (role == Qt::EditRole)
		setDirty();
}

void Cell::setDirty()	// 对单元格的值强制进行重新计算
{
	cacheIsDirty = true;	// 简单的把cacheIsDirty设置为true, 这就意味着cachedValue不再是最新值, 除非有必要, 否则不会执行重新计算操作
}

QVariant Cell::data(int role) const
{
	if (role == Qt::DisplayRole)	// 使用Qt::DisplayRole调用这个函数, 返回电子制表软件中应该显示的文本
	{		// Cell::value()返回一个QVariant值, QVariant可以存储不同类型的值, 比如double和QString, 并且提供了一些吧变量转换为其他类型变量的一些函数 例如对一个保存了double值得变量调用toString()可以产生一个表示这个double值得字符串 使用默认构造函数创建的QVariant是一个"无效"变量
		if (value().isValid())	// 使用value()计算单元格的值, 如果值是无效的返回"####"
			return value().toString();
		else
			return "####";
	} else if (role == Qt::TextAlignmentRole)	// 如果使用Qt::TextAlignmentRole调用这个函数, 返回一个合适的对齐方式
	{
		if (value().type() == QVariant::String)
			return int(Qt::AlignLeft | Qt::AlignVCenter);
		else
			return int(Qt::AlignRight | Qt::AlignVCenter);
	}
	else	// 如果使用Qt::EditRole调用这个函数, 返回单元格中的公式
		return QTableWidgetItem::data(role);
}

const QVariant Invalid;
QVariant Cell::value() const	// 返回单元格的值, 如果cacheIsDirty是true, 就需要重新计算这个值
{
	if (cacheIsDirty)
	{
		cacheIsDirty = false;

		QString formulaStr = formula();
		if (formulaStr.startsWith('\''))	// 由单引号开始的公式那么单引号占用位置0, 值是从位置1直到最后 位置的一个字符串
			cachedValue = formulaStr.mid(1);
		else if (formulaStr.startsWith('='))// 公式由等号开始, 那么会使用从位置1开始的字符串, 并且将它可能包含的任意空格全部移除
		{
			cachedValue = Invalid;
			QString expr = formulaStr.mid(1);
			expr.replace(" ", "");
			expr.append(QChar::Null);

			int pos = 0;
			cachedValue = evalExpression(expr, pos);	// 计算表达式的值	pos是引用传递, 用来说明需要从哪里开始解析字符的位置
			if (expr[pos] != QChar::Null)	// 调用evalExpression()之后, 如果表达式 解析成功, 那么在位置pos处的字符应当是QChar::Null字符
				cachedValue = Invalid;	// 解析失败这样做
		} else
		{
			bool ok;
			double d = formulaStr.toDouble(&ok);	// 如果公式不是有单引号或者等号开始的, 使用toDouble()试着把它转换为浮点数
			if (ok)	// 转换正常, cachedValue设置成结果数字
				cachedValue = d;
			else	// 转换不正常, 把cachedValue设置为字符串公式 例如, 公式"1.50"会导致toDouble()把ok设置成true, 返回1.5, 公式"Wold"导致ok为false, 返回0.0
				cachedValue = formulaStr;
		}
	}
	return cachedValue;
}

QVariant Cell::evalExpression(const QString & str, int & pos) const
{
	QVariant result = evalTerm(str, pos);
	while (str[pos] != QChar::Null)
	{
		QChar op = str[pos];
		if (op != '+' && op != '-')
			return result;
		++pos;
		
		QVariant term = evalTerm(str, pos);
		if (result.type() == QVariant::Double && term.type() == QVariant::Double)
		{
			if (op == '+')
				result = result.toDouble() + term.toDouble();
			else
				result = result.toDouble() - term.toDouble();
		} else
			result = Invalid;
	}
	return result;
}

QVariant Cell::evalTerm(const QString & str, int & pos) const
{
	QVariant result = evalFactor(str, pos);
	while (str[pos] != QChar::Null)
	{
		QChar op = str[pos];
		if (op != '*' && op != '/')
			return result;
		++pos;

		QVariant factor = evalFactor(str, pos);
		if (result.type() == QVariant::Double && factor.type() == QVariant::Double)
		{
			if (op == '*')
				result = result.toDouble() * factor.toDouble();
			else
			{
				if (factor.toDouble() == 0.0)
					result = Invalid;
				else
					result = result.toDouble() / factor.toDouble();
			}
		} 
		else
		{
			result = Invalid;
		}
	}
	return result;
}

QVariant Cell::evalFactor(const QString & str, int & pos) const
{
	QVariant result;
	bool negative = false;

	if (str[pos] == '-')
	{
		negative = true;
		++pos;
	}
	if (str[pos] == '(')
	{
		++pos;
		result = evalExpression(str, pos);
		if (str[pos] != ')')
			result = Invalid;
		++pos;
	}
	else
	{
		QRegExp regExp("[A-Za-z][1-9][0-9]{0,2}");
		QString token;

		while (str[pos].isLetterOrNumber() || str[pos] == '.')
		{
			token += str[pos];
			++pos;
		}
		if (regExp.exactMatch(token))
		{
			int column = token[0].toUpper().unicode() - 'A';
			int row = token.mid(1).toInt() - 1;

			Cell * c = static_cast<Cell *>(tableWidget()->item(row, column));
			if (c)
				result = c->value();
			else
				result = 0.0;
		}
		else
		{
			bool ok;
			result = token.toDouble(&ok);
			if (!ok)
				result = Invalid;
		}
	}
	if (negative)
	{
		if (result.type() == QVariant::Double)
			result = -result.toDouble();
		else
			result = Invalid;
	}
	return result;
}