#include <QApplication>
#include <QHBoxLayout>
#include <QSlider>
#include <QSpinBox>
int main(int argc, char * argv[])
{
	QApplication App(argc, argv);
	
	// QWidget主窗口
	QWidget * window = new QWidget;
	window->setWindowTitle("Enter Your Age");

	// 滑块部件
	QSlider * slider = new QSlider(Qt::Horizontal);	// 布局系统会正确的将主窗口设置为其父窗口
	slider->setRange(0, 130);

	// 微调框
	QSpinBox * spinBox = new QSpinBox;
	spinBox->setRange(0, 130);

	// 建立链接
	QObject::connect(spinBox, SIGNAL(valueChanged(int)), slider, SLOT(setValue(int)));
	QObject::connect(slider, SIGNAL(valueChanged(int)), spinBox, SLOT(setValue(int)));
	spinBox->setValue(35);

	// 布局控制
	QHBoxLayout * layout = new QHBoxLayout;
	layout->addWidget(spinBox);
	layout->addWidget(slider);

	window->setLayout(layout);	// 给主窗口按上布局管理器, 布局管理器中的部件自动视主窗口为父对象
	window->show();

	return App.exec();
}