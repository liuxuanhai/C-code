// 定时器事件是一种低级事件, 而且如果需要多个定时器, 保持对所有定时器的跟踪将会变得很麻烦, 这种情况下, 通常更为简单的方式是为每一个定时器分别创建一个QTimer对象, QTimer会在每一个时间间隔发射timerout()信号, QTimer也提供了一个非常方便的接口, 可用于单触发定时器(只触发一次的定时器), 就像第六章(P122)中看到的那样
#ifndef TICKER_H
#define TICKER_H

#include <QWidget>
#include <QPainter>
#include <QEvent>

class Ticker : public QWidget
{
	Q_OBJECT;
	//Q_PROPERTY(QString text READ text WRITE setText);

public:
	inline Ticker(QWidget * parent = nullptr);
	
	inline void setText(const QString & newText);
	inline QString text() const { return myText; }
	inline QSize sizeHint() const;

protected:
	inline void paintEvent(QPaintEvent * e);
	inline void timerEvent(QTimerEvent * e);
	inline void showEvent(QShowEvent * e);
	inline void hideEvent(QHideEvent * e);

private:
	QString myText;
	int offset;
	int myTimerId;
};

Ticker::Ticker(QWidget * parent) : QWidget(parent)
{
	offset		= 0;
	myTimerId	= 0;	// 定时器ID通常是非0的, 所以可以使用0来初始化来表示定时器没有启动
}

void Ticker::setText(const QString & newText)
{
	myText = newText;
	update();			// 强制执行重绘动作
	updateGeometry();	// 通知对Ticker窗口部件负责的任意布局管理器, 提示该窗口部件的大小发生了变化
}

QSize Ticker::sizeHint() const
{
	return fontMetrics().size(0, text());	// 0 是一个标识符, 简单的字符串不需要他, 因此只传递了一个0值
}

void Ticker::paintEvent(QPaintEvent *)
{
	QPainter painter(this);

	int textWidth = fontMetrics().width(text());	// 整个字符串的宽度
	if (textWidth < 1)
		return;
	int x = -offset;
	while (x < width())
	{
		painter.drawText(x, 0, textWidth, height(), Qt::AlignLeft | Qt::AlignVCenter, text());
		x += textWidth;
	}
}

void Ticker::showEvent(QShowEvent *)	// 本可以在构造函数中startTimer(), 但是只有窗口部件实际可见的时候, 才有必要保存Qt产生的定时器事件的那些资源
{
	myTimerId = startTimer(30);	// 启动定时器, 返回定时器ID
}

void Ticker::timerEvent(QTimerEvent * e)
{
	if (e->timerId() == myTimerId)
	{
		++offset;
		if (offset >= fontMetrics().width(text()))
			offset = 0;
		scroll(-1, 0);	// 把窗口部件的内容向左滚动一个像素	调用update()也可以, 但是scroll()会更有效率, 因为它只是简单移动屏幕上已经存在的像素并且只对这个窗口部件的新显示区域产生一个绘制事件(此时, 只是一个1像素乘以宽度的像素条);
	}
	else
		QWidget::timerEvent(e);	// 如果不是我们关注的那个定时器, 把它传给基类
}

void Ticker::hideEvent(QHideEvent *)
{
	killTimer(myTimerId);
	myTimerId = 0;
}

#endif