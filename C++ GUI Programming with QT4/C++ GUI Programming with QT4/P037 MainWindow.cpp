#include "P010 FindDialog.h"
#include "P020 GoToCell.h"
#include "P036 MainWindow.h"
#include "P027 sortdialog.h"
#include "P060 Spreadsheet.h"

MainWindow::MainWindow()
{
	spreadsheet = new Spreadsheet;	// 创建一个Spreadsheet窗口部件
	setCentralWidget(spreadsheet);	// 将其设置为这个主窗口的中央窗口, 中央窗口部件会占用主窗口的中央区域部分

	//// 创建主窗口的其余部分
	createActions();	// 创建"动作", "动作"是菜单或者工具栏中得一个选项
	createMenus();
	createContextMenu();
	createToolBars();
	createStatusBar();

	//// 读取这个应用程序存储的一些设置
	readSettngs();

	findDialog = nullptr;	// 将这个指针初始化为空, 在第一次调用MainWindow::find()函数的时候, 将创建该FindDialog对象

	setWindowIcon(QIcon("images/panda.png"));	// 设置显示在窗口左上角的图标(Qt的资源机制法)
			// 为程序提供图片的三种方法:
			//		1. 把图片保存到文件中, 并且在运行的时候载入他们;
			//		2. 把XPM文件包含在源代码中(这一方法之所以可行, 是因为XPM文件也是有效的C++文件);
			//		3. 使用Qt的资源机制(resource mechanism);

	setCurrentFile("");
}

void MainWindow::createActions()
{
	createFileActions();
	createEditActions();
	createToolsActions();
	createOptionsActions();
	createHelpActions();
}

#include <QMenuBar>
void MainWindow::createMenus()
{
	createFileMenu();
	createEditMenu();
	createToolsMenu();
	createOptionsMenu();
	createHelpMenu();
}

void MainWindow::createContextMenu()
{
	spreadsheet->addAction(cutAction);
	spreadsheet->addAction(copyAction);
	spreadsheet->addAction(pasteAction);
	spreadsheet->setContextMenuPolicy(Qt::ActionsContextMenu);
}

#include <QStatusBar>
void MainWindow::createStatusBar()
{
	locationLabel = new QLabel(" W999 ");
	locationLabel->setAlignment(Qt::AlignHCenter);
	locationLabel->setMinimumSize(locationLabel->sizeHint());

	formulaLabel = new QLabel;
	formulaLabel->setIndent(3);	// indent 缩进	设置一个缩进格式, 以便让那些在他里面显示的文本能够与他的左侧有一个小的偏移量

	statusBar()->addWidget(locationLabel);		// 第一次调用statusBar()的时候会创建状态栏// QLabel对象添加到状态栏中, 他们的父对象会被自动重定义
	statusBar()->addWidget(formulaLabel, 1);	// 伸展因子 1 实现了定位指示器的多余空间分配给公式指示器
												// 伸展因子 0 意味着它不喜欢被伸展
	
	connect(spreadsheet, SIGNAL(currentCellChanged(int, int, int, int)), this, SLOT(updateStatusBar()));
	connect(spreadsheet, SIGNAL(modified()), this, SLOT(spreadsheetModified()));
	updateStatusBar();
}

void MainWindow::spreadsheetModified()
{
	setWindowModified(true);	// 把windowModified属性设置成true, 用以更新标题栏
	updateStatusBar();			// 更新位置和公式指示器
}

#include <QToolBar>
void MainWindow::createToolBars()
{
	fileToolBar = addToolBar(tr("&File"));
	fileToolBar->addAction(newAction);
	fileToolBar->addAction(openAction);
	fileToolBar->addAction(saveAction);

	editToolBar = addToolBar(tr("&Edit"));
	editToolBar->addAction(cutAction);
	editToolBar->addAction(copyAction);
	editToolBar->addAction(pasteAction);
	editToolBar->addSeparator();
	editToolBar->addAction(findAction);
	editToolBar->addAction(goToCellAction);
}

void MainWindow::createFileActions()
{
	newAction = new QAction(tr("&New"), this);	// 加速键New 父对象为主窗口
	newAction->setIcon(QIcon("images/newFile.png"));
	newAction->setShortcut(QKeySequence::New);	// 使用适当的QKeySequence::StandardKey枚举值, 可以确保Qt能够为应用程序在其运行的平台上提供正确的快捷键
												// 这里的表象是在菜单的选项后边多了一个 Ctrl + N, 这里的N是因为QKeySequence::New而不是"&New"
												// Sequence 序列, 顺序
	newAction->setStatusTip(tr("Create a new spreadsheet file"));	// 状态提示
	connect(newAction, SIGNAL(triggered()), this, SLOT(newFile()));	// triggered 触发

	openAction = new QAction(tr("&Open"), this);
	openAction->setIcon(QIcon("images/openFile"));
	openAction->setShortcut(QKeySequence::Open);
	openAction->setStatusTip(tr("Open a file"));
	connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

	saveAction = new QAction(tr("&Save"), this);
	saveAction->setIcon(QIcon("images/save.png"));
	saveAction->setShortcut(QKeySequence::Save);
	openAction->setStatusTip(tr("Save the file"));
	connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));
	
	saveAsAction = new QAction(tr("Save As"), this);
	saveAsAction->setIcon(QIcon("images/saveAs.png"));
	saveAsAction->setShortcut(QKeySequence::SaveAs);
	connect(saveAsAction, SIGNAL(triggered()), this, SLOT(save()));

	exitAction = new QAction(tr("E&xit"), this);
	exitAction->setIcon(QIcon("images/exit.png"));
	exitAction->setShortcut(tr("Ctrl + Q"));	// 由于没有标准化键序列, 所以需要在这里明确指定键序列
	exitAction->setStatusTip(tr("Exit the application"));
	connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

	// 最近打开的文件
	for (int i = 0; i < MaxRecentFiles; i++)
	{
		recentFileActions[i] = new QAction(this);
		recentFileActions[i]->setVisible(false);	// 添加的这些动作都是隐式的
		connect(recentFileActions[i], SIGNAL(triggered()), this, SLOT(openRecentFile()));
	}
}

void MainWindow::createEditActions()
{
	cutAction = new QAction(tr("&Cut"), this);
	cutAction->setIcon(QIcon("images/cut.png"));
	cutAction->setShortcut(QKeySequence::Cut);
	connect(cutAction, SIGNAL(triggered()), this, SLOT(cut()));

	copyAction = new QAction(tr("&Copy"), this);
	copyAction->setIcon(QIcon("images/copy.png"));
	copyAction->setShortcut(QKeySequence::Copy);
	connect(copyAction, SIGNAL(triggered()), this, SLOT(copy()));

	pasteAction = new QAction(tr("&Paste"), this);
	pasteAction->setIcon(QIcon("images/paste.png"));
	pasteAction->setShortcut(QKeySequence::Paste);
	connect(pasteAction, SIGNAL(triggered()), this, SLOT(paste()));

	deleteAction = new QAction(tr("Delete"), this);
	deleteAction->setIcon(QIcon("images/delete.png"));
	deleteAction->setShortcut(QKeySequence::Delete);
	connect(deleteAction, SIGNAL(triggered()), this, SLOT(del()));

	selectAllAction = new QAction(tr("&All"), this);
	selectAllAction->setShortcut(QKeySequence::SelectAll);
	selectAllAction->setStatusTip(tr("Select all the cells in the spreadsheet"));
	connect(selectAllAction, SIGNAL(triggered()), spreadsheet, SLOT(selectAll()));	// QTableWidget的父类之一QAbstractItemView提供

	findAction = new QAction(tr("&Find"), this);
	findAction->setIcon(QIcon("images/find.png"));
	findAction->setShortcut(QKeySequence::Find);
	connect(findAction, SIGNAL(triggered()), this, SLOT(find()));

	goToCellAction = new QAction(tr("Go To Cell"), this);
	goToCellAction->setIcon(QIcon("images/goNext.png"));
	goToCellAction->setShortcut(tr("Ctrl + G"));
	connect(goToCellAction, SIGNAL(triggered()), this, SLOT(goToCell()));
}

void MainWindow::createToolsActions()
{
	recalculateAction = new QAction(tr("Recalrulate"), this);
	recalculateAction->setShortcut(tr("F9"));
	connect(recalculateAction, SIGNAL(triggered()), this, SLOT(recalculate()));

	sortAction = new QAction(tr("Sort..."), this);
	connect(sortAction, SIGNAL(triggered()), this, SLOT(sort()));
}

void MainWindow::createOptionsActions()
{
	showGridAction = new QAction(tr("&Show Grid"), this);
	showGridAction->setCheckable(true);	// 这是一个复选动作
	showGridAction->setChecked(spreadsheet->showGrid());	// 启用的时候, Spreadsheet组件就会显示一个网格
	showGridAction->setStatusTip(tr("Show or hide the spreadsheet's grid"));
	connect(showGridAction, SIGNAL(toggled(bool)), spreadsheet, SLOT(setShowGrid(bool)));	// 这个槽继承于QTableWidget

	autoRecalculateAction = new QAction(tr("Auto Recalculate"), this);
	autoRecalculateAction->setCheckable(true);
	autoRecalculateAction->setChecked(true);
	connect(autoRecalculateAction, SIGNAL(toggled(bool)), this, SLOT(autoRecalculate()));
}

void MainWindow::createHelpActions()
{ 
	aboutAction = new QAction(tr("About"), this);
	connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

	aboutQtAction = new QAction(tr("About &Qt"), this);
	aboutQtAction->setIcon(QIcon("images/qtLogo.png"));
	aboutQtAction->setStatusTip(tr("Show the Qt library's About box"));
	connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));	// 通过访问qApp全局变量, 我们可以使用QApplication的aboutQt()槽
}

void MainWindow::createFileMenu()
{
	
	fileMenu = menuBar()->addMenu(tr("&File"));	// addMenu()会用指定的文本创建一个QMenu窗口部件, 并且会把它添加到菜单中
												// menuBar()函数返回一个指向QMenuBar的指针
												// 菜单栏会在第一次调用menuBar()函数的时候创建出来
	fileMenu->addAction(newAction);	// 为File菜单添加动作
	fileMenu->addAction(openAction);
	fileMenu->addAction(saveAction);
	fileMenu->addAction(saveAsAction);
	
	separatorAction = fileMenu->addSeparator();	// separaotr 间隔器 插入间隔器会从视觉上把关系密切的这些项目放在一起
												// 这里保存了一个间隔符, 这样就可以允许隐藏(如果没有最近文件)或者显示那个间隔器, 因为两个间隔器之间什么都没有有点逗逼
	for (int i = 0; i < MaxRecentFiles; i++)
		fileMenu->addAction(recentFileActions[i]);	// 使用循环添加recentFileActions数组中得内容(最初是隐藏的)
	fileMenu->addSeparator();
	fileMenu->addAction(exitAction);
}

void MainWindow::createEditMenu()
{
	editMenu = menuBar()->addMenu(tr("&Edit"));
	editMenu->addAction(cutAction);
	editMenu->addAction(copyAction);
	editMenu->addAction(pasteAction);
	editMenu->addAction(deleteAction);
	editMenu->addSeparator();
	editMenu->addAction(findAction);
	editMenu->addAction(goToCellAction);
}

void MainWindow::createToolsMenu()
{
	toolsMenu = menuBar()->addMenu(tr("&Tools"));
	toolsMenu->addAction(recalculateAction);
	toolsMenu->addAction(sortAction);
}

void MainWindow::createOptionsMenu()
{
	optionsMenu = menuBar()->addMenu(tr("Options"));
	optionsMenu->addAction(showGridAction);
	optionsMenu->addAction(autoRecalculateAction);
}

void MainWindow::createHelpMenu()
{
	helpMenu = menuBar()->addMenu(tr("Help"));
	helpMenu->addAction(aboutAction);
	helpMenu->addAction(aboutQtAction);
}

void MainWindow::newFile()
{
	if (okToContinue())	// 用来判断此时程序中是否存在未保存的文件
	{
		spreadsheet->clear();	// 清空电子制表软件中的全部单元格和公式
		setCurrentFile("");		// 更新窗口的标题, 以说明正在编辑的是一个没有标题的文档, 他还会设置curFile文件并且更新最近打开的额文件的列表
	}
}

#include <QMessageBox>
bool MainWindow::okToContinue()
{
	if (isWindowModified())
	{
		int r = QMessageBox::warning(this, tr("SpreadsheetWarning"), 
			tr("The doucument has been modified.\n"
			"Do you want to save your changes?"), 
			QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
		if (r == QMessageBox::Yes)
			return save();
		else if (r == QMessageBox::Cancel)
			return false;
	}
	return true;
}

#include <QFileDialog>
void MainWindow::open()
{
	if (okToContinue())	// 处理未保存的变化
	{
		QString fileName = QFileDialog::getOpenFileName(this, tr("Open Spreadsheet"), ".", tr("Spread files (*.sp)"));
										// 使用静态函数从用户那里获得一个新的文件名, 这个函数会弹出一个文件对话框, 让用户选择文件, 并返回选择文件的文件名
										// 如果用户点击了Cancel按钮, 则返回一个空字符串
										// 第一个参数是他的父窗口部件, 用于对话框和其他窗口部件, 这个不同于对话框和其他窗口部件的父子关系, 对话框通常拥有自主权, 但是如果他有父对象, 默认情况下它会居中放在父对象上, 一个子对话框也会公用父对象的任务栏
										// 第二个参数是对话框标题
										// 第三个告诉它应该从哪一级目录开始, 在这个例子中是当前目录
										// 第四个指定了文件过滤器, filter由一个描述文本和一个通配符组成
		if (!fileName.isEmpty())		
			loadFile(fileName);
	}
}

bool MainWindow::loadFile(const QString & fileName)
{
	if (!spreadsheet->readFile(fileName))	// readFile()读取磁盘中的文件
											// 如果读取不成功的话, readFile()将会通过一个消息框把遇到的问题通知给用户, 通常情况下, 让底层组件来报告错误消息是一个不错的习惯, 因为他们可以提供准确的错误细节
	{
		statusBar()->showMessage(tr("Loading canceled"), 2000);	// 状态栏中显示一个消息2000毫秒
		return false;
	}

	setCurrentFile(fileName);
	statusBar()->showMessage(tr("File loaded"), 2000);
	return true;
}

bool MainWindow::save()// 如果这个文件是之前打开文件或者是一个已经保存过的文件, 这样已经有了一个名字, 那么save()函数就会用这个名字调用saveFile()函数, 否则, 它只是简单的调用saveAs()函数
{
	if (curFile.isEmpty())
		return saveAs();
	else
		return saveFile(curFile);
}

bool MainWindow::saveFile(const QString & fileName)	
{
	if (!spreadsheet->writeFile(fileName))
	{
		statusBar()->showMessage(tr("Saving canceled"), 2000);
		return false;
	}

	setCurrentFile(fileName);
	statusBar()->showMessage(tr("File Saved"), 2000);
	return true;
}

bool MainWindow::saveAs()
{
	QString fileName = QFileDialog::getSaveFileName(this, // 通过此函数从用户那里得到一个文件名, 如果用户单击了Cancel, 则返回false, 这将会使这个结果向上传递给他的调用者save()或者okToContinue()			如果给定的文件已经存在, getSaveFileName()函数将会要求用户确认是否覆盖该文件, 但是通过给getSaveFileName()函数传递一个QFIleDialog::DontConfirmOverwrite附加参数, 可以改变这一行为
		tr("Save Spreadsheet"), ".", tr("Spreadsheet files (*.sp)"));
	if (fileName.isEmpty())
		return false;

	return saveFile(fileName);
}

#include <QCloseEvent>
void MainWindow::closeEvent(QCloseEvent * e)	// 这里通过重新实现QWidget::closeEvent()函数, 就可以中途截取对这个主窗口的关闭操作, 并且确定是不是真的关闭这个窗口	 如果接受这个事件的话, Qt会隐藏该窗口, 当最后一个窗口关闭后, 应用程序就结束了	如果把QApplication的quitOnLastWindowClosed属性设置为false, 可以禁止这种行为, 这样, 该程序会运行到调用QApplication::quit()函数才会结束
{
	if (okToContinue())
	{
		writeSettings();	// 保存这个应用程序的当前设置
		e->accept();
	}
	else
		e->ignore();
}

void MainWindow::setCurrentFile(const QString & fileName)	// 对保存正在编辑的文件名的curFile私有变量进行设置, 再把这个文件名显示在标题栏中之前, 需要使用strippedName()函数移除文件名中的路径字符
{
	curFile = fileName;
	setWindowModified(false);	// 每个QWidget都有一个windowModified属性, 如果该窗口的文档存在没有保存的变化, 则应当把它设置为true, 否则应当将其设置为false

	QString shownName = tr("Untitled");
	if (!curFile.isEmpty())
	{
		shownName = strippedName(curFile);
		recentFiles.removeAll(curFile);
		recentFiles.prepend(curFile);	// prepend 预谋 预先
		updateRecentFileActions();
	}
	setWindowTitle(tr("%1[*] - %2").arg(shownName)	// QString::arg()函数将会使用自己的参数替换最小数字的"%n"参数, 并且会用他的参数返回结果"%n"字符和最终的结果字符串
								   .arg(tr("Spreadsheet")));
	// 直接写setWindowTitle(shownName + tr("[*] - Spreadsheet"));也行, 但是使用arg()函数可以为翻译人员提供更多的灵活性
}

QString MainWindow::strippedName(const QString & fullFileName)	// 移除文件名中的路径字符, 这样可以使文件看起来更友好一些
{
	return QFileInfo(fullFileName).fileName();
}

void MainWindow::updateRecentFileActions()
{
	QMutableStringListIterator i(recentFiles);
	while (i.hasNext())
		if (!QFile::exists(i.next()))
			i.remove();
	for (int j = 0; j < MaxRecentFiles; ++j)
	{
		if (j < recentFiles.count())
		{
			QString text = tr("&%1 %2")
							.arg(j + 1)
							.arg(strippedName(recentFiles[j]));
			recentFileActions[j]->setText(text);
			recentFileActions[j]->setData(recentFiles[j]);
			recentFileActions[j]->setVisible(true);
		}
		else
			recentFileActions[j]->setVisible(false);
	}
	separatorAction->setVisible(!recentFiles.isEmpty());
}

void MainWindow::openRecentFile()	// 用户选择一个最近打开的文件
{
	if (okToContinue())
	{
		QAction * action = qobject_cast<QAction *>	// qobject_cast<T>()函数可在Qt的moc(meta-object compiler, 元对象编译器)所生成的元信息基础上执行动态类型强制类型转换, 它返回一个指向所需QObject子类的指针, 或者是在该对象不能被 转换成所需那种类型时返回0
			(sender());	// 使用sender()查出是哪个特定的动作调用了这个槽
		if (action)
			loadFile(action->data().toString());
	}
}

#include <QSettings>

void MainWindow::writeSettings()	// 保存主窗口的几何形状(位置和尺寸大小), 最近打开文件列表以及ShowGrid和Auto-Recalculate选项的设置值
{
	QSettings settings("Software Inc.", "Spreadsheet");	// 默认情况下, QSettings会存储应用程序中与特定平台相关的一些设置信息
					// "组织的名字", "应用程序的名字"

	settings.setValue("geometry", saveGeometry());
	settings.setValue("recentFiles", recentFiles);
	settings.setValue("showGrid", showGridAction->isCheckable());
	settings.setValue("autoRecalc", autoRecalculateAction->isChecked());

	settings.beginGroup("findDialog");
	//settings.setValue("matchCase", caseCheckBox->isChecked());
	//settings.setValue("searchBackward", backwardCheckBox->isChecked());
	settings.endGroup();
}

void MainWindow::readSettngs()
{
	QSettings settings("Software Inc.", "Spreadsheet");

	restoreGeometry(settings.value("geometry").toByteArray());

	recentFiles = settings.value("recentFiles").toStringList();
	updateRecentFileActions();

	bool showGrid = settings.value("showGrid", true).toBool();
	showGridAction->setChecked(showGrid);

	bool autoRecalc = settings.value("autoRecalc", true).toBool();
	autoRecalculateAction->setChecked(autoRecalc);
}
