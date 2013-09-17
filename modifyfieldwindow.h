#ifndef MODIFYFIELDWINDOW_H
#define MODIFYFIELDWINDOW_H

#include <QDialog>
#include <QMessageBox>
#include <vector>
#include <QString>

#include "field.h"

namespace Ui {
class ModifyFieldWindow;
}

class ModifyFieldWindow : public QDialog
{
    Q_OBJECT
    
public:
    explicit ModifyFieldWindow(QWidget *parent = 0);
    ~ModifyFieldWindow();
    Field* getField();
    int getIndex();
    void setFields(vector<Field*>);
private slots:
    void on_MFWBt_Modify_clicked();

private:
    Ui::ModifyFieldWindow *ui;
    Field* field;
    int index;
};

#endif // MODIFYFIELDWINDOW_H
