// 图标编辑器
#ifndef ICONEDITOR_H
#define ICONEDITOR_H

#include <QColor>
#include <QImage>
#include <QWidget>

class IconEdit : public QWidget
{
	Q_OBJECT;
	Q_PROPERTY(QColor penColor READ penColor WRITE setPenColor)
	Q_PROPERTY(QImage iconImage READ iconImage WRITE setIconImage)
	Q_PROPERTY(int zoomFactor READ zoomFactor WRITE setZoomFactor)
		// 使用Q_PROPERTY(property 性质 性能)()宏声明了三个自定义属性: penColor, iconImage和zoomFactor
		// 每个属性都有一个数据类型, 一个"读"函数和一个作为可选项的"写"函数(penColor 属性类型: QColor 可以使用penColor()和setPenColor()对他进行读写)
		// 在Qt设计师中使用这个窗口部件的时候, Qt设计师的属性编辑器里, 那些继承于QWidget的属性下面, 将会显示这些自定义属性, 这些属性可以是由QVariant所支持的任何类型
public:
	IconEdit(QWidget * parent = nullptr);

	inline void		setPenColor(const QColor & newColor);
	inline QColor	penColor() const { return curColor; }
	inline void		setZoomFactor(int newZoom);
	inline int		zoomFactor() const { return zoom; }
	inline void		setIconImage(const QImage & newImage);
	inline QImage	iconImage() const { return image; }
	inline QSize	sizeHint() const;

protected:	// 重新实现QWidget中的三个保护函数
	inline void		mousePressEvent(QMouseEvent * event);
	inline void		mouseMoveEvent(QMouseEvent * event);
	inline void		paintEvent(QPaintEvent * event);

private:	// 拥有了自己的私有函数和私有变量
	inline void		setImagePixel(const QPoint & pos, bool opaque);
	inline QRect	pixelRect(int i, int j) const;

	QColor	curColor;
	QImage	image;
	int		zoom;
};

IconEdit::IconEdit(QWidget * parent) : QWidget(parent)
{
	setAttribute(Qt::WA_StaticContents);	// 告诉Qt, 当重新改变窗口部件的大小时, 窗口部件的内容没有发生变化, 而且他的内容仍旧保持从窗口部件左上角开始的特性, 这样避免了重新定义窗口部件大小的时候Qt对已经显示的区域进行重新绘制
		// 通常, 重新定义一个窗口部件的大小时, Qt会为窗口部件的整个可见区生成一个绘制事件, 如果在窗口部件创建的时候使用了Qt::WA_StaticContents属性, 那么绘制事件的区域会被严格限定在之前没有被显示的像素部分上

	setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);	// 告诉布局系统是否可以对其进行拉长和缩短
		// 这里告诉布局管理器, 窗口部件的大小提示(sizeHint())就是他的最小尺寸大小
		// 综上, 布局管理系统可以拉长这个窗口部件, 但是决不允许把它缩短到比他的大小提示还要小的尺寸

	curColor = Qt::black;	// 画笔颜色设置为黑色
	zoom = 8;				// 缩放因子设置为8 (图标中的每一个像素都会显示成一个8 x 8的正方形)
	image = QImage(16, 16, QImage::Format_ARGB32);	// 类型: QImage 初始化: 16 x 16的像素大小和32位的ARGB颜色格式, 这种格式支持半透明效果 通过填充一种透明的颜色就可以清空Images中的数据
		// QImage类使用一种与硬件无关的方式来存储图像, 可以把它设置成1位, 8位或者32位色深, 32位: 分别用八位存储红绿蓝分量, 剩余八位存储这个像素的alpha分量(即不透明度, 越大越不透明) 纯红色: QRgb red = 0xFFFF0000; 只有在处理QImage时才使用QRgb, 其他任意表示颜色的都用QColor
		// 图标数据会保存在image成员变量中, 并且可以通过setIconImage()和iconImage()函数对他们进行访问  当用户打开一个图标文件时, 图标编辑器程序通常用调用setIconImage()函数; 当用户保存这个图标时, 会调用iconImage()来重新得到这个图标
	image.fill(qRgba(0, 0, 0, 0));
}

QSize IconEdit::sizeHint() const
{
	QSize size = zoom * image.size();
	if (zoom >= 3)	// 如果缩放因子是3或者更大, 那么在每个方向上需要额外增加一个像素, 以便可以容纳一个网格线, 如果缩放因子是2或者1, 就不必再显示网格线, 因为这些网格线几乎不能再给图标的像素留下任何空间
		size += QSize(1, 1);
	return size;
}

void IconEdit::setPenColor(const QColor & newColor)
{
	curColor = newColor;
}

void IconEdit::setIconImage(const QImage & newImage)	// 设置需要编辑的图像
{
	if (newImage != image)	// 如果这个图像不是我们正在编辑的图像, 调用 # 1
	{
		image = newImage.convertToFormat(QImage::Format_ARGB32);	// # 1 这个函数把它变成一个带alpha缓冲的32位图像, 在其他代码中将会假设图像数据时存储在32位的ARGB值中的
		update();	// 使用心得图像强制重绘这个窗口部件
		updateGeometry();	// 告诉包含这个窗口部件的布局管理器, 这个窗口部件的大小提示已经发生了改变, 于是, 该布局将会自动适应这个新的大小提示
	}
}

void IconEdit::setZoomFactor(int newZoom)
{
	if (newZoom < 1)	// 避免在其他地方被0除, 应纠正任何小于1的值
		newZoom = 1;
	if (newZoom != zoom)
	{
		zoom = newZoom;
		update();
		updateGeometry();
	}
}
#include <QPainter>
#include <QtGui>
void IconEdit::paintEvent(QPaintEvent * e)
{
	QPainter painter(this);
	if (zoom >= 3)	// 如果缩放因子是3或者比3还要大, 使用QPainter::drawLine()函数绘制构成网格的水平线段和垂直线段
	{
		painter.setPen(palette().foreground().color());	// fore 前面 foreground 前景 最显著的位置
			// 使用调色板(palette)指定画笔的颜色
			// 每个窗口部件会配备一个调色板, 由它来确定做什么事应该使用什么颜色, 默认情况下, 一个窗口部件的调色板采用窗口系统的颜色主题
			// 一个窗口部件的调色板由三个颜色组成: 激活组(Active), 非激活组(Inactive), 不可用组(Disabled)

		for (int i = 0; i <= image.width(); ++i)
			painter.drawLine(zoom * i, 0, zoom * i, zoom * image.height());	// drawLine(x1, y1, x2, y2)	// (x1, y1)是线段一个端点位置, (x2, y2)是线段另一个端点位置
		for (int j = 0; j <= image.height(); ++j)
			painter.drawLine(0, zoom * j, zoom * image.width(), zoom * j);
	}
	for (int i = 0; i < image.width(); i++)
	{
		for (int j = 0; j < image.height(); j++)
		{
			QRect rect = pixelRect(i, j);
			if (!e->region().intersected(rect).isEmpty())
			{
				QColor color = QColor::fromRgba(image.pixel(i, j));	// IconEdit::pixelRect()返回一个QRect, 定义了需要重新绘制的区域
				if (color.alpha() < 255)
					painter.fillRect(rect, Qt::white);
				painter.fillRect(rect, color);	// 绘制缩放后的像素
			}
		}
	}
}

QRect IconEdit::pixelRect(int i, int j) const	// 返回一个适用于QPainter::fillRect()的QRect, 这里的i和j是QImage的像素坐标而不是窗口部件中的坐标, 如果缩放因子是1, 那么这两个坐标系就恰好一致了
{
	if (zoom >= 3)
		return QRect(zoom * i, zoom * j + 1, zoom - 1, zoom - 1);
	else
		return QRect(zoom * i, zoom * j, zoom, zoom);
}

void IconEdit::mousePressEvent(QMouseEvent * e)	// 用户按下鼠标按钮时, 系统就会产生一个"鼠标按下"事件, 重新实现QWidget::mousePressEvent()就可以响应这个事件
{
	if (e->button() == Qt::LeftButton)	// 对鼠标光标下的像素进行设置
		setImagePixel(e->pos(), true);	// 把这个像素设置成当前画笔的颜色
	else if (e->button() == Qt::RightButton)	// 对鼠标光标下的像素进行清空
		setImagePixel(e->pos(), false);			// 传递false来清空这个像素
}

void IconEdit::mouseMoveEvent(QMouseEvent * e)	// 处理"鼠标移动"事件(默认是用户按住一个键不放的时候才能产生, 通过QWidget::setMouseTracking()可以改变这一行为)
{
	if (e->buttons() & Qt::LeftButton)	// 如果同时按下两个键或者只俺下了左键
		setImagePixel(e->pos(), true);
	else if (e->buttons() & Qt::RightButton)
		setImagePixel(e->pos(), false);
}

void IconEdit::setImagePixel(const QPoint & pos, bool opaque)	// opaque 不透明的	这个函数在mousePressEvent()和mouseMoveEvent()中得到调用, pos是鼠标在窗口部件中的位置
{
	int i = pos.x() / zoom;
	int j = pos.y() / zoom;
		// 把鼠标的位置从窗口部件的坐标转换到图像的坐标

	if (image.rect().contains(i, j))	// 检查该点是否位于正确范围之内
	{
		if (opaque)
			image.setPixel(i, j, penColor().rgba());
		else
			image.setPixel(i, j, qRgba(0, 0, 0, 0));	// 清空一个像素事实上就是把它变成透明的
		update(pixelRect(i, j));	// 重新绘制参数区域
	}
}

#endif