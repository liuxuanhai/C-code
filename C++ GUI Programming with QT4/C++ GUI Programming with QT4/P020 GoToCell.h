#ifndef GOTOCELL_H
#define GOTOCELL_H

#include <QDialog>
#include "GeneratedFiles/ui_P020 GoToCell.h"

class GoToCellDialog : public QDialog, public Ui::GoToCellDialog
{
	Q_OBJECT;
public:
	GoToCellDialog(QWidget * parent = 0);
private slots:
	void on_lineEdit_textChanged();		
};

#endif