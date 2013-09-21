#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H

#include <QDialog>
#include <sstream>
#include <QMessageBox>
#include "field.h"

namespace Ui {
class InputDialog;
}

class InputDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit InputDialog(QWidget *parent = 0);
    ~InputDialog();
    QString getString();
    void setField(Field*);
private slots:
    void on_IDBotton_clicked();

private:
    Ui::InputDialog *ui;
    QString str = "";
};

#endif // INPUTDIALOG_H
