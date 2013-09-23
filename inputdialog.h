#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H

//Importar los encabezados necesarios
#include <QDialog>
#include <sstream>
#include <QMessageBox>
#include "field.h"

namespace Ui {
class InputDialog;
}

//clase descendiente de un QDialog, solo que agregando metodos
class InputDialog : public QDialog
{
    Q_OBJECT
    
    //metodos publicos
public:
    explicit InputDialog(QWidget *parent = 0);
    ~InputDialog();
    QString getString();
    void setField(Field*);

    //acciones que se puede ejecutar en la ventana
private slots:
    void on_IDBotton_clicked();

    //Caracteristicas privadas que son importantes
private:
    Ui::InputDialog *ui;
    QString str = "";
};

#endif // INPUTDIALOG_H
