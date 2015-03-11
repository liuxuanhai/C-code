#ifndef PLOTTER_H
#define PLOTTER_H

#include <QMap>
#include <QPixmap>
#include <QVector>
#include <QWidget>

class QToolButton;
class PlotSettings;

class Plotter : public QWidget
{
	Q_OBJECT;
public:
	inline Plotter(QWidget * parent = nullptr);

	inline void setPlotSettings(const PlotSettings & settings);	// plot 图 settings 设置
	inline void setCurveData(int id, const QVector<QPointF> & data);	// curve 曲线
	inline void clearCurve(int id);
	inline QSize minimumSizeHint() const;	// 重写虚函数
	inline QSize sizeHint() const;			// 重写虚函数

public slots:
	inline void zoomIn();
	inline void zoomOut();

protected:	// 声明所有需要重新实现的QWidget事件处理器
	inline void paintEvent(QPaintEvent * e);
	inline void resizeEvent(QResizeEvent * e);
	inline void mousePressEvent(QMouseEvent * e);
	inline void mouseMoveEvent(QMouseEvent * e);
	inline void mouseReleaseEvent(QMouseEvent * e);
	inline void keyPressEvent(QKeyEvent * e);
	inline void wheelEvent(QWheelEvent * e);

private:	// 一些用于绘制这个窗口部件的函数, 一个常量和几个成员变量
	inline void updateRubberBandRegion();	// rubber band 橡胶环
	inline void refreshPixmap();	// refresh 更新
	inline void drawGrid(QPainter * painter);
	inline void drawCurves(QPainter * painter);

	enum{ Margin = 50 };	// margin 边缘	为图形区域的周围提供一些空间

	QToolButton * zoomInButton;
	QToolButton * zoomOutButton;
	QMap<int, QVector<QPointF>> curveMap;
	QVector<PlotSettings> zoomStack;
	int curZoom;
	bool ruberBandIsShown;
	QRect rubberBandRect;
	QPixmap pixmap;	// 这个变量对整个窗口不见得额绘制数据进行了复制保存, 这和屏幕上显示的图形是相同的. 绘图区总是先在脱屏像素映射上绘制图形, 然后才把这一像素映射复制到窗口部件中
};

class PlotSettings	// 给定x轴y轴的范围以及在这些轴上刻度标记符的数量
{
public:
	inline PlotSettings();

	inline void	scroll(int dx, int dy);
	inline void	adjust();
	double	spanX() const { return maxX - minX; }
	double	spanY() const { return maxY - minY; }

	double	minX;
	double	maxX;
	int		numXTicks;
	double	minY;
	double	maxY;
	int		numYTicks;

private:
	inline static void adjustAxis(double & min, double & max, int & numTicks);
};

#include <QToolButton>

Plotter::Plotter(QWidget * parent) : QWidget(parent)
{
	setBackgroundRole(QPalette::Dark);	// role 角色 任务	使用调色板中的"暗"分量作为重绘窗口部件的颜色, 而不是使用"背景色"分量
	setAutoFillBackground(true);	// 启用上边的机制
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);	// 默认是QtSizePolicy::Preferred: 窗口部件大小就是提示大小, 如果有必要, 可以无限放大, 也可以一直缩小到提示给出的最小大小
	setFocusPolicy(Qt::StrongFocus);	// 让用户通过单击或者按下Tab键而输入焦点
	ruberBandIsShown = false;
	zoomInButton = new QToolButton(this);
	zoomInButton->setIcon(QIcon("images/zoomIn.png"));
	zoomInButton->adjustSize();	// 设置成大小提示的大小
	connect(zoomInButton, SIGNAL(clicked()), this, SLOT(zoomIn()));

	zoomOutButton = new QToolButton(this);
	zoomOutButton->setIcon(QIcon("images/zoomOut.png"));
	zoomOutButton->adjustSize();
	connect(zoomOutButton, SIGNAL(clicked()), this, SLOT(zoomOut()));

	setPlotSettings(PlotSettings());
}

void Plotter::setPlotSettings(const PlotSettings & settings)	// 指定显示绘图区时用到的PlotSettings
{
	zoomStack.clear();
	zoomStack.append(settings);	// append 附加 贴上 设置数据文件的搜索路径
	curZoom = 0;
	zoomInButton->hide();
	zoomOutButton->hide();
	refreshPixmap();	// 这里不使用update(), 因为我们想让QPixmap在任意时刻都处于最新状态, 在重新生成像素映射之后, refreshPixmap()会调用update(), 会把像素映射复制到窗口部件中
}
	// 开始时使用默认缩放级, 用户每放大一次, 都会创建一个新的PlotSettings实例, 并且会将其放入缩放堆栈中

void Plotter::zoomOut()	// zoom out 缩小
{
	if (curZoom > 0)
	{
		--curZoom;
		zoomOutButton->setEnabled(curZoom > 0);
		zoomInButton->setEnabled(true);
		zoomInButton->show();
		refreshPixmap();
	}
}

void Plotter::zoomIn()
{
	if (curZoom < zoomStack.count() - 1)
	{
		++curZoom;
		zoomInButton->setEnabled(curZoom < zoomStack.count() - 1);
		zoomOutButton->setEnabled(true);
		zoomOutButton->show();
		refreshPixmap();
	}
}

void Plotter::setCurveData(int id, const QVector<QPointF> & data)
{
	curveMap[id] = data;
	refreshPixmap();
}

void Plotter::clearCurve(int id)	// 移除一条给定的曲线
{
	curveMap.remove(id);
	refreshPixmap();
}

QSize Plotter::minimumSizeHint() const	// 指定理想最小大小 这是布局管理器缩小这个部件的极限
{
	return QSize(6 * Margin, 4 * Margin);
}

QSize Plotter::sizeHint() const
{
	return QSize(12 * Margin, 8 * Margin);
}

// Protected 中的事件处理器
#include <QStylePainter>
#include <QStyleOptionFocusRect>
void Plotter::paintEvent(QPaintEvent * /*e*/)	// 通常paintEvent()执行所有绘制任务, 但是这里图形区的绘制任务都在之前的refreshPixmap()中完成了, 所以只需简单的通过把该像素映射复制到窗口部件的(0, 0)位置处理来完成整个图形绘制工作
{
	QStylePainter painter(this);
	painter.drawPixmap(0, 0, pixmap);

	if (ruberBandIsShown)
	{
		painter.setPen(palette().light().color());	// 选择当前颜色组中的"亮"分量作为画笔的颜色, 正好让绘制出的橡皮筋选择框与"暗"分量背景形成很好的反差
		painter.drawRect(rubberBandRect.normalized());	// QRect::normalized()确保这个矩形橡皮筋选择框的宽度和高度都是正值, 并且adjusted()可以把矩形的大小减去一个像素, 以允许它具有一个像素宽的轮廓
		if (hasFocus())	// 如果Plotter拥有焦点
		{
			QStyleOptionFocusRect option;
			option.initFrom(this);	// 焦点选择框各个绘制选项的初始化会基于Plotter窗口部件[通过调用initFrom()]
			option.backgroundColor = palette().dark().color();	// 明确给定背景颜色
			painter.drawPrimitive(QStyle::PE_FrameFocusRect, option);	// 绘制焦点选择框	// QStyle 窗口风格 xp, mac, win7...
		}
	}
}

void Plotter::resizeEvent(QResizeEvent * /*e*/)	// 构造函数中没有指定按钮的位置, 这是因为在一个窗口部件第一次显示之前, Qt总是会自动生成一个"重定义大小事件"
{
	int x = width() - (zoomInButton->width() + zoomOutButton->width() + 10);
	zoomInButton->move(x, 5);
	zoomOutButton->move(x + zoomInButton->width() + 5, 5);
	refreshPixmap();
}
#include <QMouseEvent>
void Plotter::mousePressEvent(QMouseEvent * e)
{
	QRect rect(Margin, Margin, width() - 2 * Margin, height() - 2 * Margin);
	if (e->button() == Qt::LeftButton)
	{
		if (rect.contains(e->pos()))	// 如果鼠标单击位置位于图像区
		{
			ruberBandIsShown = true;	// 鼠标左键按下, 产生一个橡皮筋选择框
			rubberBandRect.setTopLeft(e->pos());
			rubberBandRect.setBottomRight(e->pos());
				// QRect大小的定义方式:
					// 1. (x, y, width, height)
					// 2. 定义左上右下两个点的位置 setTopLeft(), setBottomRight()

			updateRubberBandRegion();	// 对橡皮筋选择框所覆盖的(最小)区域进行强制重绘
			setCursor(Qt::CrossCursor);	// Cross 十字	// 把鼠标光标改成十字形光标
				// 关于鼠标光标形状的控制:
					// 1. 鼠标悬停在某个窗口部件上, QWidget::setCursor()可以设置形状, 如果没有设置, 则跟随父窗口, 顶级窗口部件默认是箭头
					// 2. 对于整个应用程序中所使用的光标形状, 可以通过QApplication::setOverrideCursor()进行设置, 它会把不同窗口部件中的光标形状全部覆盖掉直到调用restoreOverrideCursor()
		}
	}
}

void Plotter::mouseMoveEvent(QMouseEvent * e)
{
	if (ruberBandIsShown)
	{
		updateRubberBandRegion();	// 预约一个绘制事件
		rubberBandRect.setBottomRight(e->pos());	// 重新计算rubberBandRect来说明鼠标移动的距离
		updateRubberBandRegion();	// 再一次对绘制区域橡皮筋选择框已经移动到的区域进行重新计算
			// 这样做可以有效擦除橡皮筋选择框, 并且可以在新的坐标系中重新绘制它
			// 如果用户向上或者向左移动鼠标, 看起来右下角跑到了左上角的上边或者左边, 这样, QRect就会具有一个负的宽度或者高度, paintEvent()中的QRect::normalized()就可以对他的角进行调整, 以确保能够获得非负的宽度值或者高度值
	}
}

void Plotter::mouseReleaseEvent(QMouseEvent * e)
{
	if (e->button() == Qt::LeftButton && ruberBandIsShown)
	{
		ruberBandIsShown = false;
		updateRubberBandRegion();
		unsetCursor();

		QRect rect = rubberBandRect.normalized();
		if (rect.width() < 4 || rect.height() < 4)	// 如果橡皮筋选择框不小于4 x 4就执行缩放操作, 如果小于, 看来应当是用户错误的点击了窗口部件, 或者仅仅是为了让窗口部件获得焦点
			return;
		rect.translate(-Margin, -Margin);

		PlotSettings prevSettings = zoomStack[curZoom];
		PlotSettings settings;
		double dx = prevSettings.spanX() / (width() - 2 * Margin);
		double dy = prevSettings.spanY() / (height() - 2 * Margin);
		settings.minX = prevSettings.minX + dx * rect.left();
		settings.maxX = prevSettings.minX + dx * rect.right();
		settings.minY = prevSettings.maxY - dy * rect.bottom();
		settings.maxY = prevSettings.maxY - dy * rect.top();
		settings.adjust();
			// 把橡皮筋选择框的坐标从窗口部件坐标系转换成绘图区坐标系


		zoomStack.resize(curZoom + 1);
		zoomStack.append(settings);
		zoomIn();
			// 调整绘图区坐标系并且放大橡皮筋选择框
	}
}

void Plotter::keyPressEvent(QKeyEvent * e)
{
	switch (e->key())
	{
	case Qt::Key_Plus:
		zoomIn();
		break;
	case Qt::Key_Minus:
		zoomOut();
		break;
	case Qt::Key_Left:
		zoomStack[curZoom].scroll(-1, 0);
		refreshPixmap();
		break;
	case Qt::Key_Right:
		zoomStack[curZoom].scroll(+1, 0);
		refreshPixmap();
		break;
	case Qt::Key_Down:
		zoomStack[curZoom].scroll(0, -1);
		refreshPixmap();
		break;
	case Qt::Key_Up:
		zoomStack[curZoom].scroll(0, +1);
		refreshPixmap();
		break;
	default:
		QWidget::keyPressEvent(e);
	}
}

void Plotter::wheelEvent(QWheelEvent * e)
{
	int numDegrees = e->delta() / 8;	// dalta()返回一个距离, 他等于滚轮旋转角度的八倍
	int numTicks = numDegrees / 15;		// 鼠标通常都以15度作为步长

	if (e->orientation() == Qt::Horizontal)		// 少见的水平滚轮
		zoomStack[curZoom].scroll(numTicks, 0);	// 通过修改缩放堆栈上最顶端的元素来改变所需的标记符数量
	else										// 常见的垂直滚轮
		zoomStack[curZoom].scroll(0, numTicks);	
	refreshPixmap();
}

// private
void Plotter::updateRubberBandRegion()
{
	QRect rect = rubberBandRect.normalized();
	update(rect.left(), rect.top(), rect.width(), 1);
	update(rect.left(), rect.top(), 1, rect.height());
	update(rect.left(), rect.bottom(), rect.width(), 1);
	update(rect.right(), rect.top(), 1, rect.height());
}

void Plotter::refreshPixmap()	// 把绘图区重新绘制到脱屏像素映射器上, 并且对显示加以更新
{
	pixmap = QPixmap(size());	// 像素映射大小调整为窗口部件大小
	pixmap.fill(this, 0, 0);	// 使用窗口部件的擦除颜色来填充该像素映射, 这个颜色就是调色板中的"暗"分量, 如果背景色是一个非实心的画笔, QPixmap::fill()就需要知道窗口部件中的偏移量, 像素映射需要在那里恰好与画笔图案相对齐 (0, 0)像素映射与整个窗口部件相对应

	QPainter painter(&pixmap);	// 创建一个QPainter在这个像素映射上进行绘制
	painter.initFrom(this);		// 设置painter所使用的画笔, 背景色, 字体与Plotter窗口部件中的一样
	// 执行绘制
	drawGrid(&painter);	
	drawCurves(&painter);
	update();	// 预约绘制事件, painteEvent()把像素映射复制到窗口部件中
}

void Plotter::drawGrid(QPainter * painter)	// 绘制曲线和坐标轴后边的网格
{
	QRect rect(Margin, Margin, width() - 2 * Margin, height() - 2 * Margin);
	if (!rect.isValid())	// 绘制网格的区域是通过rect给定的, 如果窗口部件不够大, 不能容下这个图形, 就立即返回
		return;
	PlotSettings settings = zoomStack[curZoom];
	QPen quiteDark = palette().dark().color().light();
	QPen light = palette().light().color();

	for (int i = 0; i <= settings.numXTicks; i++)	// 绘制网格的垂直线和沿x轴方向上的标记符
	{
		int x = rect.left() + (i * (rect.width() - 1) / settings.numXTicks);
		double label = settings.minX + (i * settings.spanX() / settings.numXTicks);
		painter->setPen(quiteDark);
		painter->drawLine(x, rect.top(), x, rect.bottom());
		painter->setPen(light);
		painter->drawLine(x, rect.bottom(), x, rect.bottom() + 5);
		painter->drawText(x - 50, rect.bottom() + 5, 100, 20, Qt::AlignHCenter
			| Qt::AlignTop, QString::number(label));
	}
	for (int j = 0; j <= settings.numYTicks; j++)	// 绘制网格的水平线和沿y轴方向上的标记符
	{
		int y = rect.bottom() - (j * (rect.height() - 1) / settings.numYTicks);
		double label = settings.minY + (j * settings.spanY() / settings.numYTicks);
		painter->setPen(quiteDark);
		painter->drawLine(rect.left(), y, rect.right(), y);
		painter->setPen(light);
		painter->drawLine(rect.left() - 5, y, rect.left(), y);
		painter->drawText(rect.left() - Margin, y - 10, Margin - 5, 20, 
			Qt::AlignRight | Qt::AlignVCenter, QString::number(label));	// 绘制两个坐标轴上与记号相对应的那些数字
			// drawText(x, y, width, height, alignment, text) 先定义一个矩形, 然后指定矩形中文本的位置, text就是要绘制的文本
	}
	painter->drawRect(rect.adjusted(0, 0, -1, -1));	// 沿空白区域绘制一个方形
}

void Plotter::drawCurves(QPainter * painter)	// 在网格上绘制曲线
{
	static const QColor colorForIds[6] = {
		Qt::red, Qt::green, Qt::blue, Qt::cyan, Qt::magenta, Qt::yellow
	};
	PlotSettings settings = zoomStack[curZoom];
	QRect rect(Margin, Margin, width() - 2 * Margin, height() - 2 * Margin);
	if (!rect.isValid())
		return;
	painter->setClipRect(rect.adjusted(+1, +1, -1, -1));	// 它为包含这些曲线(边白鹤包围绘图区的框架除外)的矩形设置QPainter剪辑区, 然后QPainter将会忽略在这个区域之外的像素绘制操作
	QMapIterator<int, QVector<QPointF>> i(curveMap);	// 使用java形式的迭代器遍历所有曲线, 并且对于每一条曲线都要遍历构成他的每一个QPointF值
	while (i.hasNext())
	{
		i.next();
		int id = i.key();	// 调用迭代器的key()函数获取曲线的ID
		QVector<QPointF> data = i.value();	// 用迭代器的value()函数获取相应曲线的QVector<QPointF>类型数据
		QPolygonF polyline(data.count());
		for (int j = 0; j < data.count(); j++)	// for循环把每个QPointF都从绘图区坐标系转换到窗口部件坐标系, 并且把他们保存到polyline变量中
		{
			double dx = data[j].x() - settings.minX;
			double dy = data[j].y() - settings.minY;
			double x  = rect.left() + (dx * (rect.width() - 1) / settings.spanX());
			double y  = rect.bottom() - (dy * (rect.height() - 1) / settings.spanY());
			polyline[j] = QPointF(x, y);
		}
			// 将一条曲线的全部点的坐标转换成窗口部件中的坐标

		painter->setPen(colorForIds[uint(id) % 6]);	// 为用于这条曲线的画笔设置颜色(使用预定义的颜色集之一)
		painter->drawPolyline(polyline);	// 调用drawPolyline()绘制一条经过该曲线上所有点的直线
	}
}

PlotSettings::PlotSettings()
{
	minX = 0.0;
	maxX = 10.0;
	numXTicks = 5;

	minY = 0.0;
	maxY = 10.0;
	numYTicks = 5;
}

void PlotSettings::scroll(int dx, int dy)
{
	double stepX = spanX() / numXTicks;
	minX += dx * stepX;
	maxX += dx * stepX;

	double stepY = spanY() / numYTicks;
	minY += dy * stepY;
	maxY += dy * stepY;
}

void PlotSettings::adjust()
{
	adjustAxis(minX, maxX, numXTicks);	// Axis 轴
	adjustAxis(minY, maxY, numYTicks);
}

void PlotSettings::adjustAxis(double & min, double & max, int & numTicks)
{
	const int MinTicks = 4;
	double grossStep = (max - min) / MinTicks;
	double step = std::pow(10.0, std::floor(std::log10(grossStep)));

	if (5 * step < grossStep)
		step *= 5;
	else if (2 * step < grossStep)
		step *= 2;
	
	numTicks = int(std::ceil(max / step) - std::floor(min / step));
	if (numTicks < MinTicks)
		numTicks = MinTicks;
	min = std::floor(min / step) * step;
	max = std::ceil(max / step) * step;
}

#endif