// 只需要子类化QThread并且重新实现它的run()函数就可以了
#ifndef THREAD_H
#define THREAD_H
#include <QThread>
#include <QPushButton>
#include <QDialog>
#include <QCloseEvent>
#include <QLayout>
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <iostream>

#include <QMutex>
// QMutex类: 提供一种保护一个变量或者一段代码的方法, 这样就可以每次只让一个线程读取它;
	// 这个类提供了一个lock()函数来锁住互斥量(mutex), 如果互斥量是解锁的, 那么当前线程就立即占用并锁定它, 否则, 当前线程就会被阻塞, 直到掌握这个互斥量的线程对他解锁为止;

class Thread : public QThread
{
public: 
	inline Thread(const QString & fileName);
	inline void setMessage(const QString & message) { messageStr = message; }
	inline void stop();
		// QThread提供了一个terminate()函数, 该函数可以在一个线程还在运行的时候就终止他的运行, 我们不推荐使用terminate(), 因为它可以随时停止线程执行而不给这个线程自我清空的机会;而像这里使用stopped变量和stop()方法是比较安全的

protected:
	inline void run();
private:
	QMutex			mutex;		// # 1
	QFile			file;
	QString			messageStr;
	volatile bool	stopped;	// 声明为易失性变量
};

class ThreadDialog : public QDialog
{
	Q_OBJECT
public:
	inline ThreadDialog(QWidget * parent = nullptr);

protected:
	inline void closeEvent(QCloseEvent * e);

private slots:
	inline void startOrStopThreadA();
	inline void startOrStopThreadB();

private:
	Thread threadA;
	Thread threadB;

	QPushButton * threadAButton;
	QPushButton * threadBButton;
	QPushButton * quitButton;
};

Thread::Thread(const QString & fileName) : file(fileName)
{
	stopped = false;

	if (!file.open(QIODevice::WriteOnly))
		QMessageBox::warning(nullptr, tr("ERROR"), tr((QString("Cannot open the file %1\n%2").arg(fileName).arg(file.errorString())).toStdString().c_str()));
}

void Thread::run()	// 在开始执行线程的时候, 就会调用run()函数, 只要stopped变量变为false值, 这个函数就一直想控制台打印输出给定的消息, 当控制离开run()函数时就会终止线程
{
	//QApplication::setOverrideCursor(Qt::WaitCursor);
	QTextStream out(&file);
	forever	// # 2
	{
		mutex.lock();
		if (stopped)
		{
			stopped = false;
			mutex.unlock();
			break;
		}
		mutex.unlock();
		out << qPrintable(messageStr);
	}
	out << "\n";
}

void Thread::stop()
{
	mutex.lock();	// # 3
	stopped = true;
	mutex.unlock();
}

ThreadDialog::ThreadDialog(QWidget * parent): QDialog(parent), threadA("P255 B.txt"), threadB("P255 B.txt")
{
	threadA.setMessage("A");	// 让第一个线程重复打印字母"A"
	threadB.setMessage("B");	// 让第二个线程重复打印字母"B"

	threadAButton	= new QPushButton(tr("Start A"));
	threadBButton	= new QPushButton(tr("Start B"));
	quitButton		= new QPushButton(tr("Quit"));
	quitButton->setDefault(true);
	connect(threadAButton, SIGNAL(clicked()), this, SLOT(startOrStopThreadA()));
	connect(threadBButton, SIGNAL(clicked()), this, SLOT(startOrStopThreadB()));
	connect(quitButton,	   SIGNAL(clicked()), qApp, SLOT(quit()));

	QHBoxLayout * hLayout = new QHBoxLayout(this);
	hLayout->addWidget(threadAButton);
	hLayout->addWidget(threadBButton);
	hLayout->addWidget(quitButton);
	// ....
}

void ThreadDialog::startOrStopThreadA()
{
	if (threadA.isRunning())
	{
		threadA.stop();
		threadAButton->setText(tr("Start A"));
	}
	else
	{
		threadA.start();
		threadAButton->setText(tr("Stop A"));
	}
}

void ThreadDialog::startOrStopThreadB()
{
	if (threadB.isRunning())
	{
		threadB.stop();
		threadBButton->setText(tr("Start B"));
	}
	else
	{
		threadB.start();
		threadBButton->setText(tr("Stop B"));
	}
}

void ThreadDialog::closeEvent(QCloseEvent * e)
{
	threadA.stop();
	threadB.stop();
	threadA.wait();
	threadB.wait();
	e->accept();
}

#endif