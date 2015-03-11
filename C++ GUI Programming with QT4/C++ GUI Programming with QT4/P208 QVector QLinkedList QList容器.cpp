#include <QApplication>
#include <QVector>
#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <vector>
#include <QLinkedList>

class MyWidget : public QWidget
{
private:
	QVector<int>		v;
	std::vector<int>	stdv;
	QLinkedList<QString>linkedList;
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
	v.resize(2);
	//v[0] = 0;		// resize()在分配元素内存的同时调用default构造函数初始化
	v.append(2);	// push_back(T);
	v.back() = 2;
	v[1]	 = 1;
	v << 3;

	stdv.resize(3);
	stdv.at(1) = 1;	// QVector不允许这样赋值
	//stdv << 3;	// 标准vector不允许这么做
	stdv.push_back(3);

	linkedList.append("Clash");
	linkedList.push_back("Ramones");
	QLinkedList<QString>::iterator i = linkedList.begin();
	linkedList.insert(i, "Tote Hosen");
}

void MyWidget::paintEvent(QPaintEvent * e)
{
	QPainter P(this);
	int j = 0;
	// STL风格的迭代器 -- 可以结合算法
	for (QVector<int>::const_iterator i = v.begin(); i < v.end(); ++i,++j)	// 常量迭代器
	{
		P.drawText(20, 20 * j, 100, 20, Qt::AlignLeft | Qt::AlignVCenter, QString::number(*i));
		P.drawText(50, 20 * j, 100, 20, Qt::AlignLeft | Qt::AlignVCenter, QString::number(stdv.at(j)));
	}
	j = 0;
	for (QLinkedList<QString>::iterator i = linkedList.begin(); /*j < linkedList.count()*/i != linkedList.end()/*i < linkedList.end()*/; ++i, ++j)
		P.drawText(80, 20 * j, 100, 20, Qt::AlignLeft | Qt::AlignVCenter, *i);
	// java风格的只读迭代器 -- 易于使用
	QLinkedListIterator<QString> i(linkedList);	// java风格的迭代器本身并不指向项, 而是能够定位在第一项之前, 最后一项之后或者是两项之间
		// java风格的迭代器在第一项之前就被定位了, 如果迭代器后边有一个项, hasNext()返回true, next()函数返回迭代器右边的项并且将迭代器提升至下一有效位置

	while (i.hasNext())
	{
		static int j = 0;
		P.drawText(160, 20 * j++, 100, 20, Qt::AlignLeft | Qt::AlignVCenter, i.next());
	}
	i.toBack();
	while (i.hasPrevious())
	{
		static int j = 0;
		P.drawText(240, 20 * j++, 100, 20, Qt::AlignLeft | Qt::AlignVCenter, i.previous());
	}
	// java风格的读写迭代器
	// 移除v中的数据项2
	QMutableVectorIterator<int> i3(v);
	while (i3.hasNext())
	{
		if (i3.next() == 2)	// 调用了一次next()以后, 迭代器自动后移了一位
			i3.remove();	// 后移以后这里正好删除数据为2的项
	}
	i3.toFront();
	while (i3.hasNext())
	{
		static int j = 0;
		P.drawText(20, 20 * j++ + 130, 100, 20, Qt::AlignLeft | Qt::AlignVCenter, QString::number(i3.next()));
	}
	// 将v中的1改成-1
	i3.toFront();
	while (i3.hasNext())
	{
		if (i3.next() == 1)
			i3.setValue(-1);
	}
	i3.toFront();
	while (i3.hasNext())
	{
		static int j = 0;
		P.drawText(20, 20 * j++ + 260, 100, 20, Qt::AlignLeft | Qt::AlignVCenter, QString::number(i3.next()));
	}

	// Qt 的循环遍历方式 -- foreach 循环
	foreach (int i, v)	// foreach 伪关键字按照标准for循环实现, 每次迭代中, 迭代变量i都被设置为一个新项, 从容器中的第一个想开始迭代;
		// foreach会在进入循环时自动复制!一个!容器, 因此即使在容器过程中修改了容器类, 也不会影响到循环
	{
		static int j = 0;
		P.drawText(20, 20 * j++ + 390, 100, 20, Qt::AlignLeft | Qt::AlignVCenter, QString::number(i));
	}
}
