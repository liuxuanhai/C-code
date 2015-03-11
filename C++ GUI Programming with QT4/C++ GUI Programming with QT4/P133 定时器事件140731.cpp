#include <QWidget>
#include <QEvent>
#include <QPainter>
#include <QApplication>

class Ticker : public QWidget
{
private:
	QString text;
	int		timeId;
	int		offset;
public:
	Ticker(QWidget * parent = nullptr);
	
	QString getText() { return text; }
	void	setText(const QString & t) { text = t; }
protected:
	void paintEvent(QPaintEvent *);
	void timerEvent(QTimerEvent *);	// 有定时器到时间了会调用这个函数(定时器事件)
	void showEvent(QShowEvent *) { timeId = startTimer(50); }
	void hideEvent(QHideEvent *) { killTimer(timeId); timeId = 0; }
		// 本可以在构造函数中startTimer(), 但是只有窗口部件实际可见的时候, 才有必要保存Qt产生的定时器事件的那些资源
};

int main(int argc, char ** argv)
{
	QApplication App(argc, argv);
	Ticker * T = new Ticker;

	T->show();
	return App.exec();
}

Ticker::Ticker(QWidget * parent) : QWidget(parent)
{
	offset = 0;
	timeId = 0;
}

void Ticker::paintEvent(QPaintEvent *)
{
	QPainter painter(this);	// this导致此时把设备环境信息也给传了进去

	painter.drawText(20, 20, 50, 50, Qt::AlignLeft | Qt::AlignVCenter, getText());
}

void Ticker::timerEvent(QTimerEvent * e)
{
	if (e->timerId() == timeId)
	{
		setText(QString::number(offset++));
		update();	// 使得客户区无效, 产生WM_PAINT消息
	}
	else
		QWidget::timerEvent(e);
}