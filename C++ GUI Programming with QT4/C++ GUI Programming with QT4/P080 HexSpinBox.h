// 自定义窗口部件
#ifndef HEXSPINBOX_H
#define HEXSPINBOX_H

#include <QSpinBox>

class QRegExpValidator;

class HexSpinBox : public QSpinBox
{
	Q_OBJECT;
public:
	HexSpinBox(QWidget * parent = nullptr);

protected:	// 重新实现QSpinBox中的三个虚函数
	inline QValidator::State validate(QString & text, int & pos) const;	// state 规定 声名 陈述
	inline int valueFromText(const QString & text) const;
	inline QString textFromValue(int value) const;

private:
	QRegExpValidator * validator;
};

HexSpinBox::HexSpinBox(QWidget * parent) : QSpinBox(parent)
{
	setRange(0, 255);	// 0x00 - 0xff	// 设置微调框的范围为 0 - 255
	validator = new QRegExpValidator(QRegExp("[0-9A-Fa-f]{1,8}"), this);	// 创建一个检验器, 设置父对象为this
}

QValidator::State HexSpinBox::validate(QString & text, int & pos) const
{
	return validator->validate(text, pos);
}
	// 此函数由QSpinBox调用	结果: 1. Invalid(无效) 2. Intermediate(部分有效) 3. Acceptable(可接受)

QString HexSpinBox::textFromValue(int value) const
{
	return QString::number(value, 16).toUpper();	// 把一个整数转换成一个字符串
		// 16 意味着把整数转换成小写格式的十六进制字符串
}

int HexSpinBox::valueFromText(const QString & text) const
{
	bool ok;
	return text.toInt(&ok, 16);	// 把字符串转换成整数值
		// 当用户在编译器部分输入一个值并且按下Enter时, QSpinBox就会调用它
		// 如果不是有效的十六进制数, 就把ok设置成false, 并且由toInt()返回一个0, 这里有检验器, 所以输入肯定有效
}

#endif