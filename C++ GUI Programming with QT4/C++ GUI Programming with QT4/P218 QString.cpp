#include <QApplication>
#include <QPainter>
#include <QString>
#include <QWidget>
#include <QPaintEvent>

class MyWidget : public QWidget
{
private:
	QString str;
public:
	MyWidget(QWidget * parent = nullptr);
protected:
	void paintEvent(QPaintEvent *);
};

int main(int argc, char ** argv)
{
	QApplication App(argc, argv);
	MyWidget M;

	M.show();
	App.exec();
}

MyWidget::MyWidget(QWidget * parent) : QWidget(parent)
{
	
}

void MyWidget::paintEvent(QPaintEvent *)
{
	QPainter P(this);
	str.append("0");// 尾部添加一个"0"
	str.append(1);	// 好像什么效果都没有
	str.append("1");
	str.setNum(2);	// 把原来的所有都覆盖了
	str += "3";

	str.sprintf("%s%d%ld", "4", 5, 6);	// 与C++库sprintf函数相同的格式说明符
	str += QString("%1%3%5").arg(7).arg("8").arg('9');	// arg()的重载函数可以处理各种数据类型
		// 相比较sprintf, arg通常是一个更好的解决方案, 因为他是类型安全的, 完全支持Unicode编码, 并且允许译码器堆%n参数进行重新排序

	str += QString::number(10);	// 通过使用QString::number()静态函数, 将数字转换为字符串
	
	bool isTo;	// 将字符串转换成数字
	int n = str.toInt(&isTo);
	if (isTo)
		P.drawText(200, 20, 100, 20, Qt::AlignLeft | Qt::AlignVCenter, QString::number(n));
	str += "pp";
	n = str.toInt(&isTo);
	if (!isTo)	// 转换失败, n值改为0
		P.drawText(200, 40, 100, 20, Qt::AlignLeft | Qt::AlignVCenter, QString::number(n));

	P.drawText(20, 20, 100, 20, Qt::AlignLeft | Qt::AlignVCenter, str);
	for (QString::const_iterator i = str.begin(); i != str.end(); ++i)
	{
		static int j = 0;
		P.drawText(300, 20 * ++j, 100, 20, Qt::AlignLeft | Qt::AlignVCenter, *i);
	}
		
		// 获取字符串特定位置的子串

	str += str.mid(0, 2);	// mid(int1, int2)  函数返回int1是开始位置, int2是子串的长度
	P.drawText(20, 40, 100, 20, Qt::AlignLeft | Qt::AlignVCenter, str);
	str += str.mid(0);		// 如果省略第二个参数, mid()函数返回在给定位置开始到字符串末端结束的子串
	P.drawText(20, 60, 200, 20, Qt::AlignLeft | Qt::AlignVCenter, str);
	
	P.drawText(40, 80, 200, 20, Qt::AlignLeft | Qt::AlignVCenter, str.left(2) + str.right(4));	// left(n) 返回钱n个字符作为子串, right(n) 返回最后n个字符作为子串

		// 查找子串

	int index = str.indexOf("pp");	// 返回出现"pp"的位置
	if (index != -1)				// 如果"pp"不存在, 返回-1
		P.drawText(40, 100, 200, 20, Qt::AlignLeft | Qt::AlignVCenter, str.mid(index));
	int index2 = str.indexOf("pp", index + 2);	// 第二个参数设置了开始查找的位置
	P.drawText(40, 120, 200, 20, Qt::AlignLeft | Qt::AlignVCenter, str.mid(index2));
	// startsWith() endsWith() 检查字符串是否以某个字符串开始或者结束

		// 字符串替换

	str.replace(1, 3, "k");	// 把区间1是开始的位置, 3是一共要替换的元素个数
	P.drawText(20, 140, 200, 20, Qt::AlignLeft | Qt::AlignVCenter, str);
	// 将str中所有的"pp"替换成"hhh"
	str.replace("pp", "hhh");
	P.drawText(20, 160, 200, 20, Qt::AlignLeft | Qt::AlignVCenter, str);
	// 删除位置2开始的长度为3的字符串
	str.remove(2, 3);
	P.drawText(20, 180, 200, 20, Qt::AlignLeft | Qt::AlignVCenter, str);
	// 在第一个0前面添加fc
	str.insert(2, "fc");
	P.drawText(20, 200, 200, 20, Qt::AlignLeft | Qt::AlignVCenter, str);
	// 删除两边的空格(eg: 空格符, 制表符, 换行符...)str.trimmed();
	// 将连续的空格改成一个空格符str.simpliefied()
	// QString::split()把一个字符串分成QStringList子串
		// QString str = "da xiong ge ge";
		// QStrngList words = str.split(" ");

	// 将QString转换为const char *
		// str.toAscii()或者str.toLatin1()函数, 他们返回QByteArray, 利用QBateArray::data()或QByteArray::constData(), 将QByteArray转换成const char *
		// eg: printf("User: %s\n", str.toAscill().data());
		// 或者使用宏qPrintable执行与toAscii().constData()相同的功能
	// QByteArray语意形式与在QString中的相同, 他对于存储原始的二进制数据以及8位编码的文本字符串非常有用 , 为了方便, QByteArray自动保证"最后一个项之后的项"总为"\0"
}