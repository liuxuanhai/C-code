#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QAction;
class QLabel;
class FindDialog;
class Spreadsheet;

class MainWindow : public QMainWindow
{
	Q_OBJECT;
public:
	MainWindow();
protected:
	void closeEvent(QCloseEvent * event);	// closeEvent()是QWidget类中的一个虚函数, 当用户关闭窗口的时候, 这个函数将会被自动调用		event 事件
											// 这里重新实现它, 以到达向用户询问是否保存的问题, 或者执行一些保存用户当前使用状态等等的东西
private slots:	// 像 File->New这样的菜单, 在MainWindow中会被实现为私有槽
	// File菜单
	void newFile();
	void openRecentFile(); 
	void open();
	bool save();	// 当槽作为一个信号的响应函数而被执行时, 会忽略返回值, 但是当把槽作为函数来调用的时候, 返回值就和普通C++函数一样了
	bool saveAs();
	// Edit菜单
	void cut(){}
	void copy(){}
	void paste(){}
	void del(){} 
	void find(){};
	void goToCell(){}
	// Tools菜单
	void recalculate(){}
	void sort(){};
	// Options菜单
	void autoRecalculate(){}
	// Help菜单
	void about(){};
	// 状态栏
	void updateStatusBar(){};	// 用于更新单元格定位指示器和单元格公式指示器
	void spreadsheetModified();	// modefied 修改, 改进
private:
	// 创建动作
	void createActions();
	void createFileActions();
	void createEditActions();
	void createToolsActions();
	void createHelpActions();
	void createOptionsActions();	

	// 创建菜单
	void createContextMenu();	// 上下文菜单, 在用户右键点击的时候出现的菜单
	void createMenus();		// 创建包含动作的菜单系统
	void createFileMenu();
	void createEditMenu();
	void createToolsMenu();
	void createOptionsMenu();
	void createHelpMenu();

	
	void createToolBars();	// 创建工具栏
	void createStatusBar();	// 创建状态栏
	
	// 辅助函数
	bool okToContinue();	// 判断是是否存在未保存的文件
	bool loadFile(const QString & fileName);
	bool saveFile(const QString & fileName);
	void setCurrentFile(const QString & fileName);	// 设置当前打开的文件的变量, 标题和最近文件显示(他不负责打开文件)
														// 1. curFile = fileName 为空	设置标题为Untitled 不更新最近打开文件列表
														// 2. curFile = fileName 非空	设置标题(除去路径) 更新最近打开文件列表
	void updateRecentFileActions();	// 更新File菜单中的条目
	void writeSettings();
	void readSettngs();
	QString strippedName(const QString & fullFileName);	// 用来移除文件名中的路径部分
	
	// 用到的窗口部件
	Spreadsheet	* spreadsheet;
	FindDialog	* findDialog;
	
	QStringList	  recentFiles;
	QString		  curFile;

	// 间隔器
	QAction * separatorAction;

	// File菜单
	enum{ MaxRecentFiles = 5 };
	QMenu	* fileMenu;
	QAction * newAction;	// 新建动作
	QAction * openAction;	// 打开动作
	QAction * saveAction;	// 保存动作
	QAction * saveAsAction;	// 另存为动作
	QAction * recentFileActions[MaxRecentFiles];
	QAction * exitAction;	// 退出动作
	
	// Edit菜单
	QMenu	* editMenu;
	QToolBar* fileToolBar;
	QToolBar* editToolBar;
	QAction * cutAction;	// 剪切
	QAction * copyAction;	// 复制
	QAction * pasteAction;// 粘贴
	QAction * deleteAction;
	QAction * selectAction;
	QAction * selectAllAction;	// 全选
	QAction * findAction;
	QAction * goToCellAction;
	
	// Tools菜单
	QMenu	* toolsMenu;
	QAction * recalculateAction;
	QAction * sortAction;

	// Options菜单
	QMenu	* optionsMenu;
	QAction * showGridAction;	// 这是一个复选动作, 启用的时候, Spreadsheet组件就会显示一个网格
	QAction * autoRecalculateAction;

	// Help菜单
	QMenu	* helpMenu;
	QAction * aboutAction;
	QAction * aboutQtAction;

	// 状态栏
	QLabel	* locationLabel;
	QLabel	* formulaLabel;
};

#endif