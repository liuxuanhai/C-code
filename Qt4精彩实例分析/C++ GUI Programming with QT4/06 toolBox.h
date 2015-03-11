// 创建: 2014-08-27 13:24:55

#ifndef TOOLBOX_H
#define TOOLBOX_H

#include <QToolBox>		// 提供一种列状的层叠窗体, 本例通过QToolBox实现一种抽屉效果
#include <QToolButton>	// 提供一种快速访问命令或选择项的按钮, 通常在工具条使用
#include <QGroupBox>
#include <QLayout>
class Drawer: public QToolBox
{
	Q_OBJECT
public:
	inline Drawer(QWidget * parent = nullptr, Qt::WindowFlags f = 0);
	inline ~Drawer(){}

	QToolButton * toolButton1_1;
	QToolButton * toolButton1_2;
	QToolButton * toolButton1_3;
	QToolButton * toolButton1_4;
	QToolButton * toolButton1_5;
	QToolButton * toolButton2_1;
	QToolButton * toolButton2_2;
	QToolButton * toolButton3_1;
	QToolButton * toolButton3_2;

private:
	inline void newButton(QToolButton * &);
};

Drawer::Drawer(QWidget * parent, Qt::WindowFlags f): QToolBox(parent, f)
{
	setWindowTitle(tr("My QQ"));

	QGroupBox * groupBox1 = new QGroupBox;	// 对应每个抽屉
	newButton(toolButton1_1);				// 对应抽屉内的每个按钮
	newButton(toolButton1_2);
	newButton(toolButton1_3);
	newButton(toolButton1_4);
	newButton(toolButton1_5);

	QVBoxLayout * layout1 = new QVBoxLayout(groupBox1);
	layout1->setMargin(10);
	layout1->setAlignment(Qt::AlignHCenter);
	layout1->addWidget(toolButton1_1);
	layout1->addWidget(toolButton1_2);
	layout1->addWidget(toolButton1_3);
	layout1->addWidget(toolButton1_4);
	layout1->addWidget(toolButton1_5);
	layout1->addStretch();

	QGroupBox * groupBox2 = new QGroupBox;
	newButton(toolButton2_1);
	newButton(toolButton2_2);
	
	QVBoxLayout * layout2 = new QVBoxLayout(groupBox2);
	layout2->setMargin(10);						// 窗体的显示间距
	layout2->setAlignment(Qt::AlignHCenter);	// 窗体的显示位置
	layout2->addWidget(toolButton2_1);
	layout2->addWidget(toolButton2_2);
	layout2->addStretch();	// 插入占位符, 使得所有按钮能靠上对齐, 并且整个抽屉大小变化时, 按钮不发生变化

	this->addItem((QWidget *)groupBox1, tr("my friends"));
	this->addItem((QWidget *)groupBox2, tr("my classmates"));
}

inline void Drawer::newButton(QToolButton * & tb)
{
	tb = new QToolButton;
	tb->setText(tr("panda"));					// 抽屉内按钮的文字
	tb->setIcon(QPixmap("images/panda.png"));	// 图标
	tb->setIconSize(QSize(100, 100));			// 大小
	tb->setAutoRaise(true);						// 当鼠标离开时, 按钮自动恢复成弹起状态
	tb->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
						// Qt::ToolButtonIconOnly: 只显示图标
						// Qt::ToolButtonTextOnly: 只显示文字
						// Qt::ToolButtonTextBesideIcon: 文字显示在图标旁边
						// Qt::ToolButtonTextUnderIcon:  文字显示在图标下面
}
#endif