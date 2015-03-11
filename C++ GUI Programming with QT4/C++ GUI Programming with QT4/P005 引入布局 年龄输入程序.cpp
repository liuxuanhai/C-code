#include <QApplication>
#include <QHBoxLayout>
#include <QSlider>	// 滑块部件
#include <QSpinBox>	// 微调框部件
int main(int argc, char * argv[])
{
	QApplication app(argc, argv);

	// 创建QWidget对象, 并把它作为应用程序的主窗口
	QWidget		* window	= new QWidget;
	window	->setWindowTitle("Enter Your Age");	// 设置显示在窗口标题栏上的文字
	
	// 创建QSpinBox(滑块)和QSlider(微调框)并设置他们的有效范围
	QSpinBox	* spinBox	= new QSpinBox;	// 本来应该将主窗口传递给他们的构造函数, 以说明这两个窗口部件的父对象都是这个窗口, 但是这里没有必要, 因为布局系统将会自行得出这一结果并自动把该窗口设置为微调框和滑块的父对象;
	QSlider		* slider	= new QSlider(Qt::Horizontal);
	spinBox	->setRange(0, 130);
	slider	->setRange(0, 130);

	// 确保微调框和滑块同步, 以便他们两个总是显示相同的数值
	QObject::connect(spinBox, SIGNAL(valueChanged(int)), slider, SLOT(setValue(int)));	// 一旦一个窗口部件的值发生了改变, 那么就会发射他的valueChanged(int)信号, 另一个窗口部件会用这个新值调用他的setValue(int)槽
	QObject::connect(slider, SIGNAL(valueChanged(int)), spinBox, SLOT(setValue(int)));
	spinBox	->setValue(35);	// 将微调框的值设置为35, 当这种情况发生时, QSpinBox就会发射valueChanged(int)信号, 其中, int参数的值是35, 这个参数会被传递给QSlider的setValue(int)槽, 然后发射valueChanged(int)信号, 这样就触发了微调框的setValue(int)槽, 但是由于微调框的值已经是35, 所以就不发射信号了, 这样避免了无限循环的情况 

	// 布局控制
	QHBoxLayout * layout = new QHBoxLayout;	// 创建布局管理器(layout manager)	QHBoxLayout: 在水平方向上排列窗口部件, 从左到右
											//									QVBoxLayout: 在垂直方向上排列窗口部件, 从上到下
											//									QGridLayout: 把各个窗口部件排列在一个网格中
	layout	->addWidget(spinBox);	// QHboxLayout可根据所负责的子对象的需要为他们分配所需的位置和大小
	layout	->addWidget(slider);

	window	->setLayout(layout);	// 在窗口上安装布局管理器	从软件的底层实现上来看, QSpinBox和QSlider会自动"重定义父对象", 他们会自动成为这个安装了布局的窗口部件的子对象, 正是基于这种原因, 当创建一个需要放进某个布局中的窗口部件时, 就没有必要为其显示指定父对象了
	window	->show();

	return app.exec();
}