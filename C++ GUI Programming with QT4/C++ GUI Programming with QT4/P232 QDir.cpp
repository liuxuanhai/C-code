// 计算一个特定目录以及这个目录下的任意深度的子目录中所有图片所占用的空间
#include <QApplication>
#include <QtGui>
#include <QWidget>
#include <QMessageBox>

// 计算特定目录以及这个目录下任意深度的子目录中所有图片所占用的空间
qlonglong imageSpace(const QString &path)
{
    QDir dir(path);	// 使用给定的路径创建一个QDir对象
    qlonglong size = 0;
	 
    QStringList filters;
    foreach (QByteArray format, QImageReader::supportedImageFormats())
        filters += "*." + format;

    foreach (QString file, dir.entryList(filters, QDir::Files))	// entryList() entry 条目, 入口 第一个参数是文件名过滤器的一个列表, 他们可以包含"*"和"?"这类的通配符  第二个参数指定所要的条目类型(普通文件, 目录, 驱动器)
        size += QFileInfo(dir, file).size();	// QFileInfo类可以访问文件的属性(大小, 权限, 属主和时间戳...)

    foreach (QString subDir, 
		dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot))	// 获得这个目录下的所有子目录
        size += imageSpace(path + QDir::separator() + subDir);	// 为了创建每一个子目录的路径, 把当前目录的路径和子目录名称组合起来, 然后用斜线把他们分隔开, 除了在Windows操作系统上认可"\"之外, QDir在所有平台上都把"\"认作是目录分隔符

    return size;
}

int main(int argc, char *argv[])
{
	QApplication App(argc, argv);
    QStringList args = QApplication::arguments();

    QString path = QDir::currentPath();	// 将路径转化为当前目录	// QDir::homePath()将他转化为用户的主目录, 如果用户在命令行中指定了一个路径, 就用它来代替前面的目录
    if (args.count() > 1)
        path = args[1];

	QWidget		W;

	QString str = QString("Space used by images in ") + qPrintable(path)
              + " and its subdirectories is "		// qPrintable() 将 QString 转换成 const char *
			  + QString::number(imageSpace(path) / 1024) + " KB";
	W.show();
	QMessageBox::warning(nullptr, nullptr, str);
	return App.exec();    
}
