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

/*********************************************************
 *Clase que encarga de mostrar al usuario los parametros
 *necesarios para la creacion de un nuevo campo, ademas crea
 *un nuevo campo
 */
class NewFieldWindow : public QDialog
{
    Q_OBJECT
    
    //Metodos publicos
public:
    explicit NewFieldWindow(QWidget *parent = 0);
    ~NewFieldWindow();

    //Accesor
    Field* getField();

    //Acciones que se pueden ejecutar
private slots:
    void on_NFWBt_add_clicked();

    //Caracteriticas privadas
private:
    Ui::NewFieldWindow *ui;
    Field* field;
};

#endif // NEWFIELDWINDOW_H
