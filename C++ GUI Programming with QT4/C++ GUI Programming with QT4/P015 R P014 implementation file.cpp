#include <QtGui>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "P015 review P014.h"
FindDialog::FindDialog(QWidget * parent)
{
	Label			= new QLabel(tr("Find &what:"));
	LineEdit		= new QLineEdit;
	Label->setBuddy(LineEdit);
	caseCheckBox	= new QCheckBox(tr("&Match"));
	backwardCheckBox= new QCheckBox(tr("Find &Next")); 
	findPushButton	= new QPushButton(tr("&Find"));
	findPushButton->setDefault(true);
	findPushButton->setEnabled(false);
	closePushButton = new QPushButton(tr("&Close"));

	connect(LineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(enableFindButton(const QString &)));
	connect(findPushButton, SIGNAL(clicked()), this, SLOT(findClicked()));
	connect(closePushButton, SIGNAL(clicked()), this, SLOT(close()));

	QHBoxLayout * topLeftLayout = new QHBoxLayout;
	topLeftLayout->addWidget(Label);
	topLeftLayout->addWidget(LineEdit);
	
	QVBoxLayout * LeftLayout = new QVBoxLayout;
	LeftLayout->addLayout(topLeftLayout);
	LeftLayout->addWidget(caseCheckBox);
	LeftLayout->addWidget(backwardCheckBox);

	QVBoxLayout * RightLayout = new QVBoxLayout;
	RightLayout->addWidget(findPushButton);
	RightLayout->addWidget(closePushButton);
	RightLayout->addStretch();

	QHBoxLayout * MainLayout = new QHBoxLayout;
	MainLayout->addLayout(LeftLayout);
	MainLayout->addLayout(RightLayout);

	setWindowTitle(tr("Find"/*"P015 复习 Find对话框"*/));
	setLayout(MainLayout);
	setFixedHeight(sizeHint().height());
}

void FindDialog::findClicked()
{
	QString text = LineEdit->text();
	Qt::CaseSensitivity cs = caseCheckBox->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive;
	if (backwardCheckBox->isChecked())
	{
		emit findPrev(text, cs);	// emit是Qt中得关键字, 像其他Qt扩展一样, 他也会被C++预处理器转换成标准的C++代码
	}
	else
	{
		emit findNext(text, cs);
	}
}

void FindDialog::enableFindButton(const QString & text)
{
	findPushButton->setEnabled(!text.isEmpty());
}