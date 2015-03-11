#ifndef GOTOELL_H
#define GOTOCELL_H
#include <QDialog>
#include "ui_P020  GoToCell.h"
class GoToCellDialog : public QDialog, public Ui::GoToCellDialog
{
	Q_OBJECT;
public:
	GoToCellDialog(QWidget * parent = nullptr);
private slots:
	void on_lineEdit_textChanged();
};

#endif