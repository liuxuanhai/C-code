// 1.	初始化的时候给创建布局, 并把部件加进去, 设定部件的大小策略, 设定拉伸因子等等, 用不到设定paintEvent

#include <QApplication>
#include <QPushButton>
#include <QLayout>

class studyLayout : public QWidget
{
private:
	QHBoxLayout * hLayout;
	QPushButton * okButton;
	QPushButton * cancelButton;
public:
	studyLayout(QWidget * parent = nullptr);
};

int main(int argc, char ** argv)
{
	QApplication App(argc, argv);
	studyLayout * s = new studyLayout;

	s->setGeometry(200, 200, 500, 500);
	s->show();
	s->adjustSize();	// 这个语句使得上边的setGeometry的位置可用, 大小失效 关于大小, 跟随的就是最近的一次设置的大小而已
	return App.exec();
}

studyLayout::studyLayout(QWidget * parent) : QWidget(parent)
{
	hLayout		= new QHBoxLayout;
	okButton	= new QPushButton(tr("OK"));
	cancelButton= new QPushButton(tr("Cancel"), this);
	okButton->setSizePolicy(QSizePolicy::Maximum, okButton->sizePolicy().verticalPolicy());
	hLayout->addWidget(okButton);
	hLayout->addWidget(cancelButton);
	hLayout->addStretch();
	setLayout(hLayout);
	hLayout->setContentsMargins(20, 50, 20, 50);	// 设置边距, (left, top, right, bottom)
	hLayout->setSpacing(100);	// 设置部件之间的距离
}
