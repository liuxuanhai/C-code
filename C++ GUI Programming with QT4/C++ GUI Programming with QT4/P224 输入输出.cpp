#include <QApplication>
#include <QImage>
#include <QMap>
#include <QString>
#include <QColor>
#include <QFile>
#include <QMessageBox>
#include <QWidget>

//#define WRITEFILE

const char * FILENAME = "P224 data.dat";
#if defined WRITEFILE
bool f(const QString fileName)
{
	QImage image("images/panda.png");
	QMap<QString, QColor> map;
	map.insert("red", Qt::red);
	map.insert("green", Qt::green);
	map.insert("blue", Qt::blue);
	QFile file(fileName);
	if (!file.open(QIODevice::WriteOnly))
	{
		QMessageBox::warning(nullptr, QObject::tr("SpreadsheetWarning"), 
			QObject::tr("The doucument has been modified.\n"
			"Do you want to save your changes?"), 
			QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
		return false;
	}
	QDataStream out(&file);
	out.setVersion(QDataStream::Qt_4_3);
	out << quint32(0x12345678) << image << map;	// 保证数字0x12345678在所有平台上都是按照无符号32位整数形式写入的使用了quint32
	if (file.flush())
	{
		QMessageBox::warning(nullptr, QObject::tr("SpreadsheetWarning"), 
			QObject::tr("Save Ok!"), 
			QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
		return true;
	}
	else
		QMessageBox::warning(nullptr, QObject::tr("SpreadsheetWarning"), 
			QObject::tr("Save Wrong!"), 
			QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
	return false;
}
#else
bool f(const QString fileName)
{
	quint32 n;
	QImage image;
	QMap<QString, QColor> map;
	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly))
	{
		QMessageBox::warning(nullptr, "warning", QString("Fail to read the file ") + fileName);
		return false;
	}
	QDataStream in(&file);
	in.setVersion(QDataStream::Qt_4_3);	// 如果仅仅是对C++数据类型进行操作, 不用调用这个函数
	in >> n >> image >> map;	// 如果错误发生, 则 >> 操作符总是读取0值或者空值;
	if (in.status() == QDataStream::Ok)	// QDataStream::ReadPastEnd QDataStream::ReadCorruptData
	{
		QMessageBox::warning(nullptr, "tips", QString("Read file Ok!") + (map["blue"] == Qt::blue ? "blue was read!" : "but i don't tell you data"));
		return true;
	}
	return false;
}
#endif
int main(int argc, char ** argv)
{
	QApplication App(argc, argv);

	f(FILENAME);
	App.quit();
	App.exec();
}
