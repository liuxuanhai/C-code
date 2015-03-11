#ifndef P027_SORTDIALOG_140717_H
#define P027_SORTDIALOG_140717_H

#include <QDialog>
#include <QGroupBox>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QGridLayout>

class Ui_SortDialog
{
public:
	// 总布局
	QGridLayout * mainGridLayout;	// 布局会自动调整父部件的大小但是部件不会自动调整父部件的大小

	// 第一个群组
	QGroupBox	* primaryGroupBox;
	QLabel		* primaryColumnLabel;
	QLabel		* primaryOrderLabel;
	QComboBox	* primaryColumnComboBox;
	QComboBox	* primaryOrderComboBox;
	QGridLayout * primaryGridLayout;
	QSpacerItem * primaryHSpacer;
	// 右侧按钮
	QPushButton	* okButton;
	QPushButton * cancelButton;
	QPushButton * moreButton;
	QVBoxLayout * VLayout;
	QSpacerItem * VSpacer;
	// 一二组之间的伸展器
	QSpacerItem * mainVSpacer;
	// 第二个群组
	QGroupBox	* secondaryGroupBox;
	QLabel		* secondaryColumnLabel;
	QLabel		* secondaryOrderLabel;
	QComboBox	* secondaryColumnComboBox;
	QComboBox	* secondaryOrderComboBox;
	QGridLayout * secondaryGridLayout;
	QSpacerItem * secondaryHSpacer;

	void setupUi(QDialog * SortDialog)
	{
		mainGridLayout = new QGridLayout(SortDialog);
		//SortDialog->layout()->setSizeConstraint(QLayout::SetFixedSize);
		mainGridLayout->setSizeConstraint(QLayout::SetFixedSize);
		// 固定对话框的大小 constraint 约束 fixed 固定的
		// 这样一来, 布局就会负责重定义对话框大小的职责, 并且会在显示或者隐藏窗口部件的时候自动重定义这个对话框的大小
		// 主要表象是: 如果没有这个的话, 在隐藏了第二群组以后, 主窗口不会自动缩小

				// 创建第一个群组
		
		// 部件定义
		primaryGroupBox		= new QGroupBox;
		primaryColumnLabel	= new QLabel;
		primaryOrderLabel	= new QLabel;
		primaryColumnComboBox	= new QComboBox;
		primaryOrderComboBox	= new QComboBox;
		primaryGridLayout		= new QGridLayout(primaryGroupBox);
		primaryHSpacer			= new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

		mainGridLayout->addWidget(primaryGroupBox, 0, 0, 1, 1);

		// Grid布局管理
		primaryGridLayout->addWidget(primaryColumnLabel, 0, 0, 1, 1);
		primaryGridLayout->addWidget(primaryColumnComboBox, 0, 1, 1, 1);
		primaryGridLayout->addItem(primaryHSpacer, 0, 2, 1, 1);
		primaryGridLayout->addWidget(primaryOrderLabel, 1, 0, 1, 1);
		primaryGridLayout->addWidget(primaryOrderComboBox, 1, 1, 1, 2);		

				// 创建右侧按钮

		// 部件定义
		okButton		= new QPushButton;
		cancelButton	= new QPushButton;
		moreButton		= new QPushButton;
		VLayout			= new QVBoxLayout;
		VSpacer			= new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

		moreButton->setCheckable(true);	// 将More设置成一个开关按钮

		// VLayout布局管理
		VLayout->addWidget(okButton);
		VLayout->addWidget(cancelButton);
		VLayout->addItem(VSpacer);
		VLayout->addWidget(moreButton);

		mainGridLayout->addLayout(VLayout, 0, 1, 2, 1);

				// 创建第一第二群组之间的伸展器

		mainVSpacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);	// 横向最小, 纵向伸展
		mainGridLayout->addItem(mainVSpacer, 1, 0, 1, 1);

				// 创建第二个群组
		
		// 部件定义
		secondaryGroupBox		= new QGroupBox;
		secondaryColumnLabel	= new QLabel;
		secondaryOrderLabel		= new QLabel;
		secondaryColumnComboBox	= new QComboBox;
		secondaryOrderComboBox	= new QComboBox;
		secondaryGridLayout		= new QGridLayout(secondaryGroupBox);
		secondaryHSpacer		= new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

		secondaryGroupBox->setVisible(false);	// 隐藏第二个群组

		mainGridLayout->addWidget(secondaryGroupBox, 2, 0, 1, 1);

		// Grid布局管理
		secondaryGridLayout->addWidget(secondaryColumnLabel, 0, 0, 1, 1);
		secondaryGridLayout->addWidget(secondaryColumnComboBox, 0, 1, 1, 1);
		secondaryGridLayout->addItem(secondaryHSpacer, 0, 2, 1, 1);
		secondaryGridLayout->addWidget(secondaryOrderLabel, 1, 0, 1, 1);
		secondaryGridLayout->addWidget(secondaryOrderComboBox, 1, 1, 1, 2);		

		retranslateUi(SortDialog);

		QObject::connect(okButton, SIGNAL(clicked()), SortDialog, SLOT(accept()));
		QObject::connect(cancelButton, SIGNAL(clicked()), SortDialog, SLOT(reject()));
		QObject::connect(moreButton, SIGNAL(toggled(bool)), secondaryGroupBox, SLOT(setVisible(bool)));
	}

	void retranslateUi(QDialog * SortDialog)
	{
		SortDialog->setWindowTitle("Sort");
		// 第一群组
		primaryGroupBox		->setTitle("&Primary Key");
		primaryColumnLabel	->setText("Column: ");
		primaryOrderLabel	->setText("Order: ");

		primaryColumnComboBox->clear();	// 移除所有项目
		primaryColumnComboBox->addItem("None");
		primaryOrderComboBox->clear();
		primaryOrderComboBox->addItem("Ascending");
		primaryOrderComboBox->addItem("Descending");
		// 右侧按钮
		okButton	->setText("Ok");
		cancelButton->setText("Cancel");
		moreButton	->setText("More");
		// 第二群组
		secondaryGroupBox	->setTitle("&Secondary Key");
		secondaryColumnLabel->setText("Column: ");
		secondaryOrderLabel	->setText("Order: ");

		secondaryColumnComboBox->clear();
		for (QChar i = 'A'; i <= 'F'; i.unicode()++)
			secondaryColumnComboBox->addItem(i);
		secondaryOrderComboBox->clear();
		for (QChar i = 'F'; i >= 'A'; i.unicode()--)
			secondaryOrderComboBox->addItem(i);
	}
};

#endif