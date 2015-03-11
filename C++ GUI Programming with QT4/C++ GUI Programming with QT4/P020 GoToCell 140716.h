#ifndef P020_GOTOCELL_140716_H
#define P020_GOTOCELL_140716_H

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

class GoToCellDialog;

// 用手写代码的方式实现Qt助手生成的对话框代码
namespace Ui
{
	class Ui_GoToCell
	{
	public:
		QLabel		* label;
		QLineEdit	* lineEdit;
		QPushButton	* okButton;
		QPushButton * cancelButton;
		QHBoxLayout	* HLayoutUp;
		QHBoxLayout	* HLayoutDown;
		QVBoxLayout * VLayout;

		void setupUi(QWidget * GoToCellDialog)
		{	
			// 水平布局: label lineEdit
			label		= new QLabel;
			lineEdit	= new QLineEdit;
			HLayoutUp	= new QHBoxLayout;

			label->setBuddy(lineEdit);

			HLayoutUp->addWidget(label);
			HLayoutUp->addWidget(lineEdit);

			// 水平布局: okButton cancelButton
			okButton	= new QPushButton;
			cancelButton= new QPushButton;
			HLayoutDown = new QHBoxLayout;
			
			HLayoutDown->addStretch();
			HLayoutDown->addWidget(okButton);
			HLayoutDown->addWidget(cancelButton);

			// 垂直布局: HLayoutUp HLayoutDown
			VLayout		= new QVBoxLayout(GoToCellDialog);

			VLayout->addLayout(HLayoutUp);
			VLayout->addLayout(HLayoutDown);

			retranslateUi(GoToCellDialog);
		}

		void retranslateUi(QWidget * GoToCellDialog)
		{
			GoToCellDialog->setWindowTitle("GoToCell");
			label->setText("&CellLocation: ");
			okButton->setText("Ok");
			cancelButton->setText("Calcel");
		}
	};

	class GoToCellDialog : public Ui_GoToCell{};
}

// 实现上述代码的部件之间的 信号 - 槽 关系
#include <QDialog>	// 这里必须Qdialog在前面, Ui::GoToCellDialog在后边
class GoToCellDialog : public QDialog, public Ui::GoToCellDialog
{
	Q_OBJECT;
public:
	inline GoToCellDialog(QWidget * parent = nullptr);
private slots:
	inline void enableOkButton();
};

#include <QValidator>
GoToCellDialog::GoToCellDialog(QWidget * parent) : QDialog(parent)
{
	setupUi(this);
	okButton->setEnabled(false);
	QRegExp regExp("[A-Za-z][1-9][0-9]{0,2}");
	lineEdit->setValidator(new QRegExpValidator(regExp, this));	// validator 验证器
	connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
	connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
	connect(lineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(enableOkButton()));  // 注意: 这里textChanged(const QString &)中得参数必须加上, 即使在本例中他是被忽略不用的参数
}

void GoToCellDialog::enableOkButton()
{
	okButton->setEnabled(true);
}

#endif