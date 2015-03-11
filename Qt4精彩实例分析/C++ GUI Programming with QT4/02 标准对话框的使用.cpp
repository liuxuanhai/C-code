// 创建: 2014-08-26 13:10:12
// 标准对话框: 文件对话框, 颜色对话框, 字体对话框		
// 还有以后的 QErrorMessage, QInputDialog, QMessageBox, QPrintDialog, QProgressDialog...

#include <QApplication>
#include "02 standardDialogs.h"

int main(int argc, char ** argv)
{
	QApplication app(argc, argv);
	StandardDialogs s(nullptr);

	s.show();
	return app.exec();
}