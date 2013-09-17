#ifndef NEWFIELDWINDOW_H
#define NEWFIELDWINDOW_H

#include <QDialog>
#include <QString>
#include <QMessageBox>
#include <iostream>

#include "field.h"

namespace Ui {
class NewFieldWindow;
}

class NewFieldWindow : public QDialog
{
    Q_OBJECT
    
public:
    explicit NewFieldWindow(QWidget *parent = 0);
    ~NewFieldWindow();
    Field* getField();

private slots:
    void on_NFWBt_add_clicked();

private:
    Ui::NewFieldWindow *ui;
    Field* field;
};

#endif // NEWFIELDWINDOW_H
