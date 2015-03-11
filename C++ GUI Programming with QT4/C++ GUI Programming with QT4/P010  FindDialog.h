#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>

// 前置声明
class QCheckBox;
class QLabel;
class QLineEdit;
class QPushButton;

// 声明FindDialog并让他成为QDialog的子类
class FindDialog : public QDialog
{
	Q_OBJECT;	// !定义! 了信号和槽的类都写这个
public:
	FindDialog(QWidget * parent = nullptr);
signals:
	void findNext(const QString & str, Qt::CaseSensitivity cs);
	void findPrevious(const QString & str, Qt::CaseSensitivity cs);
private slots:
	void findClicked();
	void enableFindButton(const QString & text);
private:
	QLabel		* label;
	QLineEdit	* lineEdit;
	QCheckBox	* caseCheckBox;
	QCheckBox	* backwardCheckBox;
	QPushButton * findButton;
	QPushButton * closeButton;
};

#endif