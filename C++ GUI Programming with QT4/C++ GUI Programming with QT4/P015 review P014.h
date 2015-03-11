#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QDialog>

class FindDialog : public QDialog
{
	Q_OBJECT;
public:
	FindDialog(QWidget * parent = nullptr);
signals:
	void findPrev(const QString & text, Qt::CaseSensitivity cs);
	void findNext(const QString & text, Qt::CaseSensitivity cs);
private slots:
	void findClicked();
	void enableFindButton(const QString & text);
public:
	QLabel		* Label;
	QLineEdit	* LineEdit;
	QCheckBox	* caseCheckBox;
	QCheckBox	* backwardCheckBox;
	QPushButton * findPushButton;
	QPushButton * closePushButton;
};
